#include "../headers/cyclic_list.h"
#include "../headers/mallocs.h"
#include <stdlib.h>
#include <stdio.h>

void insert_back(t_cl *list, void *value)
{
	t_list_part	*new_part;
	t_list_part	*last_part;

	new_part = malloc(sizeof(t_list_part));
	new_part->value = value;
	if (list->size == 0)
	{
		new_part->next = new_part;
		new_part->previous = new_part;
		list->head = new_part;
	}
	else
	{
		last_part = list->head->previous;
		last_part->next = new_part;
		new_part->previous = last_part;
		new_part->next = list->head;
		list->head->previous = new_part;
	}
	list->size++;
}

void	insert_front(t_cl *list, void *value)
{
	insert_back(list, value);
	list->head = list->head->previous;
}

int	rotate_list(t_cl *list)
{
	if (list->size > 0)
		list->head = list->head->next;
	return (1);
}

t_cl	*create_list()
{
	t_cl	*list;

	list = make_malloc(sizeof(t_cl));
	if (!list)
		return (NULL);
	list->size = 0;
	list->head = NULL;
	return (list);
}

void	remove_head(t_cl *list)
{
	t_list_part *tmp;

	if (list->size <= 1)
	{
		clear_list(list);
		return ;
	}
	tmp = list->head;
	list->head->next->previous = list->head->previous;
	list->head->previous->next = list->head->next;
	list->head = list->head->next;
	list->size--;

	//freeing cause the time to break, to fix
	//if (tmp->value)
	//	free(tmp->value);
	//if (tmp)
	//	free(tmp);
}

void    clear_list(t_cl *list)
{
    t_list_part *tmp;
    while (list->size != 0)
    {
        tmp = list->head->next;
        free(list->head->value);
        list->head->value=NULL;
        free(list->head);
        list->head = NULL;
        list->head = tmp;
        list->size--;
    }
    list->size = 0;
    list->head = NULL;
}

void    *delete_list(t_cl *list)
{
    clear_list(list);
    free(list);
    return (NULL);
}