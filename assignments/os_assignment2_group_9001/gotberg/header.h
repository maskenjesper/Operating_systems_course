#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

extern pthread_t tid[];
void handle_error(char*, int);
void start_thread(pthread_t *, void *(func)(void *), int *);
void join_thread(pthread_t);

