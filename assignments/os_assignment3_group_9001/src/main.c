#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "dependencies/utilities.h"
#include "memory.h"
#include "page_table.h"

int main(int argc, char *argv[]) {
    // check parameters
    if (argc != 2) {
        printf("Usage: main <filename>\n");
        exit(1);
    }

    // open file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) 
        errExit("open");

    // create page table and memory
    pte* ptable = new_page_table();
    frame* memory = new_memory();

    // read words from file
    int count = 0;
    while (1) {
        // read logical address
        int laddr = read_number(fd);
        if (laddr == -1) 
            errExit("read_number");
        else if (laddr == -2) 
            break; 
        // split into parts
        unsigned char page_n = page_number(laddr);
        unsigned char offset_n = offset_number(laddr);
        // find mapped frame
        unsigned char frame_n = get_frame(ptable, page_n, memory);
        printf("page: %d, offset: %d, frame: %d\n", page_n, offset_n, frame_n);
        int paddr = (frame_n << 8) | offset_n;
        char val = read_byte(frame_n, offset_n, memory);
        printf("Virtual address: %d Physical address: %d Value: %d\n",
               laddr, paddr, val);
    }
    
    free(ptable);
    free(memory);

    // close file
    if (close(fd) == -1)
        errExit("close");
    return 0;
}
