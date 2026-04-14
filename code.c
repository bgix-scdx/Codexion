#include "main.h"
#include "coder.h"
#include "threads.h"

void    status(coder *me, struct timeval start, int code)
{
    
    struct timeval  t_now;
    int             t;

    gettimeofday(&t_now, NULL);
    t = (start.tv_usec - t_now.tv_usec) * -1;
    printf("%d\n", t);
    // if (code == 0)
    //     printf("%d %d took a dongle1\n", t_now.tv_usec - start.tv_usec, me->id);
    // if (code == 1)
    //     printf("%d %d took a dongle2\n", t_now.tv_usec - start.tv_usec, me->id);
    // else if (code == 2)
    //     printf("%d %d is compiling.\n", t_now.tv_usec - start.tv_usec, me->id);
    // else if (code == 3)
    //     printf("%d %d is debugging.\n", t_now.tv_usec - start.tv_usec, me->id);
    // else if (code == 4)
    //     printf("%d %d is refactoring.\n", t_now.tv_usec - start.tv_usec, me->id);
    (void)me;
    (void)code;
}
void    fifo(coder *me, struct timeval start)
{
    if (me->dongle1->taken == false)
    {
        status(me, start, 0);
        me->dongle1->taken = true;
        pthread_mutex_lock(&me->dongle1->mutex);
    }
    if (me->dongle2->taken == false)
    {
        status(me, start, 1);
        me->dongle2->taken = true;
        pthread_mutex_lock(&me->dongle2->mutex);
    }
    return;
}

void    handle_coder(parg *args)
{
    coder       *me;
    settings    conditions;
    struct timeval  start_tv;
    struct timeval  loop_tv;
    struct timeval  new_tv;

    while (*args->start == false){usleep(100);}

    me = args->me;
    conditions = args->req;
    gettimeofday(&new_tv, NULL);
    gettimeofday(&loop_tv, NULL);
    start_tv = *args->t_start;
    while (me->compilation < conditions.number_of_compiles_required)
    {
        status(me, start_tv, 3);
        usleep(conditions.time_to_debug);
        status(me, start_tv, 4);
        usleep(conditions.time_to_refactor);
        gettimeofday(&new_tv, NULL);
        fifo(me, start_tv);
        gettimeofday(&loop_tv, NULL);
        if ((loop_tv.tv_usec - new_tv.tv_usec) >= conditions.time_to_burnout)
        {
            printf("\033[38;2;255m - %d has burnt out after %d (%d)ms\n\033[0m", me->id, (loop_tv.tv_usec - new_tv.tv_usec), conditions.time_to_burnout);
            pthread_mutex_unlock(&me->dongle1->mutex);
            pthread_mutex_unlock(&me->dongle2->mutex);
            args->result = 1;
            pthread_exit(NULL);
        }
        status(me, start_tv, 2);
        usleep(conditions.time_to_compile);
        me->dongle1->taken = false;
        me->dongle1->taken = true;
        pthread_mutex_unlock(&me->dongle1->mutex);
        pthread_mutex_unlock(&me->dongle2->mutex);
        me->compilation++;
    }
    printf("\033[38;2;0;255mCoder %d finished his session.\n\033[0m", me->id);
    args->result = 0;
    pthread_exit(NULL);
}