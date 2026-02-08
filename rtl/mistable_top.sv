module mistable_top #(
    parameter int W = 256,
    parameter int H = 240
) (
    input  logic        clk,
    input  logic        rst,
    output logic        pix_valid,
    output logic [7:0]  pix_r,
    output logic [7:0]  pix_g,
    output logic [7:0]  pix_b,
    output logic [15:0] pix_x,
    output logic [15:0] pix_y,
    output logic        frame_done
);

    localparam int BAR_COUNT = 8;
    localparam int BAR_W = (W / BAR_COUNT);
    localparam int LAST_BAR_START = (W * 7) / BAR_COUNT;
    localparam int LAST_BAR_W = (W - LAST_BAR_START);

    always_ff @(posedge clk) begin
        if (rst) begin
            pix_x <= 16'd0;
            pix_y <= 16'd0;
            frame_done <= 1'b0;
        end else begin
            frame_done <= 1'b0;
            if (int'(pix_x) == W - 1) begin
                pix_x <= 16'd0;
                if (int'(pix_y) == H - 1) begin
                    pix_y <= 16'd0;
                    frame_done <= 1'b1;
                end else begin
                    pix_y <= pix_y + 16'd1;
                end
            end else begin
                pix_x <= pix_x + 16'd1;
            end
        end
    end

    always_comb begin
        pix_valid = !rst;

        pix_r = 8'h00;
        pix_g = 8'h00;
        pix_b = 8'h00;

        if (pix_valid) begin
            int bar;
            bar = (pix_x * BAR_COUNT) / W;
            if (bar < 0) bar = 0;
            if (bar > 7) bar = 7;

            if (bar == 7) begin
                int denom;
                int grad;
                denom = (LAST_BAR_W > 1) ? (LAST_BAR_W - 1) : 1;
                grad = (int'(pix_x) - LAST_BAR_START) * 255 / denom;
                if (grad < 0) grad = 0;
                if (grad > 255) grad = 255;
                pix_r = grad[7:0];
                pix_g = grad[7:0];
                pix_b = grad[7:0];
            end else begin
                case (bar)
                    0: begin pix_r = 8'hff; pix_g = 8'h00; pix_b = 8'h00; end
                    1: begin pix_r = 8'hff; pix_g = 8'h80; pix_b = 8'h00; end
                    2: begin pix_r = 8'hff; pix_g = 8'hff; pix_b = 8'h00; end
                    3: begin pix_r = 8'h00; pix_g = 8'hff; pix_b = 8'h00; end
                    4: begin pix_r = 8'h00; pix_g = 8'hff; pix_b = 8'hff; end
                    5: begin pix_r = 8'h00; pix_g = 8'h00; pix_b = 8'hff; end
                    6: begin pix_r = 8'h80; pix_g = 8'h00; pix_b = 8'hff; end
                    default: begin pix_r = 8'hff; pix_g = 8'hff; pix_b = 8'hff; end
                endcase
            end
        end
    end

endmodule
