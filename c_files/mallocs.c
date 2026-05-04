#include "../headers/cyclic_list.h"
#include "../headers/mallocs.h"
#include <stdio.h>

void	*make_malloc(long size)
{
	static t_cl	*malloc_list;
	void		*tmp;

	if (size == -1 && malloc_list)
		return (delete_list(malloc_list));
	else if (!malloc_list)
	{
		malloc_list = (t_cl *)malloc(sizeof(t_cl));
		if (!malloc_list)
			return (NULL);
		malloc_list->size = 0;
		malloc_list->head = NULL;
	}
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	insert_back(malloc_list, tmp);
	return (tmp);
}
