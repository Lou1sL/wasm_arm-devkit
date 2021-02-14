
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
SRC_DIR      = ./src
INCLUDE_DIR  = ./src
STARTUP_PATH = ./src/bootloader.s
LINKER_PATH  = ./src/linker.ld

# SRCS  = $(SRC_DIR)/main.cpp
# SRCS += $(SRC_DIR)/arm7tdmi/arm7tdmi.cpp
# OBJS  = $(SRCS:.cpp=.o)

# ----------------------------------

# Compiling Flags ------------------

CXXFLAGS  = -O3 -std=c++17
CXXFLAGS += -mlittle-endian -marm -march=armv4t -mcpu=arm7tdmi -mtune=arm7tdmi -mthumb-interwork -ffast-math
CXXFLAGS += -mlong-calls -ffunction-sections -fno-omit-frame-pointer -ffreestanding -fno-unwind-tables -fno-exceptions
# CXXFLAGS +=  -nostdlib
CXXFLAGS += --specs=nosys.specs
CXXFLAGS += -Wall -DNDEBUG
CXXFLAGS +=  -c -o $@

ASMFLAGS  = -mcpu=arm7tdmi -mthumb-interwork
ASMFLAGS +=  -o $@

LINKFLAGS  = -O3 -std=c++17
LINKFLAGS += --specs=nosys.specs
LINKFLAGS += -T $(LINKER_PATH) -o $(BUILD_DIR)/$(APP_NAME).elf -Wl,-Map,$(BUILD_DIR)/$(APP_NAME).map,--cref -lm

# ----------------------------------

all: $(BUILD_DIR)/$(APP_NAME).elf

$(BUILD_DIR)/$(APP_NAME).elf : $(BUILD_DIR)/bootloader.o $(BUILD_DIR)/main.o $(BUILD_DIR)/arm7tdmi.o
	$(LINK) $(BUILD_DIR)/bootloader.o $(BUILD_DIR)/main.o $(BUILD_DIR)/arm7tdmi.o $(LINKFLAGS)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(APP_NAME).elf $(BUILD_DIR)/$(APP_NAME).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(APP_NAME).elf $(BUILD_DIR)/$(APP_NAME).bin

$(BUILD_DIR)/bootloader.o: $(STARTUP_PATH)
	$(ASM) $(ASMFLAGS) $<

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $<

$(BUILD_DIR)/arm7tdmi.o: $(SRC_DIR)/arm7tdmi/arm7tdmi.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $<

.PHONY: clean

clean:
	-rm $(BUILD_DIR)/*.o
	-rm $(BUILD_DIR)/*.elf
	-rm $(BUILD_DIR)/*.map
	-rm $(BUILD_DIR)/*.bin
	-rm $(BUILD_DIR)/*.hex