#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../utilities.h"

/**
 * argv[1] = text to read from.
 * argv[2] = size of text.
 * argv[3] = name of message queue.
 **/
int main(int argc, char** argv)
{
    if(argc != 4)
    errExit("Bad arguments\nargv[1] = text file to read from.\nargv[2] = size of text.\nargv[3] = name of message queue.\n");

    const char *text_name = argv[1];
    int text_size = atoi(argv[2]);
    const char *mq_name = argv[3];

    char buffer[text_size];
    int fd = open(text_name, O_RDONLY);
    ssize_t read_bytes = read(fd, buffer, text_size);

    mqd_t mqd;
    int flags = O_RDWR | O_CREAT;
    mode_t perm = 777;
    struct mq_attr *attr_ptr;
    attr_ptr = NULL;

    mqd = mq_open(mq_name, flags, perm, attr_ptr);
    if(mqd == -1)
        errExit("can not open message queue");	

    if(mq_send(mqd, buffer, read_bytes, 0) == -1)
        errExit("can not send msg");
}
