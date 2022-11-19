#include "header.h"

int MAX_VALUE;
static volatile int buffer = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * 
runner (void *ts)
{
    struct thread_struct *strcut_ptr = ts;

    pthread_mutex_lock(&lock);
    if(buffer < MAX_VALUE)
    {
        printf("%ld:\tbuffer:%d\n", (long) pthread_self(), buffer++);
        pthread_mutex_unlock(&lock);
        strcut_ptr->counter += 1;
        runner(ts);
    }

    pthread_mutex_unlock(&lock);
    strcut_ptr->tid = pthread_self();
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
    struct thread_struct *ts = malloc(sizeof(struct thread_struct) * thread_instances);
    
    // Setting all counters to zero
    for(int i = 0; i<thread_instances; i++)
        (*(ts + i)).counter = 0; // Really unreadable way of incrementing an address without changing the pointer

    for(int i = 0; i<thread_instances; i++)
        start_thread(&thread[i], runner, ts + i);

    for(int i = 0; i<thread_instances; i++)
        join_thread(thread[i]);

    for(int i = 0; i<thread_instances; i++)
    {
        total += ts->counter;
        printf("Thread: %ld, incremented the buffer %d times.\n", (long) ts->tid, ts->counter);
        ts++; 
    }
    printf("Total buffer accesses:%d\nFinal buffer value:%d\n", total, buffer);
}

