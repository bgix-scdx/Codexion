#include "../headers/cyclic_list.h"
#include <stdlib.h>
#include <stdio.h>

void insert_back(cyclic_list *list, void *value)
{
    list_part *new_part;
    list_part *last_part;

    new_part = (list_part *)malloc(sizeof(list_part));
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

void insert_front(cyclic_list *list, void *value)
{
    insert_back(list, value);
    list->head = list->head->previous;
}

int rotate_list(cyclic_list *list)
{
    if (list->size > 0)
        list->head = list->head->next;
    return (1);
}

cyclic_list *create_list()
{
    cyclic_list *list;

    list = (cyclic_list *)malloc(sizeof(cyclic_list));
    list->size = 0;
    list->head = NULL;
    return (list);
}

void    remove_head(cyclic_list *list)
{
    //list_part *tmp;

    if (list->size <= 1)
    {
        clear_list(list);
        return;
    }
    //tmp = list->head;
    list->head->next->previous = list->head->previous;
    list->head->previous->next = list->head->next;
    list->head = list->head->next;
    list->size--;

    // freeing cause the time to break, to fix
    //free(tmp->value);
    //free(tmp);
}

void    clear_list(cyclic_list *list)
{
    list_part *tmp;
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

void    *delete_list(cyclic_list *list)
{
    clear_list(list);
    free(list);
    return (NULL);
}