#include "utilities.h"

void errExit(const char *cause) 
{
    fprintf(stderr, "Failure! cause: %s\nerrno: %s(%d)\n",
            cause, strerror(errno), errno);
    exit(EXIT_FAILURE);
}
