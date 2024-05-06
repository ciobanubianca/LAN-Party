#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define chr 30

void addAtBeginning(team **head, int nr_players, char *team_name, player *players, int totalPoints)
{
	team *newTeam = (team *)malloc(sizeof(team));
	if (newTeam == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}

	newTeam->nrPlayers = nr_players;

	newTeam->teamName = (char *)malloc((strlen(team_name) + 1) * sizeof(char));
	if (newTeam->teamName == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}
	strcpy(newTeam->teamName, team_name);

	newTeam->players = (player *)malloc(nr_players * sizeof(player));
	if (newTeam->players == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}

	for (int i = 0; i < newTeam->nrPlayers; i++)
	{
		newTeam->players[i].firstName = (char *)malloc((strlen(players[i].firstName) + 1) * sizeof(char));
		if (newTeam->players[i].firstName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].firstName, players[i].firstName);

		newTeam->players[i].secondName = (char *)malloc((strlen(players[i].secondName) + 1) * sizeof(char));
		if (newTeam->players[i].secondName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].secondName, players[i].secondName);

		newTeam->players[i].points = players[i].points;
	}
	newTeam->totalPoints = totalPoints;

	newTeam->next = *head;
	*head = newTeam;

}	

void addAtEnd(team **head, int nr_players, char *team_name, player *players, int totalPoints)
{
	team *aux = *head;

	team *newTeam = (team *)malloc(sizeof(team));
	if (newTeam == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}

	newTeam->nrPlayers = nr_players;

	newTeam->teamName = (char *)malloc((strlen(team_name) + 1) * sizeof(char));
	if (newTeam->teamName == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}
	strcpy(newTeam->teamName, team_name);

	newTeam->players = (player *)malloc(nr_players * sizeof(player));
	if (newTeam->players == NULL)
	{
		printf("Failed to alocate memory\n");
		return;
	}

	for (int i = 0; i < newTeam->nrPlayers; i++)
	{
		newTeam->players[i].firstName = (char *)malloc((strlen(players[i].firstName) + 1) * sizeof(char));
		if (newTeam->players[i].firstName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].firstName, players[i].firstName);

		newTeam->players[i].secondName = (char *)malloc((strlen(players[i].secondName) + 1) * sizeof(char));
		if (newTeam->players[i].secondName == NULL)
		{
			printf("Failed to alocate memory\n");
			return;
		}
		strcpy(newTeam->players[i].secondName, players[i].secondName);

		newTeam->players[i].points = players[i].points;
	}
	newTeam->totalPoints = totalPoints;

	if (*head == NULL)
	{
		addAtBeginning(&*head, nr_players, team_name, players, totalPoints);
	}
	else
	{
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = newTeam;
		newTeam->next = NULL;
	}
}

void printTeamName(team *head)
{
	team *current = head;

	while (current != NULL)
	{
		printf("%s\n", current->teamName);
		current = current->next;
	}
}
