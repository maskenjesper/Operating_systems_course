#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utilities.h"

int count_words(char* buf, int len)
{
	int word_count = 0;
    for (int i = 0; i < len-1; i++) 
        if ((buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') && !(buf[i+1] == ' ' || buf[i+1] == '\n' || buf[i+1] == '\t')) 
            word_count++;
    if (!(buf[len] == ' ' || buf[len] == '\n' || buf[len] == '\t'))
        word_count++;

	return word_count;
}

/**
 * argv[1] = name of message queue.
 **/
int main(int argc, char** argv)
{
	if(argc != 2)
	    errExit("Bad arguments\nargv[1] = Name of message queue.\n");

	const char *mq_name = argv[1];
	mqd_t mqd;
	char *read_buffer;
	struct mq_attr attr;
	int flags = O_RDONLY;

	mqd = mq_open(mq_name, flags);
	if(mqd == -1)
	    errExit("can not open queue\n");

	if(mq_getattr(mqd, &attr) == -1)
	    errExit("can not get attributes\n");

	read_buffer = malloc(attr.mq_msgsize * sizeof(char));
	if(read_buffer == NULL)
	    errExit("the malloc failed\n");

	ssize_t bytes_read = mq_receive(mqd, read_buffer, attr.mq_msgsize, 0);
	if(bytes_read == -1)
	    errExit("mq_receive failed\n");

	if(mq_close(mqd) == -1)
		errExit("cannot close mq\n");

	if(mq_unlink(mq_name) == -1)
    	errExit("can not unlink\n");

	printf("words: %d\n", count_words(read_buffer, bytes_read));
    free(read_buffer);
}
