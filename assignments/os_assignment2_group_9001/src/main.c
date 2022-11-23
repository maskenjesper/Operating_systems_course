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

    void *times_worked;
    int total_times_worked = 0;
    for (int i = 0; i < 3; i++)
    {
        if (pthread_join(tid[i], &times_worked) != 0) errExit("pthread_join");
        total_times_worked += (int) times_worked;
        printf("TID %d worked on the buffer %d times\n", tid[i], (int) times_worked);
    }
    printf("Total buffer accesses: %d\n", total_times_worked);
}

void *threadWork() 
{
    int times_worked = 0;
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
        times_worked++;
    }
    return times_worked;
}