#include "../headers/coders.h"
#include <unistd.h>

void    get_dongles(coder *user, manager_args *arg, settings set)
{
    bool dong1;
    bool dong2;
    struct timeval tmp;
    int started;
    int t;

    t = 0;
    dong1 = false;
    dong2 = false;
    gettimeofday(&tmp, NULL);
    started = tmp.tv_usec;
    while ((dong1 == false || dong2 == false) && t < set.time_to_burnout)
    {
        if (((dongle *)user->d1)->taken == false && dong1 == false)
        {
            dong1 = true;
            user->d1->taken = true;
            queue_print(user, arg, arg->dats, 0);
        }
        if (((dongle *)user->d2)->taken == false && dong2 == false)
        {
            dong2 = true;
            user->d2->taken = true;
            queue_print(user, arg, arg->dats, 0);
        }
        gettimeofday(&tmp, NULL);
        t = tmp.tv_usec - started;
        //printf("[%d / %d]", t, set.time_to_burnout);
    }
    if (dong1 == false || dong2 == false)
    {
        queue_print(arg->coder, arg, arg->dats, 4);
        arg->status = 2;
        return;
    }
    pthread_mutex_lock(&user->d1->mutex);
    pthread_mutex_lock(&user->d2->mutex);
    queue_print(arg->coder, arg, arg->dats, 1);
    usleep(set.time_to_compile);
    user->d2->taken = false;
    user->d1->taken = false;
    pthread_mutex_unlock(&user->d1->mutex);
    pthread_mutex_unlock(&user->d2->mutex);
}


void    *coder_func(void *args)
{   
    manager_args    *arg;
    int             compiles;
    settings        set;
    compiles = 0;
    arg = (manager_args *)args;
    set = arg->set;
    while (*arg->started < 0)
        usleep(0);
    while (10 > ++compiles && arg->status == 0)
    {
        get_dongles(arg->coder, arg, set);
        if (arg->status == 2)
            pthread_exit(0);
        queue_print(arg->coder, arg, arg->dats, 2);
        usleep(set.time_to_debug);
        queue_print(arg->coder, arg, arg->dats, 3);
        usleep(set.time_to_refactor);
    }
    queue_print(arg->coder, arg, arg->dats, 5);
    ((manager_args *)args)->status = 1;
    pthread_exit(0);
}