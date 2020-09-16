wasm_arm-devkit


This is a demo of compiling C++ code to execute inside wasm_arm.

Copy the hex content from ./build/app.bin and copy to wasm_arm and you are done.


Dependency: 

arm-none-eabi-gcc, remember to edit COMPILER_DIR inside makefile.

https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads


wasm_arm : http://ryubai.com/e/wasm_arm

wasm_arm is an ARM CPU simulator with rich UI running inside client browser.

It supports ARMv4T instruction set, and has 128KB free-to-whatever-use memory.