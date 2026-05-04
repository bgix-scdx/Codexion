#ifndef CODEXION_H
# define CODEXION_H

typedef struct t_settings
{
    int     number_of_coders;
    int     time_to_compile;
    int     time_to_debug;
    int     time_to_refactor;
    int     number_of_compiles_required;
    int     dongle_cooldown;
    int     time_to_burnout;
    char    *scheduler;
} t_settings;


#endif