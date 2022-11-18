#include "header.h"

void 
handle_error (char* msg, int error_code)
{
    fprintf(stderr, "ERROR: %s\t%d\n", msg, error_code);
    exit(error_code);
}

void 
start_thread (pthread_t *thread, void *(*func)(void *), int *counter)
{
    
    int return_value;
    return_value = pthread_create(thread, NULL, func,  counter);
    if(return_value != 0)
        handle_error("start_thread:", return_value);
}

void 
join_thread (pthread_t thread)
{
    int return_value;
    return_value = pthread_join(thread, NULL);
    if(return_value != 0)
        handle_error("join_thread:", return_value);
}
