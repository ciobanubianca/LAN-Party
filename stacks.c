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

	newTeam->nrPlayers = aux->nrPlayers;

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

team *pop(team **top)
{
	if (isEmptyStack(*top))
	{
		return NULL;
	}

	team *temp = (*top);

	team *aux = (team *)malloc(sizeof(team));
	if (aux == NULL)
	{
		printf("Failed to allocate memory!\n");
		return NULL;
	}
	aux->nrPlayers = temp->nrPlayers;

	aux->teamName = (char *)malloc((strlen(temp->teamName) + 1) * sizeof(char));
	if (aux->teamName == NULL)
	{
		printf("Failed to alocate memory\n");
		return NULL;
	}
	strcpy(aux->teamName, temp->teamName);

	aux->players = (player *)malloc(temp->nrPlayers * sizeof(player));
	if (aux->players == NULL)
	{
		printf("Failed to alocate memory\n");
		return NULL;
	}

	for (int i = 0; i < aux->nrPlayers; i++)
	{
		aux->players[i].firstName = (char *)malloc((strlen(temp->players[i].firstName) + 1) * sizeof(char));
		if (aux->players[i].firstName == NULL)
		{
			printf("Failed to alocate memory\n");
			return NULL;
		}
		strcpy(aux->players[i].firstName, temp->players[i].firstName);

		aux->players[i].secondName = (char *)malloc((strlen(temp->players[i].secondName) + 1) * sizeof(char));
		if (aux->players[i].secondName == NULL)
		{
			printf("Failed to alocate memory\n");
			return NULL;
		}
		strcpy(aux->players[i].secondName, temp->players[i].secondName);

		aux->players[i].points = temp->players[i].points;
	}
	aux->totalPoints = temp->totalPoints;

	*top = (*top)->next;
	free(temp);

	return aux;
}

int isEmptyStack(team *top)
{
	return (top == NULL);
}

void printStack(char *file, team *stack)
{
	FILE *f1 = fopen(file, "at");
	if (f1 == NULL)
	{
		printf("The file cannot be opened!\n");
		return;
	}
	if (isEmptyStack(stack))
	{
		return;
	}
	team *current = stack;
	while (current != NULL)
	{
		printf("%s-%.2f\n", current->teamName, averageScore(current));
		current = current->next;
	}
}

int OneElem(team *top)
{
	if (isEmptyStack(top))
	{
		return 0;
	}

	if (top != NULL && top->next == NULL)
	{
		return 1;
	}

	return 0;
}

void freeStack(team **stack)
{
	while (*stack != NULL)
	{
		team *temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}

int nrOfWinners(team *stack)
{
	int nr = 0;
	team *current = stack;
	while (current != NULL)
	{
		nr++;
		current = current->next;
	}
	return nr;
}