#ifndef MANAGER_H
# define MANAGER_H
# include <pthread.h>
# include "../headers/cyclic_list.h"
# include "../headers/mallocs.h"
# include "../codexion.h"

typedef struct manager_dats
{
    int count;
    int *burnt_out;
    pthread_mutex_t *print;
} manager_dats;

cyclic_list *threads_launchers(settings set, manager_dats *dats);
int manager(settings set);

#endif