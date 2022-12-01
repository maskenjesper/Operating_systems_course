#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "memory.h"

typedef struct pte {
    char valid;
    char frame;
} pte;

pte* new_page_table();
void init_table(pte*, int);
unsigned char get_frame(pte* table, unsigned char page, frame* memory);
