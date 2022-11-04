#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int error(const char *cause) {
    fprintf(stderr, "Failure! cause: ");
    fprintf(stderr, cause);
    fprintf(stderr, "\n");
    return 1;
}

void parent() {

}

void producer() {

}

void consumer() {

}

int main() {
    switch (fork()) {
        case -1:
            return error("fork");
        case 0: // child
            producer();
            break;
        default: // parent
            switch (fork()) {
                case -1:
                    return error("fork");
                case 0:
                    consumer();
                    break;
                default:
                    parent();
                    break;
            }
            break;
    }
}