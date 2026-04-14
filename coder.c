#include "coder.h"
#include "main.h"

coder	*create_coder(int id, void *right, void *left)
{
	coder	*tmp;

	tmp = (coder *)malloc(sizeof(coder));
    if (!tmp)
    {
        return (NULL);
    }
	tmp->id = id;
	tmp->dongle1 = left;
	tmp->dongle2 = right;
	tmp->status = 0;
	tmp->compilation = 0;
	//tmp->last_compile = *(struct timeval *)malloc(sizeof(struct timeval));
	return (tmp);
}

dongle	*create_dongle(int id)
{
	dongle *tmp;

	tmp = (dongle *)malloc(sizeof(dongle));
	tmp->taken = false;
	tmp->last_used = 0;
	tmp->id = id;
	pthread_mutex_init(&tmp->mutex, NULL);
	return (tmp);
}