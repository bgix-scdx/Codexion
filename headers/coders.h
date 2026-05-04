#ifndef CODERS_H
# define CODERS_H
# include "../headers/manager.h"
# include <sys/time.h>
# include <time.h>
# include <stdio.h>
# include <stdbool.h>

struct timeval;

typedef struct dongle
{
    struct timeval last_taken;
    int            id;
    bool           taken;
    pthread_mutex_t mutex;
} dongle;

typedef struct coder
{
    int     status;
    int     finished;
    int     started;
    int     id;
    dongle  *d1;
    dongle  *d2;
} coder;

typedef struct coder_arg
{
    manager_dats *dats;
    dongle       *dong1;
    dongle       *dong2;
} coder_arg;

typedef struct manager_args
{
    int             *started;
    coder           *coder;
    struct timeval  *starttime;
    manager_dats    managerdats;
    int             status;
    manager_dats    *dats;
    settings        set;
} manager_args;

void queue_print(coder *user, manager_args *arg, manager_dats *dats, int code);
cyclic_list *list_coders(int count, cyclic_list *dongles);
cyclic_list *list_dongles(int count);

#endif