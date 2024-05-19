TOP_NAME = top
SIM_NAME = sub_add
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  --trace\
				-O3 --x-assign fast --x-initial fast --noassert

BUILD_DIR = ./build
OBJ = ./obj_dir
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOP_NAME)

default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
TB_CPP = $(NPC_HOME)/csrc/tb_$(SIM_NAME).cpp
SIM = $(abspath ./vsrc/$(SIM_NAME).v)
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*main.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOP_NAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOP_NAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

all: default

run: $(BIN)
	@$^

sim:
	$(call git_commit, "sim RTL")
	$(VERILATOR) --top-module $(SIM_NAME) --cc $(SIM)
	$(VERILATOR) -Wall --trace --x-assign unique --x-initial unique --cc $(SIM) --exe $(TB_CPP)
	make -C $(OBJ) -f V$(SIM_NAME).mk V$(SIM_NAME)
	./$(OBJ)/V$(SIM_NAME) +verilator+rand+reset+2

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ)

.PHONY: default all clean run sim

include ../Makefile

