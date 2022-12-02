#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "utilities.h"

typedef struct pte {
    int valid;
    int frame;
} pte;

typedef struct ptable {
    pte* table;
    int faults;
} ptable;

ptable* new_ptable();
void free_ptable(ptable* ptable);
int pt_get_frame(ptable* table, int page);
