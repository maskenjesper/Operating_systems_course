#include "header.h"

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
    pthread_t thread_1, thread_2, thread_3;

    start_thread(&thread_1, runner, counter);
    start_thread(&thread_2, runner, counter + 1);
    start_thread(&thread_3, runner, counter + 2);

    join_thread(&thread_1);
    join_thread(&thread_2);
    join_thread(&thread_3);

    printf("thread_1: %d\n", *counter);
    printf("thread_2: %d\n", *(counter + 1));
    printf("thread_3: %d\n", *(counter + 2));
    int total = *counter + *(counter + 1) + *(counter + 2);
    printf("Total:%d\nValue:%d\n", total, buffer);

    // return zero;
}

