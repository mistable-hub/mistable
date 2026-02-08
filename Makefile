SIM_DIR := build/vobj
SIM_BIN := $(SIM_DIR)/sim

.PHONY: sim clean

sim:
	mkdir -p $(SIM_DIR)
	verilator -cc rtl/mistable_top.sv --exe $(abspath sim/tb.cpp) -Mdir $(SIM_DIR) -o sim
	$(MAKE) -C $(SIM_DIR) -f Vmistable_top.mk
	./$(SIM_BIN)

clean:
	rm -rf build
