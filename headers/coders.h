#ifndef CODERS_H
# define CODERS_H
# include "../headers/manager.h"
# include <sys/time.h>

typedef struct dongle
{
    struct timeval last_taken;
    int            id;
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

cyclic_list *list_coders(int count, cyclic_list *dongles);
cyclic_list *list_dongles(int count);

#endif