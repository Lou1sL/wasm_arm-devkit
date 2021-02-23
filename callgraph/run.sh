#!/bin/sh

# sudo apt-get install graphviz
# sudo apt-get install gawk

clang-11 -O0 -S -std=c++17 -emit-llvm graph_main.cpp -o - | opt-11 -std-link-opts -analyze -dot-callgraph -o /dev/null
cat '<stdin>.callgraph.dot' | c++filt > callgraph_filted.dot
cat callgraph_filted.dot | sed 's,>,\\>,g; s,-\\>,->,g; s,<,\\<,g' | gawk '/external node/{id=$1} $1 != id' > callgraph.dot
dot callgraph.dot -Tsvg -o callgraph.svg

rm '<stdin>.callgraph.dot' callgraph_filted.dot