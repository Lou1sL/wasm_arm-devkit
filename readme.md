wasm_arm-devkit

wasm_arm : http://ryubai.com/e/wasm_arm


This is a demo of compiling C++ code for wasm_arm.

It has 4KB user/system mode stack, 256Bytes for each other mode stacks, and 32KB heap.

Copy the hex content from ./build/app.bin to Data string textarea or just click Load *.bin File button.


Dependency: 

arm-none-eabi-gcc, remember to edit COMPILER_DIR inside makefile.

https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads


