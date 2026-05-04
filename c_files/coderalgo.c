#include "../headers/coders.h"
#include <unistd.h>
#include <stdio.h>

void	wait_for_dongles(t_coder *user, t_ma *arg, t_settings set, int started)
{
	bool			dong1;
	bool			dong2;
	int				t;
	struct timeval	tmp;
	int				s;

	gettimeofday(&tmp, NULL);
	t = 0;
	s = tmp.tv_usec * 1000;
	dong1 = false;
	dong2 = false;
	while ((dong1 == false || dong2 == false) && arg->status == 0
			&& (tmp.tv_usec - started) < set.time_to_burnout)
	{
		printf("1: %ld: %d\n", (s - user->d2->last_taken.tv_usec * 1000) ,set.dongle_cooldown);
		printf("2: %ld: %d\n", (s - user->d1->last_taken.tv_usec * 1000) ,set.dongle_cooldown);
		if (((t_dongle *)user->d1)->taken == false && dong1 == false &&
			((t_dongle *)user->d2)->taken == false && dong2 == false &&
			(started - user->d1->last_taken.tv_usec) >= set.dongle_cooldown && 
			(started - user->d2->last_taken.tv_usec) >= set.dongle_cooldown)
		{
			user->d1->taken = true;
			user->d2->taken = true;
			dong1 = true;
			dong2 = true;
			queue_print(user, arg, arg->dats, 0);
			queue_print(user, arg, arg->dats, 6);
		}
		else if (((t_dongle *)user->d1)->taken == false && dong1 == false &&
			(tmp.tv_usec - user->d1->last_taken.tv_usec) >= set.dongle_cooldown)
		{
			dong1 = true;
			user->d1->taken = true;
			queue_print(user, arg, arg->dats, 0);
		}
		else if (((t_dongle *)user->d2)->taken == false && dong2 == false &&
			(tmp.tv_usec - user->d2->last_taken.tv_usec) >= set.dongle_cooldown)
		{
			dong2 = true;
			user->d2->taken = true;
			queue_print(user, arg, arg->dats, 6);
		}
		gettimeofday(&tmp, NULL);
		usleep(1);
		s = tmp.tv_usec / 1000;
		t = tmp.tv_usec - started;
	}
	if (dong1 == false || dong2 == false)
	{
		queue_print(user, arg, arg->dats, 4);
		arg->status = 2;
	}
}

void	get_t_dongles(t_coder *user, t_ma *arg, t_settings set)
{
	struct timeval	tmp;
	int		started;
	long			t;

	t = 0;
	gettimeofday(&tmp, NULL);
	started = tmp.tv_usec;
	wait_for_dongles(user, arg, set, started);
	pthread_mutex_lock(&user->d1->mutex);
	pthread_mutex_lock(&user->d2->mutex);
	queue_print(arg->t_coder, arg, arg->dats, 1);
	usleep(set.time_to_compile);
	gettimeofday(&tmp, NULL);
	user->d1->last_taken.tv_usec = tmp.tv_usec;
	user->d2->last_taken.tv_usec = tmp.tv_usec;
	user->d2->taken = false;
	user->d1->taken = false;
	pthread_mutex_unlock(&user->d1->mutex);
	pthread_mutex_unlock(&user->d2->mutex);
}

void	*t_coder_func(void *args)
{
	t_ma			*arg;
	int				compiles;
	t_settings		set;

	compiles = 0;
	arg = (t_ma *)args;
	set = arg->set;
	while (*arg->started < 0)
		usleep(0);
	while (10 > ++compiles && arg->status == 0)
	{
		get_t_dongles(arg->t_coder, arg, set);
		if (arg->status == 2)
			pthread_exit(0);
		queue_print(arg->t_coder, arg, arg->dats, 2);
		usleep(set.time_to_debug);
		queue_print(arg->t_coder, arg, arg->dats, 3);
		usleep(set.time_to_refactor);
	}
	queue_print(arg->t_coder, arg, arg->dats, 5);
	((t_ma *)args)->status = 1;
	pthread_exit(0);
}
