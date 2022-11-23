#! /bin/sh

# Create out structure
mkdir -p out

# Compile
gcc -o out/main -pthread src/main.c src/dependencies/utilities.c
