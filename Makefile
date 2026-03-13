SIM_DIR := build/vobj
SIM_BIN := $(SIM_DIR)/sim

.PHONY: sim clean shell sanity golden

sim:
	mkdir -p $(SIM_DIR)
	verilator -cc rtl/mistable_top.sv --exe $(abspath sim/tb.cpp) -Mdir $(SIM_DIR) -o sim
	$(MAKE) -C $(SIM_DIR) -f Vmistable_top.mk
	./$(SIM_BIN)

clean:
	rm -rf build

shell:
	./dev

sanity:
	./scripts/sanity.sh

golden:
	UPDATE_GOLDEN=1 ./scripts/test.sh
