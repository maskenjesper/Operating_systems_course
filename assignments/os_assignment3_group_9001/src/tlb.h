#pragma once

#include <stdlib.h>

typedef struct tlbe {
    int valid;
    int page;
    int frame;
} tlbe;

typedef struct tlb {
    tlbe* table;
    int pos;
    int hits;
} tlb;

tlb* new_tlb();
void free_tlb(tlb* tlb);
int tlb_get_frame(tlb* tlb, int page);
void tlb_add_entry(tlb* tlb, int page, int frame);
