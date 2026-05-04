#include "../headers/manager.h"
#include "../headers/coders.h"
#include "../headers/coderalgo.h"
#include <stdio.h>
#include <unistd.h>


void show_code(int code, manager_dats *dats)
{
    if (code == 0)
        printf("\033[38;2;0;0;255mhas taken a dongle.");
    else if (code == 1)
        printf("\033[38;2;255;0;255mis compiling.");
    else if (code == 2)
        printf("\033[38;2;255;255;0mis debugging.");
    else if (code == 3)
        printf("\033[38;2;0;255;255mis refactoring.");
    else if (code == 4)
    {
        dats->burnt_out += 1;
        printf("\033[1;38;2;255mburned out.");
    }
    else if (code == 5)
        printf("\033[1;38;2;0;255mfinished their work.");
}

void queue_print(coder *user, manager_args *arg, manager_dats *dats, int code)
{
    struct timeval  currenttime;
    static long tv;
    static long tu;
    long  t;
    pthread_mutex_lock(dats->print);
    gettimeofday(&currenttime, NULL);
    if (!tv)
    {
        tv = currenttime.tv_sec;
        tu = currenttime.tv_usec;
    }
    t = (currenttime.tv_sec - tv) * 1000 + (currenttime.tv_usec - tu) / 1000;
    printf("\033[38;2;0;255;255m[%ld] ", t);
    printf("\033[38;2;0;255;0m%d ", user->id);
    show_code(code, dats);
    printf("\033[0m \n");
    if (code == 4)
        return ;
    (void)arg;
    pthread_mutex_unlock(dats->print);
}

cyclic_list *start_threads(cyclic_list *coders, cyclic_list *th, manager_dats *dats, settings set)
{
    cyclic_list *args_list;
    int             i;
    int             started;
    pthread_t       thread;
    manager_args    *args;
    struct timeval  starttime;

    args_list = create_list();
    started = coders->size * -1 + 1;
    i = 0;
    gettimeofday(&starttime, NULL);
    while (++i < coders->size && rotate_list(coders))
    {
        // TODO: proteger create, return -1 apres avoir cree
        args = make_malloc(sizeof(manager_args));
        args->started = &started;
        args->coder = coders->head->value;
        args->status = 0;
        args->managerdats = *dats;
        args->starttime = &starttime;
        args->dats = dats;
        args->set = set;
        pthread_create(&thread, NULL, coder_func, args);
        insert_back(th, thread);
        insert_back(args_list, args);
        ++started;
    }
    //gettimeofday(&starttime, NULL);
    return (args_list);
}

// 0 = run completed, 1 = burnout, -1 = error
int manager_watch(cyclic_list *Args)
{
    while (Args->size > 0 && rotate_list(Args))
    {
        if (((manager_args *)Args->head->value)->status == 2)
            return(0);
        else if (((manager_args *)Args->head->value)->status == 1)
            remove_head(Args);
    }
    printf("Reading ended");
    return (0);
}

cyclic_list *threads_launchers(settings set, manager_dats *dats)
{
    cyclic_list *Cthreads;
    cyclic_list *Ccoders;
    cyclic_list *Cdongles;
    cyclic_list *Args;
    pthread_mutex_t print;

    pthread_mutex_init(&print, NULL);
    dats->print = &print;
    Cdongles = list_dongles(set.number_of_coders);
    Ccoders = list_coders(set.number_of_coders, Cdongles);
    Cthreads = create_list();
    Args = start_threads(Ccoders, Cthreads, dats, set);
    manager_watch(Args);
    return (Cthreads);
}

int manager(settings set)
{
    manager_dats *datas;

    datas = make_malloc(sizeof(datas));
    datas->burnt_out = 0;
    datas->count = 0;
    threads_launchers(set, datas);

    return(0);
}