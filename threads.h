#ifndef THREADS_H
# define THREADS_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_thread{
    pthread_t thread_id;
    void (*function)(void *);
    void *value;
} thread;

thread create_thread(void *function, void *value)
{
    thread tmp;

    tmp = *(thread *)malloc(sizeof(thread));
    tmp.function = function;
    tmp.value = value;
    pthread_create(&tmp.thread_id, NULL, (void *(*)(void *))function, value);
    return (tmp);
}

#endif