#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void arg_error(void)
{
    const char *error_msg = "argv[1] = Name of message queue.\n";
    fprintf(stderr, error_msg, strlen(error_msg));
    exit(1);
}

void error_output(char* msg)
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
		error_output("can not open queue\n");

	if(mq_getattr(mqd, &attr) == -1)
		error_output("can not get attributes\n");

	read_buffer = malloc(attr.mq_msgsize);
	if(read_buffer == NULL)
		error_output("the malloc failed\n");

	ssize_t bytes_read = mq_receive(mqd, read_buffer, attr.mq_msgsize, 0);
	if(bytes_read == -1)
		error_output("mq_receive failed\n");

	write(STDOUT_FILENO, read_buffer, bytes_read);

	if(mq_unlink(queue_name) == -1)
    	error_output("can not unlink\n");

	exit(EXIT_SUCCESS);
}
