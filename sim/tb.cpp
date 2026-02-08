#include <verilated.h>
#include <fstream>
#include <vector>
#include <cstdint>

#include "Vmistable_top.h"

static const int W = 256;
static const int H = 240;

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vmistable_top top;
    top.clk = 0;
    top.rst = 1;

    const int reset_cycles = 5;
    for (int i = 0; i < reset_cycles; ++i) {
        top.clk = 0;
        top.eval();
        top.clk = 1;
        top.eval();
    }
    top.rst = 0;

    std::vector<uint8_t> fb(W * H * 3, 0);
    bool frame_done = false;

    const int max_cycles = W * H + 1000;
    for (int cycle = 0; cycle < max_cycles; ++cycle) {
        top.clk = 0;
        top.eval();
        top.clk = 1;
        top.eval();

        if (top.pix_valid) {
            uint16_t x = top.pix_x;
            uint16_t y = top.pix_y;
            if (x < W && y < H) {
                size_t idx = (static_cast<size_t>(y) * W + x) * 3;
                fb[idx + 0] = static_cast<uint8_t>(top.pix_r);
                fb[idx + 1] = static_cast<uint8_t>(top.pix_g);
                fb[idx + 2] = static_cast<uint8_t>(top.pix_b);
            }
        }

        if (top.frame_done) {
            frame_done = true;
            break;
        }
    }

    if (!frame_done) {
        return 1;
    }

    std::ofstream out("build/frame.ppm", std::ios::binary);
    if (!out) {
        return 1;
    }

    out << "P6\n" << W << " " << H << "\n255\n";
    out.write(reinterpret_cast<const char *>(fb.data()), fb.size());
    out.close();

    return 0;
}
