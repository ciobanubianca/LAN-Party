#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"

void push(team **top, team *aux)
{
    team *newTeam = (team *)malloc(sizeof(team));
    if (newTeam == NULL)
    {
        printf("Failed to allocate memory!\n");
        return;
    }

    newTeam->nrPlayers = aux->nrPlayers ;
    
    newTeam->teamName = (char *)malloc((strlen(aux->teamName) + 1) * sizeof(char));
	if (newTeam->teamName == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}
	strcpy(newTeam->teamName, aux->teamName);

	newTeam->players = (player *)malloc(aux->nrPlayers * sizeof(player));
	if (newTeam->players == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}

	for (int i = 0; i < newTeam->nrPlayers; i++)
	{
		newTeam->players[i].firstName = (char *)malloc((strlen(aux->players[i].firstName) + 1) * sizeof(char));
		if (newTeam->players[i].firstName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].firstName, aux->players[i].firstName);

		newTeam->players[i].secondName = (char *)malloc((strlen(aux->players[i].secondName) + 1) * sizeof(char));
		if (newTeam->players[i].secondName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].secondName, aux->players[i].secondName);

		newTeam->players[i].points = aux->players[i].points;
	}
	newTeam->totalPoints = aux->totalPoints;

    newTeam->next = *top;
   *top = newTeam; 
}


int pop(team **top)
{
    if(isEmptyStack(*top))
    {
        return INT_MIN ;
    }

    team *temp = (*top);

    int aux = temp->nrPlayers ;
    *top = (*top)->next;
    free(temp);

    return aux ;
}


int isEmptyStack(team *top)
{
    return (top == NULL);
}


int top(team *top)
{
    if(isEmptyStack(top))
    {
        return INT_MIN;
    }
    return top->nrPlayers;
}
