#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void handle_error(int);
void start_thread(pthread_t *, void *(func)(void *), int *);
void join_thread(pthread_t *);

