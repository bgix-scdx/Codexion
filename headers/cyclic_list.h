#ifndef CYCLIC_LIST
# define CYCLIC_LIST

typedef struct t_list_part
{
	void				*value;
	struct t_list_part	*next;
	struct t_list_part	*previous;
}	t_list_part;

typedef struct t_cl
{
	int			size;
	t_list_part	*head;
}	t_cl;


void			insert_back(t_cl *list, void *value);
void			insert_front(t_cl *list, void *value);
int				rotate_list(t_cl *list);
t_cl			*create_list(void);
void			clear_list(t_cl *list);
void			*delete_list(t_cl *list);
void			remove_head(t_cl *list);

#endif