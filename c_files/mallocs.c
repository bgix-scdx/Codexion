#include "../headers/cyclic_list.h"
#include "../headers/mallocs.h"
#include <stdio.h>

void    *make_malloc(unsigned long size)
{
    static cyclic_list *malloc_list;
    void *tmp;

    if (size == 0 && malloc_list)
        return (delete_list(malloc_list));
    else if (!malloc_list)
    {
        malloc_list = (cyclic_list *)malloc(sizeof(cyclic_list));
        malloc_list->head = NULL;
        malloc_list->size = 0;
        if (!malloc_list)
            return (NULL);
    }
    tmp = malloc(size);
    if (!tmp)
        return (NULL);
    insert_back(malloc_list, tmp);
    return (tmp);
}
