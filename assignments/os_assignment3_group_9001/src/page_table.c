#include "page_table.h"

extern char memory[];
extern unsigned char nextFreeFrame;
extern const int
PAGESIZE,
PAGECOUNT,
FRAMESIZE;

ptable* new_ptable() {
    ptable* ptable = malloc(sizeof(ptable));
    ptable->faults = 0;
    ptable->table = malloc(PAGECOUNT * sizeof(pte));
    for (int i = 0; i < PAGECOUNT; i++) {
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
        fseek(f, page * (long) PAGESIZE, SEEK_SET);
        // read the page into memory at next free frame
        fread(&memory[nextFreeFrame * FRAMESIZE], 1, PAGESIZE, f);
        fclose(f);

        // update page table with frame reference
        table->table[page].valid = 1;
        table->table[page].frame = nextFreeFrame++;
        table->faults++;
    }
    return table->table[page].frame;
}
