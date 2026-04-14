#ifndef THREADS_H
# define THREADS_H
# include "coder.h"
# include "main.h"

typedef struct s_thread{
    pthread_t   thread_id;
    void        (*function)(parg);
    void        *value;
    int         *result;
} thread;

thread      *create_thread(void *function, settings set, coder *cdr, bool *start, struct timeval *t_start);

#endif