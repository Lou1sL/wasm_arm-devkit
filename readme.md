wasm_arm-devkit

wasm_arm : http://ryubai.com/e/wasm_arm


This is a demo of compiling C++ code for wasm_arm.

It has 1MB user/system mode stack, 4KB for each other mode stacks, and 1MB heap.

Copy the hex content from ./build/app.bin to Data string textarea or just click Load *.bin File button.


Dependency: 

arm-none-eabi-gcc, remember to edit COMPILER_DIR inside makefile.

https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads


