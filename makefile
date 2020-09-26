
APP_NAME  = app
SRC_DIR = .
BUILD_DIR = ./build
COMPILER_DIR = /home/wasm_arm-gcc

CC      = "$(COMPILER_DIR)/bin/arm-none-eabi-g++"
ASM     = "$(COMPILER_DIR)/bin/arm-none-eabi-as"
LINK    = "$(COMPILER_DIR)/bin/arm-none-eabi-g++"
OBJCOPY = "$(COMPILER_DIR)/bin/arm-none-eabi-objcopy"

CCFLAGS = --specs=nosys.specs -marm -march=armv4t -mcpu=arm7tdmi -mtune=arm7tdmi -mthumb-interwork -ffast-math \
	-mlong-calls \
	-ffunction-sections -fno-omit-frame-pointer \
	-fno-unwind-tables -fno-exceptions -nostdlib \
	-ffreestanding \
	-Wall -DNDEBUG -O3 -c -o $@

ASMFLAGS = -mcpu=arm7tdmi -mthumb-interwork -o $@

LINKFLAGS = --specs=nosys.specs \
	-O3 -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/$(APP_NAME).elf -Wl,-Map,$(BUILD_DIR)/$(APP_NAME).map,--cref -lm


all: $(BUILD_DIR)/$(APP_NAME).hex

$(BUILD_DIR)/$(APP_NAME).hex : $(BUILD_DIR)/$(APP_NAME).bin
	$(OBJCOPY) -I binary -O ihex $< $@

$(BUILD_DIR)/$(APP_NAME).bin : $(BUILD_DIR)/$(APP_NAME).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(APP_NAME).elf : $(SRC_DIR)/linker.ld $(BUILD_DIR)/bootloader.o $(BUILD_DIR)/main.o
	$(LINK) $(BUILD_DIR)/bootloader.o $(BUILD_DIR)/main.o $(LINKFLAGS)

$(BUILD_DIR)/bootloader.o: $(SRC_DIR)/bootloader.s
	$(ASM) $(ASMFLAGS) $<

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CCFLAGS) -I$(SRC_DIR) $<

.PHONY: clean

clean:
	-rm $(BUILD_DIR)/*.o
	-rm $(BUILD_DIR)/*.elf
	-rm $(BUILD_DIR)/*.map
	-rm $(BUILD_DIR)/*.bin
	-rm $(BUILD_DIR)/*.hex