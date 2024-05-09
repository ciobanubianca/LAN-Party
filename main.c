#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"
#define characters 60

#define numOfTasks 5

int main(int argc, char *argv[])
{
    int *tasks = (int *)calloc(numOfTasks, sizeof(int));
    readTasks(argv[1], tasks, numOfTasks);

    int nrTeams = 0;
    team *teamList = readTeams(argv[2], &nrTeams);

    if (tasks[0] == 1)
    {
        task1(argv[3], teamList, nrTeams);
    }

    if (tasks[1] == 1)
    {
        task2(argv[3], &teamList, &nrTeams);
    }

    if (tasks[2] == 1)
    {
        task3(argv[3], &teamList, &nrTeams);
    }

    /*if (tasks[3] == 1)
    {
        task4(argv[3], &teamList, &nrTeams);
    }

    if (tasks[4] == 1)
    {
        task5(argv[3], &teamList, &nrTeams);
    } */

    return 0;
}