#! /bin/sh

# Create out structure
mkdir -p out

# Compile
gcc -o out/main src/main.c src/utilities.c src/page_table.c src/tlb.c
