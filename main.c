#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"
#define characters 50

#define numOfTasks 5

int main(int argc, char *argv[])
{
    int nrTeams = 0;
    team *teamList = readTeams(argv[2], &nrTeams);

    int *tasks = (int *)calloc(numOfTasks, sizeof(int));
    readTasks(argv[1], tasks, numOfTasks);

    if (tasks[0] == 1)
    {
        task1(argv[3], teamList, nrTeams);
    }

    return 0;
}