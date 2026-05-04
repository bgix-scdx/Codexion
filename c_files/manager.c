#include "../headers/manager.h"
#include "../headers/coders.h"
#include "../headers/coderalgo.h"
#include <stdio.h>
#include <unistd.h>


void show_code(int code, t_md *dats)
{
	if (code == 0)
		printf("\033[38;2;0;0;255mhas taken a t_dongle.");
	else if (code == 1)
		printf("\033[38;2;255;0;255mis compiling.");
	else if (code == 2)
		printf("\033[38;2;255;255;0mis debugging.");
	else if (code == 3)
		printf("\033[38;2;0;255;255mis refactoring.");
	else if (code == 6)
		printf("\033[38;2;0;255;255mhas taken a t_dongle.");
	else if (code == 4)
	{
		dats->burnt_out += 1;
		printf("\033[1;38;2;255mburned out.");
	}
	else if (code == 5)
		printf("\033[1;38;2;0;255mfinished their work.");
}

void	queue_print(t_coder *user, t_ma *arg, t_md *dats, int code)
{
	struct timeval	currenttime;
	static int		stop;
	static long		tv;
	static long		tu;
	long			t;

	pthread_mutex_lock(dats->print);
	if ((arg->status == 2 && code != 4 ) || stop != 0)
		return ((void)pthread_mutex_unlock(dats->print));
	gettimeofday(&currenttime, NULL);
	if (!tv)
	{
		tv = currenttime.tv_sec;
		tu = currenttime.tv_usec;
		stop = 0;
	}
	t = (currenttime.tv_usec - tu) / 1000 + (currenttime.tv_sec - tv) * 1000;
	printf("\033[38;2;0;255;255m[%ld]", t);
	printf("\033[38;2;0;255;0m%d ", user->id);
	show_code(code, dats);
	printf("\033[0m \n");
	if (code == 4)
		stop = 1;
	pthread_mutex_unlock(dats->print);
}

t_cl	*start_threads(t_cl *t_coders, t_cl *th, t_md *dats, t_settings set)
{
	t_cl				*args_list;
	t_ts				ts;
	t_ma				*args;

	args_list = create_list();
	ts.started = t_coders->size * -1 + 1;
	ts.i = 0;
	while (++ts.i <= t_coders->size && rotate_list(t_coders))
	{
		args = make_malloc(sizeof(t_ma));
		if (!args)
			return (NULL);
		args->started = &ts.started;
		args->t_coder = t_coders->head->value;
		args->status = 0;
		args->managerdats = *dats;
		args->dats = dats;
		args->set = set;
		pthread_create(&ts.thread, NULL, t_coder_func, args);
		insert_back(th, &ts.thread);
		insert_back(args_list, args);
		++ts.started;
	}
	return (args_list);
}

// 0 = run completed, 1 = burnout, -1 = error
void	threads_launchers(t_settings set, t_md *dats)
{
	t_cl			*cthreads;
	t_cl			*ct_coders;
	t_cl			*ct_dongles;
	t_cl			*args;
	pthread_mutex_t	print;

	pthread_mutex_init(&print, NULL);
	dats->print = &print;
	ct_dongles = list_t_dongles(set.number_of_coders);
	ct_coders = list_t_coders(set.number_of_coders, ct_dongles);
	cthreads = create_list();
	args = start_threads(ct_coders, cthreads, dats, set);
	if (!args || !ct_dongles || !ct_coders || !cthreads)
		return ;
	while (args->size > 0 && rotate_list(args))
	{
		if (((t_ma *)args->head->value)->status == 2)
			return ;
		else if (((t_ma *)args->head->value)->status == 1)
			remove_head(args);
	}
}

int	manager(t_settings set)
{
	t_md	*datas;

	datas = make_malloc(sizeof(t_md));
	datas->burnt_out = 0;
	datas->count = 0;
	threads_launchers(set, datas);
	make_malloc(-1);
	return (0);
}
