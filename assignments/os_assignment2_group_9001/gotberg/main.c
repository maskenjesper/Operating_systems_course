#include "header.h"

pthread_t tid[3];
static volatile int buffer = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * 
runner (void *counter)
{
    int *ptr = (int *) counter;
    printf("%ld:\tbuffer:%d\n", (long) pthread_self(), buffer);

    pthread_mutex_lock(&lock);
    if(buffer < 15)
    {
        buffer++;
        pthread_mutex_unlock(&lock);
        *ptr += 1;
        runner(counter);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int
main (int argc, char** argv)
{
    int *counter = malloc(sizeof(int) * 3);
    *counter = *(counter + 1) = *(counter + 2) = 0;
    pthread_t thread[3];

    for(int i = 0; i<3; i++)
        start_thread(&thread[i], runner, counter + i);

    for(int i = 0; i<3; i++)
        join_thread(thread[i]);

    for(int i = 0; i<3; i++)
        printf("Thread nr %d, incremented the buffer %d times.\n", i, *(counter + i));

    int total = *counter + *(counter + 1) + *(counter + 2);
    printf("Total buffer accesses:%d\nFinal buffer value:%d\n", total, buffer);
}

