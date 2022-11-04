#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "../../utilities.c"

int main() {
    int MAX_SIZE = 100;
    int MAX_NUM_MSG = 10;
    char *my_mq = "/mymq";
    char buf[MAX_SIZE];
    mqd_t mqd;
    struct mq_attr attr;

    // Form the queue attributes
    attr.mq_maxmsg = MAX_NUM_MSG;
    attr.mq_msgsize = MAX_SIZE;

    // Create message queue
    mqd = mq_open(my_mq, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);
    if (mqd == (mqd_t) -1) errExit("mq_open");

    // Read the message from the message queue
    if (mq_receive(mqd, buf, MAX_SIZE, NULL) == -1) errExit("mq_receive");
    printf("Message: %s\n", buf);

    // Close the message queue
    mq_close(mqd);
}