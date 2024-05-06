#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[])
{
    int nrTeams = 0;
    team *teamList = task1(argv[1], argv[2], argv[3], &nrTeams);

    return 0;
}