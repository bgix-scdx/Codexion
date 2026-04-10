#ifndef CYCLIC_LIST
# define CYCLIC_LIST
# include <stdlib.h> 
# include <stdio.h>
# include "coder.h"

typedef struct list_part
{
    void *value;
    struct list_part *next;
    struct list_part *previous;
} list_part;

typedef struct cyclic_list
{
   int size;
   list_part *head;
} cyclic_list;

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

void rotate_list(cyclic_list *list)
{
    if (list->size > 0)
        list->head = list->head->next;
}

cyclic_list *create_list()
{
    cyclic_list *list;

    list = (cyclic_list *)malloc(sizeof(cyclic_list));
    list->size = 0;
    list->head = NULL;
    return (list);
}

void    clear_list(cyclic_list *list)
{
    list_part *tmp;

    while (list->size != 0)
    {
        tmp = list->head->next;
        free(list->head->value);
        free(list->head);
        list->head = tmp;
        list->size--;
    }
    list->head = NULL;
}

void    delete_list(cyclic_list *list)
{
    clear_list(list);
    free(list);
}

#endif