#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define chr 30

team *task1(char *file1, char *file2, char *file3, int *nrTeams)
{
    FILE *f1 = fopen(file1, "rt");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return NULL;
    }


    FILE *f2 = fopen(file2, "rt");
    if (f2 == NULL)
    {
        printf("The file cannot be opened!\n");
        return NULL;
    }

    int nr_players, totalPoints = 0, *PointsPerTeam;
    char *team_name, space;
    player *players;

    fscanf(f2, "%d", nrTeams);

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

    PointsPerTeam = (int *)malloc((*nrTeams) * sizeof(int)); 
    if (PointsPerTeam == NULL)
    {
        printf("Failed to alocate memory\n");
        return NULL;
    }

    for (int i = 0; i < (*nrTeams); i++) 
    {
        fscanf(f2, "%d", &nr_players); 

        team_name = (char *)malloc(chr * sizeof(char));
        if (team_name == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }

        fscanf(f2, "%c", &space); //citeste spatiul dintre nr de jucatori si numele echipei

        fgets(team_name, chr, f2);

        if (team_name[strlen(team_name) - 1] == '\n') //elimina newline-ul
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
            players[j].firstName = (char *)malloc(chr * sizeof(char));
            if (players[j].firstName == NULL)
            {
                printf("Failed to alocate memory\n");
                return NULL;
            }

            players[j].secondName = (char *)malloc(chr * sizeof(char));
            if (players[j].secondName == NULL)
            {
                printf("Failed to alocate memory\n");
                return NULL;
            }

            fscanf(f2, "%s%c%s%c%d", players[j].firstName, &space, players[j].secondName, &space, &players[j].points);

            totalPoints += players[j].points;
        }
        PointsPerTeam[i] = totalPoints;

        addAtBeginning(&(TeamList[0]), nr_players, team_name, players, PointsPerTeam[i]);
        fscanf(f2, "\n"); //ignora linia dintre echipe in fisier
        totalPoints = 0;
    }

    FILE *f3 = fopen(file3, "wt");
    if (f3 == NULL)
    {
        printf("The file cannot be opened!\n");
        return NULL;
    }

    int i = 0;
    team *current = *TeamList;

    while (i < *nrTeams)
    {
        fprintf(f3, "%s\n", current->teamName);
        current = current->next;
        i++;
    }

     fclose(f3);

    for(int i = 0 ; i < *nrTeams ; i++)
    {
        free(TeamList[i]->teamName) ;
        free(TeamList[i]->players) ;
        free(TeamList[i]) ;

        for(int j = 0 ; j < TeamList[i]->nrPlayers ; j++)
        {
            free(TeamList[i]->players[j].firstName) ;
            free(TeamList[i]->players[j].secondName) ;
        }
    }
    free(PointsPerTeam) ;
    free(TeamList) ; 

    fclose(f2);
    fclose(f1) ;

    return *TeamList;
}
