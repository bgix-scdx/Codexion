#ifndef CODER_H
# define CODER_H
# include "main.h"

typedef struct t_dongle
{
    bool			taken;
    int				id;
    pthread_mutex_t	mutex;
    int				last_used;
}   dongle;

//status:
//0 = compiling
//1 = debugging
//2 = refactoring
//3 = Burnt-out
typedef struct t_coder
{
    int		        id;
    int		        status;
	int		        compilation;
    struct timeval  last_compile;
    dongle	        *dongle1;
    dongle	        *dongle2;
}   coder;

typedef struct parg{
    settings    req;
    coder       *me;
    bool        *start;
    int         result;
    struct timeval  *t_start;
} parg;

coder	*create_coder(int id, void *right, void *left);
dongle	*create_dongle(int id);
void     handle_coder(parg *args);

#endif