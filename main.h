#ifndef MAIN_H
# define MAIN_H
# include <pthread.h>
# include <stdlib.h> 
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct settings
{
    int     number_of_coders;
    int     time_to_compile;
    int     time_to_debug;
    int     time_to_refactor;
    int     number_of_compiles_required;
    int     dongle_cooldown;
    int     time_to_burnout;
    char    *scheduler;
} settings;

#endif