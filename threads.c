#include "main.h"
#include "threads.h"
#include "coder.h"

thread  *create_thread(void *function, settings set, coder *cdr, bool *start, struct timeval *t_start)
{
    thread  *tmp;
    parg    *args;

    tmp = (thread *)malloc(sizeof(thread));
    args = (parg *)malloc(sizeof(parg));
    if (!tmp || !args)
    {
        return (NULL);
    }
    tmp->function = function;
    args->req = set;
    args->me = cdr;
    args->result = -1;
    args->start = start;
    args->t_start = t_start;
    pthread_create(&tmp->thread_id, NULL, function, args);
    tmp->result = &args->result;
    tmp->value = &tmp->thread_id;
    return (tmp);
}