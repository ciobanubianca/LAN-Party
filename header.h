#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define characters 60

typedef struct player
{
    char *firstName;
    char *secondName;
    int points;
} player;

typedef struct team
{
    int nrPlayers;
    char *teamName;
    float totalPoints;

    player *players;
    struct team *next;

} team;

typedef struct queue
{
    team *front, *rear;
} Queue;

typedef struct node
{
    team val;
    struct node *left, *right;
}node ;

FILE *OpenWriteFile(char *file);

//=== LIST ==========================================================================================

void addAtBeginning(team **head, int nr_players, char *team_name, player *players, float totalPoints);

void addAtEnd(team **head, int nr_players, char *team_name, player *players, float totalPoints);

void printTeamName(team *head);

//=== QUEUE =========================================================================================

Queue *createQueue();

void enQueue(Queue *q, int nr_players, char *team_name, player *players, float totalPoints);

int isEmpty(Queue *q);

team *deQueue(Queue *q);

void printTeamNameQueue(Queue *q);

//=== STACK =========================================================================================

void push(team **top, team *aux);

team *pop(team **top);

int isEmptyStack(team *top);

void printStack(char *file, team *stack);

int OneElem(team *top);

void freeStack(team **stack);

int nrOfWinners(team *stack);

//=== BST ============================================================================================

node *newNode(int nr_players, char *team_name, player *players, float totalPoints);

node *insert(node *node, team *key);

void printBST(node *root, FILE *f1);

void preorder(node *root);

//=== TASK 1 =========================================================================================

void readTasks(char *file, int *tasks, int numOfTasks);

team *readTeams(char *file1, int *nrTeams);

void task1(char *file, team *teamList, int nrTeams);

//=== TASK 2 ==========================================================================================

float averageScore(team *teamlist);

float *averagescoresV(team *teamList, int *nrTeams);

float lowestScore(float *v, int *nrTeams);

int EliminatedTeams(int *nrTeams);

void deleteTeamAverg(team **teamlist, float medie);

float *deleteMin(float *v, int *nrTeams, float min);

void task2(char *file, team **teamList, int *nrTeams);

//=== TASK 3 ============================================================================================

void trim(char *str);

void task3(char *file, team **teamList, team **lastEight, int *nrTeams);

void matches(char *file, Queue *q, team **winnersStack, team **losersStack, team **lastEight, int *round, int *nrTeams);

float averageScore2(team *teamlist);

//=== TASK 4 ============================================================================================

void task4(char *file, team *lastEight);


#endif