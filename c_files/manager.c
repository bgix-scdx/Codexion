#include "../headers/manager.h"
#include "../headers/coders.h"

cyclic_list *threads_launchers(settings set, manager_dats *dats)
{
    cyclic_list *Cthreads;
    cyclic_list *Ccoders;
    cyclic_list *Cdongles;
    coder_arg   args;

    args.dats = dats;
    Cdongles = list_dongles(set.number_of_coders);
    Ccoders = list_coders(set.number_of_coders, Cdongles);
    Cthreads = create_list();
    
    (void)Ccoders;
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