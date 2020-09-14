wasm_arm-devkit


This is a demo of compiling C++ code to execute inside wasm_arm.
Copy the hex content from ./build/app.bin and copy to wasm_arm and you are done.


Dependency: 
arm-none-eabi-gcc, remember to edit COMPILER_DIR inside makefile.



wasm_arm : http://ryubai.com/bgba/wasm_arm
wasm_arm is an ARM CPU simulator with rich UI running inside client browser.
wasm_arm supports ARMv4T instruction set, and has 128KB free-to-whatever-use memory.
wasm_arm is written in C++, and is compiled to WebAssembly(hence the name).