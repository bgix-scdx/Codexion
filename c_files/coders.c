#include "../headers/coders.h"

coder       *make_coder(int id, cyclic_list *dongles)
{
    coder   *tmp;

    tmp = make_malloc(sizeof(coder));
    tmp->status = 0;
    tmp->started = 0;
    tmp->finished = 0;
    tmp->id = id;
    tmp->d1 = dongles->head->value;
    tmp->d2 = dongles->head->next->value;
    return (tmp);
}

cyclic_list *list_coders(int count, cyclic_list *dongles)
{
    cyclic_list *coders;
    int         i;

    i = -1;
    coders = create_list();
    while (++i < count && rotate_list(dongles))
        insert_front(coders, make_coder(i, dongles));
    return (coders);
}

dongle  *make_dongle(int id)
{
    dongle *tmp;

    tmp = make_malloc(sizeof(dongle));
    tmp->id = id;
    tmp->taken = false;
    pthread_mutex_init(&tmp->mutex, NULL);
    return (tmp);
}

cyclic_list *list_dongles(int count)
{
    cyclic_list *tmp;
    int         i;

    tmp = create_list();
    i = -1;
    while (++i < count)
        insert_back(tmp, make_dongle(i));
    return (tmp);
}