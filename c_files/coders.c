#include "../headers/coders.h"

t_coder	*make_t_coder(int id, t_cl *dongles)
{
	t_coder	*tmp;

	tmp = make_malloc(sizeof(t_coder));
	tmp->status = 0;
	tmp->started = 0;
	tmp->finished = 0;
	tmp->id = id;
	tmp->d1 = dongles->head->value;
	tmp->d2 = dongles->head->next->value;
	return (tmp);
}

t_cl	*list_t_coders(int count, t_cl *dongles)
{
	t_cl	*t_coders;
	int		i;

	i = -1;
	t_coders = create_list();
	while (++i < count && rotate_list(dongles))
		insert_front(t_coders, make_t_coder(i, dongles));
	return (t_coders);
}

t_dongle	*make_dongle(int id)
{
	t_dongle	*tmp;

	tmp = make_malloc(sizeof(t_dongle));
	tmp->id = id;
	tmp->taken = false;
	tmp->last_taken.tv_usec = 0;
	pthread_mutex_init(&tmp->mutex, NULL);
	return (tmp);
}

t_cl	*list_t_dongles(int count)
{
	t_cl	*tmp;
	int		i;

	tmp = create_list();
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < count)
		insert_back(tmp, make_dongle(i));
	return (tmp);
}