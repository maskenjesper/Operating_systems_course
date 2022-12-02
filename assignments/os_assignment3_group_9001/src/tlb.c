#include "tlb.h" 

extern const int TLBSIZE;

tlb* new_tlb() {
    tlb* tlb = malloc(sizeof(tlb));
    tlb->hits = 0;
    tlb->pos = 0;

    tlb->table = malloc(TLBSIZE * sizeof(tlbe));
    for (int i = 0; i < TLBSIZE; i++) {
        tlb->table[i].valid = 0;
    } 
    return tlb;
}

void free_tlb(tlb* tlb) {
    free(tlb->table);
    free(tlb);
}

int tlb_get_frame(tlb* tlb, int page) {
    for (int i = 0; i < TLBSIZE; i++) {
        if (tlb->table[i].valid == 1 && tlb->table[i].page == page) {
            tlb->hits++;
            return tlb->table[i].frame;
        }
    }
    return -1;
}

void tlb_add_entry(tlb* tlb, int page, int frame) {
    if (tlb->pos >= TLBSIZE) {
        tlb->pos = 0;
    }
    tlb->table[tlb->pos].valid = 1;
    tlb->table[tlb->pos].page = page;
    tlb->table[tlb->pos].frame = frame;
    tlb->pos++;
}
