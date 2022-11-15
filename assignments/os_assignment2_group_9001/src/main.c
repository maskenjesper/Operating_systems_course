#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "dependencies/utilities.h"

int buffer = 0;
void *threadWork();
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int main() 
{
    pthread_t tid[3];
    pthread_attr_t attr[3];
    for (int i = 0; i < 3; i++) 
    {
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i], &attr[i], threadWork, NULL);
    }

    void *times_worked[] = {0, 0, 0};
    int total_times_worked = 0;
    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], &times_worked[i]);
        total_times_worked += (int) times_worked[i];
        printf("TID %d worked on the buffer %d times\n", tid[i], (int) times_worked[i]);
    }
    printf("Total buffer accesses: %d\n", total_times_worked);

}

void *threadWork() 
{
    int times_worked = 0;
    int running = 1;
    while (running) 
    {
        pthread_mutex_lock(&mtx);

        if (buffer < 15)
        {
            printf("TID: %d, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
            buffer++;
            times_worked++;
        }
        else 
            running = 0;

        pthread_mutex_unlock(&mtx);
    }
    return times_worked;
}