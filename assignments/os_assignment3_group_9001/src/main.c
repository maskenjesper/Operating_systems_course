#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "dependencies/utilities.h"

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

    // read words from file
    int count = 0;
    while (1) {
        int laddr = read_number(fd);
        if (laddr == -1) 
            errExit("read_number");
        else if (laddr == -2) 
            break; 
        unsigned char page_n = page_number(laddr);
        unsigned char offset_n = offset_number(laddr);
        printf("Address %d: page %d, offset %d\n", ++count, page_n, offset_n);
    }

    // close file
    if (close(fd) == -1)
        errExit("close");
    return 0;
}
