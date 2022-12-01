#! /bin/sh

# Create out structure
mkdir -p out

# Compile
gcc -o out/main src/main.c src/dependencies/utilities.c src/page_table.c src/memory.c
