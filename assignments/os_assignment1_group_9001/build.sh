#! /bin/sh

# Create out 

# Compile
gcc -o out/part1/main part1/main.c utilities.c
gcc -o out/part2/receiver part2/receiver.c utilities.c
gcc -o out/part2/sender part2/sender.c utilities.c

# Create text file to test with
touch out/part2/words.txt
echo one two three four fives > out/part2/words.txt