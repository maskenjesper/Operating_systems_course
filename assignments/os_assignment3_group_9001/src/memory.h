#pragma once

#include <stdlib.h>

typedef struct frame {
    char occupied;
    unsigned char buf[256];
} frame;

frame* new_memory();
void init_memory(frame*, int);
char read_byte(unsigned char, unsigned char, frame*);
