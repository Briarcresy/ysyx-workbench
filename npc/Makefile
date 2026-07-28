TOPNAME=top
RTL_SRC=vsrc/top.v
SIM_SRC=csrc/sim_main.cpp
BIN=obj_dir/V$(TOPNAME)
VERILATOR_FLAGS=--cc --exe --build -Wall --trace-vcd --top-module $(TOPNAME) 

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator $(VERILATOR_FLAGS) $(RTL_SRC) $(SIM_SRC)
	$(BIN)
# 	@echo "Write this Makefile by your self."
	

include ../Makefile
