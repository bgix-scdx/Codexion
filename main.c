#include <stdio.h>
#include <stdlib.h>
#include "cyclic_list.h"
#include "threads.h"
#include <string.h>
void error(const char *text)
{
    printf("\n\033[38;2;255;0;0m%s\033[0m\n", text);
}


int check_args(int argc, char **argv)
{
    int loop;

    loop = 0;
    if (argc != 9)
    {
        error("Error, arguments missing !");
        return (1);
    }
    while (loop < argc - 2)
    {
        if (atoi(argv[loop + 1]) < 1)
        {
            error("Error, arguments must be positive integers greater than 1 !");
            return (1);
        }
        loop++;
    }
    if (strcmp(argv[argc - 1], "fifo") != 0 && strcmp(argv[argc - 1], "edf") != 0)
    {

        error("Error, last argument must be either 'fifo' or 'edf' !");
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    cyclic_list *dongles;
    cyclic_list *coders;
    dongle      *tmp_dongle;
    coder       *tmp_coder;
    list_part *d1;
    list_part *d2;
    int loop;

    if (check_args(argc, argv))
        return (1);
    dongles = create_list();
    coders = create_list();
    loop = 0;
    while (loop < atoi(argv[1]))
    {
        tmp_dongle = create_dongle(loop);
        insert_back(dongles, tmp_dongle);
        loop++;
    }
    loop = 0;
    while (loop < atoi(argv[1]))
    {
        d1 = dongles->head;
        d2 = dongles->head->next;
        tmp_coder = create_coder(loop, d1->value, d2->value);
        insert_front(coders, tmp_coder);
        rotate_list(dongles);
        loop++;
    }
    loop = 0;
    thread t = create_thread(error, "Hello world!");
    pthread_join(t.thread_id, NULL);
    printf("Done\n");
    free(dongles);
    free(coders);
    return (0);
}