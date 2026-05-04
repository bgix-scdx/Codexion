#include "headers/mallocs.h"
#include "headers/cyclic_list.h"
#include <stdio.h>
#include <string.h>
#include "codexion.h"
#include "headers/manager.h"

int check_args(int argc, char **argv)
{
	int	loop;

	loop = 0;
	if (argc != 9)
	{
		printf("Error, arguments missing !");
		return (1);
	}
	while (loop < argc - 2)
	{
		if (atoi(argv[loop + 1]) < 1)
		{
			printf("Error, arguments must be positives greater than 1 !");
			return (1);
		}
		loop++;
	}
	if (strcmp(argv[argc - 1], "fifo") != 0 &&
		strcmp(argv[argc - 1], "edf") != 0)
	{

		printf("Error, last argument must be either 'fifo' or 'edf' !");
		return (1);
	}
	return (0);
}

t_settings	save_set(char **argv)
{
	t_settings	tmp;

	tmp.number_of_coders = atoi(argv[1]);
	tmp.time_to_burnout = atoi(argv[2]);
	tmp.time_to_debug = atoi(argv[3]);
	tmp.time_to_refactor = atoi(argv[4]);
	tmp.dongle_cooldown = atoi(argv[5]);
	tmp.number_of_compiles_required = atoi(argv[6]);
	tmp.time_to_compile = atoi(argv[7]);
	tmp.scheduler = argv[8];
	return (tmp);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	return (manager(save_set(argv)));
}