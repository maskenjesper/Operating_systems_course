#include "memory.h"

frame* new_memory() {
    int size = 256;
    frame* memory = malloc(size * sizeof(frame));
    init_memory(memory, size);
    return memory;
}

void init_memory(frame* memory, int size) {
    for (int i = 0; i < size; i++) {
        memory[i].occupied = 0;
    }
}

char read_byte(unsigned char frame_n, unsigned char offset_n, frame* memory) {
    return memory[frame_n].buf[offset_n];
}
