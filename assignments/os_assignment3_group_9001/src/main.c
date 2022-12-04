#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "utilities.h"
#include "page_table.h"
#include "tlb.h"

// specs
const int 
PAGESIZE = 256,
FRAMESIZE = 256,
PAGECOUNT = 256,
FRAMECOUNT = 256,
TLBSIZE = 16;

// allocate (physical) memory space
char memory[256 * 256];
unsigned char nextFreeFrame = 0;

int main(int argc, char *argv[]) 
{
    // check parameters
    if (argc != 2) 
    {
        printf("Usage: main <filename>\n");
        exit(1);
    }

    // open file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) 
        errExit("open");

    // create page table and tlb
    ptable* ptable = new_ptable();
    tlb* tlb = new_tlb();

    // read words from file
    int count = 0;
    while (1) 
    {
        // read logical address
        int laddr = read_number(fd);
        if (laddr == -1) 
            errExit("read_number");
        else if (laddr == -2) 
            break; 
        // split into parts
        int page_n = (laddr & 0xff00) >> 8;
        int offset_n = laddr & 0xff;
        // find mapped frame
        int frame_n = tlb_get_frame(tlb, page_n);
        if (frame_n == -1) 
        {
            frame_n = pt_get_frame(ptable, page_n);
            tlb_add_entry(tlb, page_n, frame_n);
        }
        // construct physical address
        int paddr = (frame_n << 8) | offset_n;
        char val = memory[paddr];

        printf("Virtual address: %d Physical address: %d Value: %d\n",
               laddr, paddr, val);
        count++;
    }
    
    printf("Page-fault rate: %f\nTLB hit rate: %f", 
           (float) (ptable->faults)/count, (float) (tlb->hits)/count);

    free_ptable(ptable);
    free_tlb(tlb);

    // close file
    if (close(fd) == -1)
        errExit("close");
    return 0;
}
