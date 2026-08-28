TOPNAME = minirvCPU
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

VSRCS = $(shell find $(abspath vsrc) -name "*.v")
CSRCS = $(shell find $(abspath csrc) -name "*.cpp")

default: $(BIN)

$(BIN): $(VSRCS) $(CSRCS)
	mkdir -p $(BUILD_DIR)
	verilator --build --cc -Wall -Wno-fatal \
		--top-module $(TOPNAME) $(VSRCS) $(CSRCS) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: $(BIN)
	$(BIN) $(IMG)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default run clean
