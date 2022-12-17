#! /bin/sh

# Create out structure
mkdir -p out

# Compile
gcc -lm -o out/main src/main.c src/utilities.c
