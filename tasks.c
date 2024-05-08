#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

#define characters 50

void readTasks(char *file, int *tasks, int numOfTasks)
{
    FILE *f1 = fopen(file, "rt");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }

    for (int i = 0; i < numOfTasks; i++)
    {
        fscanf(f1, "%d", &tasks[i]);
    }

    fclose(f1);
}

//=== TASK 1 ===========================================================

team *readTeams(char *file1, int *nrTeams)
{
    FILE *f1 = fopen(file1, "rt");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return NULL;
    }

    int nr_players;
    float totalPoints = 0.0;
    char *team_name, space;
    player *players;

    fscanf(f1, "%d", nrTeams);

    team **TeamList = (team **)malloc((*nrTeams) * sizeof(team *));
    if (TeamList == NULL)
    {
        printf("Failed to alocate memory\n");
        return NULL;
    }

    for (int i = 0; i < (*nrTeams); i++)
    {
        TeamList[i] = (team *)malloc(sizeof(team));
        if (TeamList[i] == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }
    }

    for (int i = 0; i < (*nrTeams); i++)
    {
        fscanf(f1, "%d", &nr_players);

        team_name = (char *)malloc(characters * sizeof(char));
        if (team_name == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }

        fscanf(f1, "%c", &space); // citeste spatiul dintre nr de jucatori si numele echipei

        fgets(team_name, characters, f1);

        if (team_name[strlen(team_name) - 1] == '\n') // elimina newline-ul
        {
            team_name[strlen(team_name) - 1] = '\0';
        }

        players = (player *)malloc(nr_players * sizeof(player));
        if (players == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }

        for (int j = 0; j < nr_players; j++)
        {
            players[j].firstName = (char *)malloc(characters * sizeof(char));
            if (players[j].firstName == NULL)
            {
                printf("Failed to alocate memory\n");
                return NULL;
            }

            players[j].secondName = (char *)malloc(characters * sizeof(char));
            if (players[j].secondName == NULL)
            {
                printf("Failed to alocate memory\n");
                return NULL;
            }

            fscanf(f1, "%s%c%s%c%d", players[j].firstName, &space, players[j].secondName, &space, &players[j].points);

            totalPoints += players[j].points;
        }

        addAtBeginning(&(TeamList[0]), nr_players, team_name, players, totalPoints);
        fscanf(f1, "\n"); // ignora linia dintre echipe in fisier
        totalPoints = 0.0;
    }

    fclose(f1);

    return *TeamList;
}

void task1(char *file, team *teamList, int nrTeams)
{
    FILE *f1 = fopen(file, "wt");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }

    int i = 0;
    team *current = teamList;

    while (i < nrTeams)
    {
        fprintf(f1, "%s\n", current->teamName);
        current = current->next;
        i++;
    }

    fclose(f1);
}
