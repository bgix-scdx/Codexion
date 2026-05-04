#ifndef t_coderS_H
# define t_coderS_H
# include "../headers/manager.h"
# include <sys/time.h>
# include <time.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct t_dongle
{
	struct	timeval	last_taken;
	int				id;
	bool			taken;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct t_coder
{
	int			status;
	int			finished;
	int			started;
	int			id;
	t_dongle	*d1;
	t_dongle	*d2;
}	t_coder;

typedef struct t_coder_arg
{
	t_md		*dats;
	t_dongle	*dong1;
	t_dongle	*dong2;
}	t_coder_arg;

typedef struct t_ma
{
	int				*started;
	t_coder			*t_coder;
	struct timeval	*starttime;
	t_md			managerdats;
	int				status;
	t_md			*dats;
	t_settings		set;
}	t_ma;

void	queue_print(t_coder *user, t_ma *arg, t_md *dats, int code);
t_cl    *list_t_coders(int count, t_cl *t_dongles);
t_cl    *list_t_dongles(int count);

#endif