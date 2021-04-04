@echo off
docker run --rm -it -v %cd%:/home/wasm_arm-devkit -w="/home/wasm_arm-devkit" devkitpro/devkitarm make clean