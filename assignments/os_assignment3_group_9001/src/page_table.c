#include "page_table.h"

extern char memory[256 * 256];
extern unsigned char nextFreeFrame;

ptable* new_ptable() {
    ptable* ptable = malloc(sizeof(ptable));
    ptable->faults = 0;
    ptable->table = malloc(256 * sizeof(pte));
    for (int i = 0; i < 256; i++) {
        ptable->table[i].valid = 0;
    }
    return ptable;
}

void free_ptable(ptable* ptable) {
    free(ptable->table);
    free(ptable);
}

int pt_get_frame(ptable* table, int page) {
    if (table->table[page].valid != 1) { // page fault
        // open backing store
        FILE* f = fopen("data/BACKING_STORE.bin", "rb");
        if (f == NULL)
            errExit("fopen");
        // set correct read location
        fseek(f, page * 256L, SEEK_SET);
        // read the page into memory at next free frame
        fread(&memory[nextFreeFrame * 256], 1, 256, f);
        fclose(f);

        // update page table with frame reference
        table->table[page].valid = 1;
        table->table[page].frame = nextFreeFrame++;
        table->faults++;
    }
    return table->table[page].frame;
}
