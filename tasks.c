#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "header.h"

#define characters 60

FILE *OpenWriteFile(char *file)
{
    FILE *f1 = fopen(file, "wt");
    return f1;
}

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
        printf("Failed to allocate memory\n");
        return NULL;
    }

    for (int i = 0; i < (*nrTeams); i++)
    {
        TeamList[i] = (team *)malloc(sizeof(team));
        if (TeamList[i] == NULL)
        {
            printf("Failed to allocate memory\n");
            return NULL;
        }
    }

    for (int i = 0; i < (*nrTeams); i++)
    {
        fscanf(f1, "%d", &nr_players);

        team_name = (char *)malloc(characters * sizeof(char));
        if (team_name == NULL)
        {
            printf("Failed to allocate memory\n");
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
            printf("Failed to allocate memory\n");
            return NULL;
        }

        for (int j = 0; j < nr_players; j++)
        {
            players[j].firstName = (char *)malloc(characters * sizeof(char));
            if (players[j].firstName == NULL)
            {
                printf("Failed to allocate memory\n");
                return NULL;
            }

            players[j].secondName = (char *)malloc(characters * sizeof(char));
            if (players[j].secondName == NULL)
            {
                printf("Failed to allocate memory\n");
                return NULL;
            }

            fscanf(f1, "%s%c%s%c%d", players[j].firstName, &space, players[j].secondName, &space, &players[j].points);

            totalPoints += players[j].points;
        }

        addAtBeginning(&(TeamList[0]), nr_players, team_name, players, totalPoints);

        if (i < (*nrTeams) - 1)
        {
            fscanf(f1, "\n"); // ignora linia dintre echipe in fisier
        }

        totalPoints = 0.0;
    }

    fclose(f1);

    return *TeamList;
}

void task1(char *file, team *teamList, int nrTeams)
{
    FILE *f1 = OpenWriteFile(file);
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

//=== TASK 2 ===========================================================

float averageScore(team *teamlist) // media punctajelor pentru o echipa
{
    float average = 0.0;

    for (int i = 0; i < teamlist->nrPlayers; i++)
    {
        average += teamlist->players[i].points;
    }
    return (float)(average / teamlist->nrPlayers);
}

float averageScore2(team *teamlist)
{
    float average = (float)(teamlist->totalPoints / teamlist->nrPlayers);

    return (float)(average);
}

float *averagescoresV(team *teamList, int *nrTeams) // vector cu mediile echipelor
{
    float *v = (float *)malloc(*nrTeams * sizeof(float));
    if (v == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    for (int i = 0; i < *nrTeams; i++)
    {
        v[i] = averageScore(teamList);
        teamList = teamList->next;
    }

    return v;
}

float lowestScore(float *v, int *nrTeams)
{
    float min = v[0];

    for (int i = 1; i < *nrTeams; i++)
    {
        if (v[i] <= min)
        {
            min = v[i];
        }
    }
    return min;
}

float *deleteMin(float *v, int *nrTeams, float min)
{
    int index = 0;
    for (int i = 0; i < (*nrTeams); i++)
    {
        if (v[i] == min)
        {
            index = i;
            for (int j = index; j < (*nrTeams - 1); j++)
            {
                v[j] = v[j + 1];
            }
            break;
        }
    }
    return v;
}

// nr de echipe pe care le eliminam pana la nr max de echipe ca putere a lui 2
int EliminatedTeams(int *nrTeams)
{
    int power = (int)log2(*nrTeams);
    int powerOfTwo = pow(2, power);
    return (*nrTeams - powerOfTwo);
}

void task2(char *file, team **teamList, int *nrTeams)
{
    FILE *f1 = OpenWriteFile(file);
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }

    float *v = averagescoresV(*teamList, nrTeams);

    int numOfEliminatedTeams = EliminatedTeams(nrTeams);

    float min = 0.0;
    // stergem un nr de echipe egal cu diferenta dintre nr total de echipe si nr max de echipe care poate fi scris ca o putere a lui 2
    for (int k = 0; k < numOfEliminatedTeams; k++)
    {
        min = lowestScore(v, nrTeams);
        deleteTeamAverg(teamList, min);
        v = deleteMin(v, nrTeams, min); // stergem si minimul din vector
        (*nrTeams)--;
    }

    team *current = *teamList;

    int i = 0;
    while (i < *nrTeams)
    {
        fprintf(f1, "%s\n", current->teamName);
        current = current->next;
        i++;
    }
    free(v);

    fclose(f1);
}
//=== TASK 3 =====================================================================

void trim(char *str) //elimina space uri, tab uri, newline uri
{
    int i = strlen(str) - 1;
    while (i >= 0 && isspace(str[i]))
    {
        str[i] = '\0';
        i--;
    }
}

void matches(char *file, Queue *q, team **winnersStack, team **losersStack, team **lastEight, int *round, int *nrTeams)
{
    FILE *f1 = fopen(file, "at");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }

    team *firstTeam, *secondTeam;
    // transform totalul de puncte al fiecarei echipe in media aritmetica a punctajelor
    team *average = q->front;
    while (average != NULL)
    {
        average->totalPoints = averageScore2(average);
        average = average->next;
    }

    float p = 0.0;

    if (isEmpty(q))
    {
        return;
    }

    while (*nrTeams > 1)
    {
        fprintf(f1, "\n--- ROUND NO:%d\n", *round);

        while (isEmpty(q) != 1)
        {
            firstTeam = deQueue(q);
            secondTeam = deQueue(q);
            trim(firstTeam->teamName);
            trim(secondTeam->teamName);

            // aliniaza primul string la stanga si completeaza in dreapta lui cu spatii pana la al 33 lea caracter,
            // la fel si pt al doilea string, il aliniaza la dreapta si completeaza la stanga restul pana la 33, cu spatii
            fprintf(f1, "%-33s-%33s\n", firstTeam->teamName, secondTeam->teamName);

            if (averageScore2(firstTeam) > averageScore2(secondTeam))
            {
                /*p = (float)(1.0 / firstTeam->nrPlayers); //adaugam la punctajul fiecarui jucator 1 / nr jucatori (1p pe echipa)
                for (int i = 0; i < firstTeam->nrPlayers; i++)
                {
                    firstTeam->players[i].points  += p;
                }*/
                firstTeam->totalPoints += 1.0;
                push(winnersStack, firstTeam);
                push(losersStack, secondTeam);
            }
            else
            {
                secondTeam->totalPoints += 1.0;
                push(winnersStack, secondTeam);
                push(losersStack, firstTeam);
            }
        }
        team *current = *winnersStack;
        fprintf(f1, "\nWINNERS OF ROUND NO:%d\n", *round);

        while (current != NULL)
        {
            if (current->teamName[strlen(current->teamName) - 1] == '\n')
            {
                (current->teamName[strlen(current->teamName) - 1]) = '\0';
            }
            fprintf(f1, "%-34s-  %.2f\n", current->teamName, current->totalPoints);
            current = current->next;
        }
        freeStack(losersStack);

        if (nrOfWinners(*winnersStack) == 8) // pastram ultimele 8 echipe intr o stiva
        {
            current = *winnersStack;
            while (current != NULL)
            {
                push(lastEight, current);
                current = current->next;
            }
        }
        // mutam echipele din stiva in coada
        team *temp;
        while (*winnersStack != NULL)
        {
            temp = pop(winnersStack);
            enQueue(q, temp->nrPlayers, temp->teamName, temp->players, temp->totalPoints);
        }
        freeStack(winnersStack);
        (*round)++;
        (*nrTeams) = (*nrTeams) / 2;
    }
    fclose(f1);
}

void task3(char *file, team **teamList, team **lastEight, int *nrTeams)
{
    FILE *f1 = fopen(file, "at");
    if (f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }

    int round = 1;
    Queue *q = createQueue();

    team *current = *teamList;
    for (int i = 0; i < *nrTeams; i++)
    {
        enQueue(q, current->nrPlayers, current->teamName, current->players, current->totalPoints);
        current = current->next;
    }

    team *winnersStack = NULL;
    team *losersStack = NULL;

    matches(file, q, &winnersStack, &losersStack, lastEight, &round, nrTeams);

    fclose(f1);
}

//=== TASK 4 =====================================================================

void task4(char *file, team *lastEight)
{
    FILE *f1 = fopen(file, "at");
    if(f1 == NULL)
    {
        printf("The file cannot be opened!\n");
        return;
    }
    
    node *root = NULL;
    team *current = lastEight;
    fprintf(f1, "\nTOP 8 TEAMS:\n");
    while(current != NULL)
    {  
        root = insert(root, current);
        current = current->next;
    }
    
    printBST(root, f1);

    fclose(f1);
}