#include "utilities.h"

void errExit(const char *cause) 
{
    fprintf(stderr, "Failure! cause: %s\nerrno: %s(%d)\n",
            cause, strerror(errno), errno);
    exit(EXIT_FAILURE);
}

int read_number(int fd) 
{
    char buf[10];
    int i;
    for (i = 0; i < 10; i++) 
    {
        ssize_t res = read(fd, &buf[i], sizeof(char));
        if (res == -1)
            errExit("read");
        else if (res == 0) 
            return -2;
        if (buf[i] == '\n') 
            break;
    }
    buf[i] = '\0';
    return atoi(buf);
}
