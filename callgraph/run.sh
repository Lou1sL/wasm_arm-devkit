#!/bin/sh

clang-11 -O0 -S -std=c++17 -emit-llvm graph_main.cpp -o - | opt-11 -std-link-opts -analyze -dot-callgraph -o /dev/null
# sudo apt-get install graphviz
# sudo apt-get install gawk
cat '<stdin>.callgraph.dot' | c++filt | sed 's,>,\\>,g; s,-\\>,->,g; s,<,\\<,g' | gawk '/external node/{id=$1} $1 != id' | dot -Tpng -o callgraph.png