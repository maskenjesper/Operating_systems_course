#include "header.h"

int MAX_VALUE;
static volatile int buffer = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * 
runner (void *counter)
{
    unsigned int *counter_ptr;
    counter_ptr = counter;
    pthread_mutex_lock(&lock);
    if(buffer < MAX_VALUE)
    {
        printf("%ld:\tbuffer:%d\n", (long) pthread_self(), buffer++);
        pthread_mutex_unlock(&lock);
        *counter_ptr += 1;
        runner(counter);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int
main (int argc, char** argv)
{
    int thread_instances;
    int total = 0; 

    // The user can specify number of threads, or the number of threads and the max value
    (argc > 1) ? (thread_instances = atoi(argv[1])) : (thread_instances = 3);
    (argc > 2) ? (MAX_VALUE = atoi(argv[2])) : (MAX_VALUE = 15);

    pthread_t thread[thread_instances];
    unsigned int *counters = calloc(thread_instances, sizeof(int));
    
    for(int i = 0; i<thread_instances; i++)
        start_thread(&thread[i], runner, counters + i);

    for(int i = 0; i<thread_instances; i++)
        join_thread(thread[i]);

    for(int i = 0; i<thread_instances; i++)
    {
        printf("Thread: %ld, incremented the buffer %u times.\n", (long) thread[i], *counters);
        total += *counters++;
    }
    printf("Total buffer accesses:%d\nFinal buffer value:%d\n", total, buffer);
}

