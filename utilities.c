#include "utilities.h"

void errExit(const char *cause) {
    fprintf(stderr, "Failure! cause: ");
    fprintf(stderr, cause);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}