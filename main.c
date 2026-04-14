#include "main.h"
#include "threads.h"
#include "coder.h"
#include "cyclic_list.h"
#include "display.h"

int check_args(int argc, char **argv)
{
    int loop;

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
            printf("Error, arguments must be positive integers greater than 1 !");
            return (1);
        }
        loop++;
    }
    if (strcmp(argv[argc - 1], "fifo") != 0 && strcmp(argv[argc - 1], "edf") != 0)
    {

        printf("Error, last argument must be either 'fifo' or 'edf' !");
        return (1);
    }
    return (0);
}

settings save_set(char **argv)
{
    settings tmp;

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

int init(int argc, char **argv)
{
    cyclic_list     *dongles;
    cyclic_list     *coders;
    cyclic_list     *threads;
    bool            start;
    settings        req;
    struct timeval  start_time;
    dongle          *tmp_dongle;
    thread          *tmp_thread;
    coder           *tmp_coder;
    int             status;
    int             count;
    list_part   *d1;
    list_part   *d2;
    int loop;
    
    status = 0;
    count = 0;
    start = false;
    if (check_args(argc, argv))
        return (1);
    req = save_set(argv);
    dongles = create_list();
    coders = create_list();
    threads = create_list();
    loop = 0;
    while (++loop < req.number_of_coders)
    {
        tmp_dongle = create_dongle(loop);
        insert_back(dongles, tmp_dongle);
    }
    loop = 0;
    while (++loop < req.number_of_coders)
    {
        d1 = dongles->head;
        d2 = dongles->head->next;
        tmp_coder = create_coder(loop, d1->value, d2->value);
        insert_front(coders, tmp_coder);
        rotate_list(dongles);
    }
    loop = 0;
    while (++loop < req.number_of_coders && ++count)
    {
        tmp_coder = coders->head->value;
        tmp_thread = create_thread(handle_coder, req, tmp_coder, &start, &start_time);
        insert_front(threads, tmp_thread);
        rotate_list(coders);
    }
    loop = 0;
    gettimeofday(&start_time, NULL);
    start = true;
    while (count > 0)
    {
        rotate_list(threads);
        if (*((thread *)threads->head->value)->result == 1)
            return (1);
        else if (*((thread *)threads->head->value)->result == 0)
        {
            remove_head(threads);
            count--;
        }
        
        if (status != 0)
        {
            return (1);
        }
    }
    (void)threads;
    //stop(dongles, coders, threads);
    return (0);
}

int main(int argc, char **argv)
{
    return (init(argc, argv));
}
