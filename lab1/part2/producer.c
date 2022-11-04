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

    // Write "hello" to the message queue
    if (mq_send(mqd, write_msg, strlen(write_msg), 0) == -1) errExit("mq_send");

    // Close the message queue
    mq_close(mqd);
}