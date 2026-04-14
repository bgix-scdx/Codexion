#include "main.h"

void make_line(int x, int y)
{
    int     mult;
    int     i;
    char    **background[1000];
    char    *col = "\033[38;2;100;100;100;48;2;0;0;0m";
    mult = 10;
    i = 0;
    *background[0] = "╱╱╱╱╱╱╱╱╱╱";
    *background[1] = "╲╲╲╲╲╲╲╲╲╲";
    *background[2] = "╱╱╱╱╱╱╱╱╱╱";

    while (i <= 2)
    {
        printf("\033[%d;%dH%s%s\033[0m", x + i + 1, y, col,  *background[i]);
        i++;
    }
    (void)x;
    (void)y;
    (void)mult;
}

void display(settings cond)
{
    int x;
    int y;

    x = 0;
    y = 0;
    make_line(x, y);

    (void)cond;
}