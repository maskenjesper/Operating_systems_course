#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../utilities.h"

int count_words(char* buffer, int length)
{
	int i;
	int words = 0;
	for(i = 0; i < length-2; i++)
	{
	    if( (buffer[i] != ' ' && buffer[i+1] == ' ' && buffer[i+2] != ' ') || (buffer[i+2] == '\n' && i != length-3) )
		words++;
	}
	return ++words;
	
}
void arg_error(void)
{
    const char *error_msg = "argv[1] = Name of message queue.\n";
    fprintf(stderr, error_msg, strlen(error_msg));
    exit(1);
}

void errExit(char* msg)
{
    fprintf(stderr, msg, strlen(msg));
    exit(1);
}

/**
 * argv[1] = name of message queue.
 **/
int main(int argc, char** argv)
{
	if(argc != 2)
	    arg_error();

	const char *queue_name = argv[1];
	mqd_t mqd;	
	void *read_buffer;
	struct mq_attr attr;
	int flags = O_RDONLY;

	mqd = mq_open(queue_name, flags);
	if(mqd == -1)
	    errExit("can not open queue\n");

	if(mq_getattr(mqd, &attr) == -1)
	    errExit("can not get attributes\n");

	read_buffer = malloc(attr.mq_msgsize);
	if(read_buffer == NULL)
	    errExit("the malloc failed\n");

	ssize_t bytes_read = mq_receive(mqd, read_buffer, attr.mq_msgsize, 0);
	if(bytes_read == -1)
	    errExit("mq_receive failed\n");

	if(mq_unlink(queue_name) == -1)
    	    errExit("can not unlink\n");

	printf("words: %d\n", count_words(read_buffer, bytes_read));
	exit(EXIT_SUCCESS);
}
