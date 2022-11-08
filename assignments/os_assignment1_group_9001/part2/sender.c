#include <mqueue.h>
#include <unistd.h>
#include <sys/stat.h>
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

    const char *file_name = argv[1];
    int buffer_size = atoi(argv[2]);
    const char *mq_name = argv[3];

    char buffer[buffer_size];
    int fd = open(file_name, O_RDONLY);
    ssize_t read_bytes = read(fd, buffer, buffer_size);
    close(fd);

    mqd_t mqd;
    int flags = O_RDWR | O_CREAT;
    mode_t perm = S_IRUSR | S_IWUSR;
    struct mq_attr attr_ptr;
    attr_ptr.mq_maxmsg = 1;
    attr_ptr.mq_msgsize = read_bytes;

    mqd = mq_open(mq_name, flags, perm, &attr_ptr);
    if(mqd == -1)
        errExit("can not open message queue");	

    if(mq_send(mqd, buffer, read_bytes, 0) == -1)
        errExit("can not send msg");

    if(mq_close(mqd) == -1)
        errExit("cannot close mq");
}
