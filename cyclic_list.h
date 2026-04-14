#ifndef CYCLIC_LIST
# define CYCLIC_LIST
# include "main.h"

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


typedef struct three_main
{
    cyclic_list *threads;
    cyclic_list *coders;
    cyclic_list *dongles;
}   three_main;

void        insert_back(cyclic_list *list, void *value);
void        insert_front(cyclic_list *list, void *value);
void        rotate_list(cyclic_list *list);
cyclic_list *create_list();
void        clear_list(cyclic_list *list);
void        delete_list(cyclic_list *list);
void        remove_head(cyclic_list *list);

#endif