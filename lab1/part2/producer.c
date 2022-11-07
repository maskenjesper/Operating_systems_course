#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include "../../utilities.c"

int main() {
    char *my_mq = "/mymq";
    char *write_msg = "hello my friend";
    mqd_t mqd;

    // Open an existing message queue
    mqd = mq_open(my_mq, O_WRONLY);
    if (mqd == (mqd_t) -1) errExit("mq_open");

    // Open the file to read from
    int fd = open("words.txt", O_RDONLY);
    
    // Read from opened file
    char text[100];
    ssize_t len = read(fd, text, 100);
    if (len == -1) errExit("read");

    // Write "hello" to the message queue
    if (mq_send(mqd, text, len, 0) == -1) errExit("mq_send");

    // Close the message queue
    mq_close(mqd);
}