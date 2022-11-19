#include "header.h"

static volatile int buffer = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * 
runner (void *ts)
{
    struct thread_struct *strcut_ptr = ts;


    pthread_mutex_lock(&lock);
    if(buffer < 15)
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
    int total = 0; 
    pthread_t thread[3];
    struct thread_struct *ts = malloc(sizeof(struct thread_struct) * 3);
    
    // Set all counters to zero
    for(int i = 0; i<3; i++)
    {
        ts->counter = 0;
        ts++;
    }

    // Reset the pointer to first address
    ts += -3; 

    for(int i = 0; i<3; i++)
        start_thread(&thread[i], runner, ts + i);

    for(int i = 0; i<3; i++)
        join_thread(thread[i]);

    for(int i = 0; i<3; i++)
    {
        total += ts->counter;
        printf("Thread: %ld, incremented the buffer %d times.\n", (long) ts->tid, ts->counter);
        ts++;
    }
    printf("Total buffer accesses:%d\nFinal buffer value:%d\n", total, buffer);
}

