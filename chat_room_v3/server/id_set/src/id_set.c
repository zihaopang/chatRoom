#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int id_set()
{
    int id;

    srand((unsigned)time(NULL));

    id = rand()%10000 + 1;

    return id;
}
