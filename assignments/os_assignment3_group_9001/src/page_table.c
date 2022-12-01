#include "page_table.h"
#include "dependencies/utilities.h"
#include <stdio.h>

pte* new_page_table() {
    int size = 256;
    pte* table = malloc(size * sizeof(pte));
    init_table(table, size);
    return table;
}

void init_table(pte* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i].valid = 0;
    }
}

unsigned char get_frame(pte* table, unsigned char page, frame* memory) {
    if (table[page].valid != 1) {
        FILE* f = fopen("data/BACKING_STORE.bin", "rb");
        if (f == NULL)
            errExit("fopen");
        fseek(f, page * 256L, SEEK_SET);
        for (int i = 0; i < 256; i++) {
            if (memory[i].occupied == 0) {
                memory[i].occupied = 1;
                table[page].frame = i;
                fread(memory[i].buf, 1, 256, f);
                table[page].valid = 1;
                break;
            }
        }
        fclose(f);
    }
    return table[page].frame;
}
