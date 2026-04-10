# include <stdbool.h>
# include <stdio.h>
# include "cyclic_list.h"

typedef struct t_dongle
{
    bool    taken;
    int     id;
    float   *last_used;
}   dongle;

typedef struct t_coder
{
    int     id;
    int     status;
    float   last_compile;
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
    tmp->last_used = (float *)malloc(sizeof(float));
    tmp->taken = false;
    *tmp->last_used = 0.0;
    tmp->id = id;
    return (tmp);
}