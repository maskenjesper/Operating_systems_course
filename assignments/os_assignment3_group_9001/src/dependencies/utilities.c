#include "utilities.h"

void errExit(const char *cause) {
    fprintf(stderr, "Failure! cause: ");
    fprintf(stderr, "%s", cause);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

unsigned char page_number(int laddr) {
    return (laddr & 0xff00) >> 8;
}

unsigned char offset_number(int laddr) {
    return laddr & 0xff;
}

int read_number(int fd) {
    char buf[10];
    int i;
    for (i = 0; i < 10; i++) {
        ssize_t res = read(fd, &buf[i], sizeof(char));
        if (res == -1)
            errExit("read");
        else if (res == 0) 
            return -2;
        if (buf[i] == '\n') 
            break;
    }
    buf[i] = '\0';
    int num = atoi(buf);
    printf("%d\n", num);
    return num;
}
