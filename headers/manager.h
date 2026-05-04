#ifndef MANAGER_H
# define MANAGER_H
# include <pthread.h>
# include "../headers/cyclic_list.h"
# include "../headers/mallocs.h"
# include "../codexion.h"

typedef struct t_md
{
	int				count;
	int				*burnt_out;
	pthread_mutex_t	*print;
}	t_md;

typedef struct t_ts
{
	int					i;
	int					started;
	unsigned long		thread;
}	t_ts;



void	threads_launchers(t_settings set, t_md *dats);
int		manager(t_settings set);

#endif