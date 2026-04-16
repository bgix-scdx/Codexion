#include "../headers/cyclic_list.h"
#include "../headers/mallocs.h"
#include <stdio.h>

void    *make_malloc(long size)
{
    static cyclic_list *malloc_list;
    void *tmp;

    if (size == -1 && malloc_list)
        return (delete_list(malloc_list));
    else if (!malloc_list)
    {
        malloc_list = create_list();
        if (!malloc_list)
            return (NULL);
    }
    tmp = malloc(size);
    if (!tmp)
        return (NULL);
    insert_back(malloc_list, tmp);
    return (tmp);
}
