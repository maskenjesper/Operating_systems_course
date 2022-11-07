#include <stdio.h>
#include <unistd.h>
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
    ssize_t len = mq_receive(mqd, buf, MAX_SIZE, NULL);
    if (len == -1) errExit("mq_receive");
    printf("Message: %s\n", buf);

    // Count number of words
    int word_count = 0;
    for (int i = 0; i < len-1; i++) 
        if ((buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') && (buf[i+1] != ' ' || buf[i+1] != '\n' || buf[i+1] != '\t'))
            word_count++;
    if (buf[len] != ' ' || buf[len] != '\n' || buf[len] != '\t' )
        word_count++;
        
    printf("Word count: %d\n", word_count);

    mq_unlink(my_mq);

    // Close the message queue
    mq_close(mqd);
}