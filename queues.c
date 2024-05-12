#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "header.h"

Queue *createQueue()
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
    {
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, int nr_players, char *team_name, player *players, float totalPoints)
{
    team *newTeam = (team *)malloc(sizeof(team));
    if (newTeam == NULL)
    {
        printf("Failed to allocate memory!\n");
        return;
    }

    newTeam->nrPlayers = nr_players;

    newTeam->teamName = (char *)malloc((strlen(team_name) + 1) * sizeof(char));
    if (newTeam->teamName == NULL)
    {
        printf("Failed to allocate memory\n");
        return;
    }
    strcpy(newTeam->teamName, team_name);

    newTeam->players = (player *)malloc(nr_players * sizeof(player));
    if (newTeam->players == NULL)
    {
        printf("Failed to allocate memory\n");
        return;
    }

    for (int i = 0; i < newTeam->nrPlayers; i++)
    {
        newTeam->players[i].firstName = (char *)malloc((strlen(players[i].firstName) + 1) * sizeof(char));
        if (newTeam->players[i].firstName == NULL)
        {
            printf("Failed to allocate memory\n");
            return;
        }
        strcpy(newTeam->players[i].firstName, players[i].firstName);

        newTeam->players[i].secondName = (char *)malloc((strlen(players[i].secondName) + 1) * sizeof(char));
        if (newTeam->players[i].secondName == NULL)
        {
            printf("Failed to allocate memory\n");
            return;
        }
        strcpy(newTeam->players[i].secondName, players[i].secondName);

        newTeam->players[i].points = players[i].points;
    }
    newTeam->totalPoints = totalPoints;

    newTeam->next = NULL;

    if (q->rear == NULL)
    {
        q->rear = newTeam;
    }
    else
    {
        (q->rear)->next = newTeam;
        (q->rear) = newTeam;
    }

    if (q->front == NULL)
    {
        q->front = q->rear;
    }
}

int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

team *deQueue(Queue *q)
{
    team *aux = q->front;
    team *Team = (team *)malloc(sizeof(team));

    if (isEmpty(q))
    {
        return NULL;
    }

    Team->nrPlayers = aux->nrPlayers;

    Team->teamName = (char *)malloc((strlen(aux->teamName) + 1) * sizeof(char));
    if (Team->teamName == NULL)
    {
        return NULL;
    }
    strcpy(Team->teamName, aux->teamName);

    Team->players = (player *)malloc(Team->nrPlayers * sizeof(player));
    if (Team->players == NULL)
    {
        printf("Failed to alocate memory\n");
        return NULL;
    }

    for (int i = 0; i < Team->nrPlayers; i++)
    {
        Team->players[i].firstName = (char *)malloc((strlen(aux->players[i].firstName) + 1) * sizeof(char));
        if (Team->players[i].firstName == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }
        strcpy(Team->players[i].firstName, aux->players[i].firstName);

        Team->players[i].secondName = (char *)malloc((strlen(aux->players[i].secondName) + 1) * sizeof(char));
        if (Team->players[i].secondName == NULL)
        {
            printf("Failed to alocate memory\n");
            return NULL;
        }
        strcpy(Team->players[i].secondName, aux->players[i].secondName);

        Team->players[i].points = aux->players[i].points;
    }
    Team->totalPoints = aux->totalPoints;

    q->front = (q->front)->next;
    free(aux->teamName); // Dealoc memory allocated for aux's teamName
    for (int i = 0; i < aux->nrPlayers; i++)
    {
        free(aux->players[i].firstName);
        free(aux->players[i].secondName);
    }
    free(aux->players);
    free(aux);
    return Team;
}

void printTeamNameQueue(Queue *q)
{
    if (isEmpty(q))
    {
        return;
    }
    team *current = q->front;

    while (current != NULL)
    {
        printf("%s\n", current->teamName);
        current = current->next;
    }
}
