#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void start_thread(pthread_t *, void *(func)(void *), unsigned int *);
void join_thread(pthread_t);

