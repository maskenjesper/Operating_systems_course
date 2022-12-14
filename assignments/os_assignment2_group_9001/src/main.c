#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "dependencies/utilities.h"

void *threadWork();

int buffer = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int main() 
{
    pthread_t tid[3];
    for (int i = 0; i < 3; i++)
        if (pthread_create(&tid[i], NULL, threadWork, NULL) != 0) errExit("pthread_create");

    int total_times_worked = 0;
    for (int i = 0; i < 3; i++)
    {
        void *result;
        if (pthread_join(tid[i], &result) != 0) errExit("pthread_join");
        int times_worked = *(int *) result;
        total_times_worked += times_worked;
        printf("TID %d worked on the buffer %d times\n", tid[i], times_worked);
        free(result);
    }
    printf("Total buffer accesses: %d\n", total_times_worked);
}

void *threadWork() 
{
    int *times_worked = calloc(1, sizeof(int));
    while (1) 
    {
        if (pthread_mutex_lock(&mtx) != 0) errExit("phtread_mutex_lock");
            if (buffer < 15)
            {
                printf("TID: %d, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
                buffer++;
            }
            else 
            {
                if (pthread_mutex_unlock(&mtx) != 0) errExit("pthread_mutex_unlock");
                break;
            }
        if (pthread_mutex_unlock(&mtx) != 0) errExit("pthread_mutex_unlock");
        (*times_worked)++;
    }
    return times_worked;
}