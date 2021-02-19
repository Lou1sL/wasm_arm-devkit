
# Envirmental Settings -------------

COMPILER_DIR = /home/tool/arm-none-eabi-gcc/bin

# ----------------------------------

CXX     = $(COMPILER_DIR)/arm-none-eabi-g++
ASM     = $(COMPILER_DIR)/arm-none-eabi-as
LINK    = $(COMPILER_DIR)/arm-none-eabi-g++
OBJCOPY = $(COMPILER_DIR)/arm-none-eabi-objcopy

# Libraries ------------------------

# ----------------------------------

# Project Settings -----------------

APP_NAME     = app

BUILD_DIR    = ./build
OUT_DIR      = ./out
SRC_DIR      = ./src
INCLUDE_DIR  = ./src

LNKR  = $(SRC_DIR)/linker.ld
ASMS  = $(SRC_DIR)/bootloader.s
SRCS  = $(SRC_DIR)/main.cpp
SRCS += $(SRC_DIR)/arm7tdmi/arm7tdmi.cpp

ASM_OBJS  = $(ASMS:$(SRC_DIR)/%.s=$(OUT_DIR)/%.o)
CPP_OBJS  = $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# ----------------------------------

# Compiling Flags ------------------

CXXFLAGS  = -O0 -std=c++17
CXXFLAGS += -mlittle-endian -marm -march=armv4t -mcpu=arm7tdmi -mtune=arm7tdmi -mthumb-interwork -ffast-math
CXXFLAGS += -mlong-calls -ffunction-sections -fno-omit-frame-pointer -ffreestanding -fno-unwind-tables -fno-exceptions
# CXXFLAGS +=  -nostdlib
CXXFLAGS += --specs=nosys.specs
CXXFLAGS += -Wall -DNDEBUG

ASMFLAGS  = -mcpu=arm7tdmi -mthumb-interwork

LINKFLAGS  = -O0 -std=c++17
LINKFLAGS += --specs=nosys.specs
LINKFLAGS += -T $(LNKR) -o $(BUILD_DIR)/$(APP_NAME).elf -Wl,-Map,$(BUILD_DIR)/$(APP_NAME).map,--cref -lm

# ----------------------------------

.PHONY: all clean

all: $(BUILD_DIR)/$(APP_NAME).elf

$(BUILD_DIR)/$(APP_NAME).elf : $(CPP_OBJS) $(ASM_OBJS)
	$(LINK) $(CPP_OBJS) $(ASM_OBJS) $(LINKFLAGS)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(APP_NAME).elf $(BUILD_DIR)/$(APP_NAME).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(APP_NAME).elf $(BUILD_DIR)/$(APP_NAME).bin

# $(ASM_OBJS): $(OUT_DIR)/%.o : $(SRC_DIR)/%.s
$(OUT_DIR)/bootloader.o: $(ASMS)
	$(ASM) $(ASMFLAGS) -o $@ $<

$(OUT_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -I$(INCLUDE_DIR) $<

$(OUT_DIR)/arm7tdmi/arm7tdmi.o: $(SRC_DIR)/arm7tdmi/arm7tdmi.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ -I$(INCLUDE_DIR) $<


GARBAGE_TYPES         = *.o *.elf *.map *.bin *.hex
DIRECTORIES_TO_CLEAN  = $(shell find "./build" "./out" -type d)
GARBAGE_TYPED_FOLDERS = $(foreach DIR, $(DIRECTORIES_TO_CLEAN), $(addprefix $(DIR)/,$(GARBAGE_TYPES)))

clean:
	$(RM) -rf $(GARBAGE_TYPED_FOLDERS)