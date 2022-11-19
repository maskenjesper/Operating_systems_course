#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct thread_struct
{
    int counter;
    pthread_t tid;
};

void start_thread(pthread_t *, void *(func)(void *), struct thread_struct *);
void join_thread(pthread_t);

