# include <stdbool.h>
# include <stdio.h>
# include "cyclic_list.h"
# include <pthread.h>
typedef struct t_dongle
{
    bool    taken;
    int     id;
    pthread_mutex_t mutex;
    int   last_used;
}   dongle;

typedef struct t_coder
{
    int     id;
    int     status;
    int     last_compile;
    dongle    *dongle1;
    dongle    *dongle2;
}   coder;

coder   *create_coder(int id, void *right, void *left)
{
    coder *tmp;

    tmp = (coder *)malloc(sizeof(coder));
    tmp->id = id;
    tmp->dongle1 = left;
    tmp->dongle2 = right;
    tmp->status = 0;
    tmp->last_compile = 0;
    return (tmp);
}

dongle *create_dongle(int id)
{
    dongle *tmp;

    tmp = (dongle *)malloc(sizeof(dongle));
    tmp->taken = false;
    tmp->taken = false;
    tmp->last_used = 0;
    tmp->id = id;
    pthread_mutex_init(&tmp->mutex, NULL);
    return (tmp);
}