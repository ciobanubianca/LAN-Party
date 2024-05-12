#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

node *newNode(int nr_players, char *team_name, player *players, float totalPoints)
{
    node *new = (node *)malloc(sizeof(node));
    if(new == NULL)
    {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    new->val.nrPlayers = nr_players;
    
    new->val.teamName = (char *)malloc((strlen(team_name) + 1) * sizeof(char));
    if (new->val.teamName == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }
    strcpy(new->val.teamName , team_name);

    new->val.players = (player *)malloc(nr_players * sizeof(player));
    if (new->val.players == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    for (int i = 0; i < new->val.nrPlayers; i++)
    {
        new->val.players[i].firstName = (char *)malloc((strlen(players[i].firstName) + 1) * sizeof(char));
        if (new->val.players[i].firstName == NULL)
        {
            printf("Failed to allocate memory\n");
            return NULL;
        }
        strcpy(new->val.players[i].firstName, players[i].firstName);

        new->val.players[i].secondName = (char *)malloc((strlen(players[i].secondName) + 1) * sizeof(char));
        if (new->val.players[i].secondName == NULL)
        {
            printf("Failed to allocate memory\n");
            return NULL;
        }
        strcpy(new->val.players[i].secondName, players[i].secondName);

        new->val.players[i].points = players[i].points;
    }
    new->val.totalPoints = totalPoints;

    new->left = new->right = NULL;
    return new;
}

node *insert(node *node, team *key)
{
    if(node == NULL)
    {
        return newNode(key->nrPlayers, key->teamName, key->players, key->totalPoints);
    }

    if(key->totalPoints < node->val.totalPoints)
    {
        node->left = insert(node->left, key);
    }
    else if(key->totalPoints > node->val.totalPoints)
    {
        node->right = insert(node->right, key);
    }
    if(key->totalPoints == node->val.totalPoints)
    {
        if(strcmp(key->teamName, node->val.teamName) > 0)
        {
            node->right = insert(node->right, key);
        }
        
        else if(strcmp(key->teamName, node->val.teamName) < 0)
        {
        node->left = insert(node->left, key);
        }
    }
    return node;
}

void printBST(node *root, FILE *f1)
{
    if(root)
    {
        printBST(root->right, f1);
        fprintf(f1, "%-34s-  %.2f\n", root->val.teamName, root->val.totalPoints);
        printBST(root->left, f1);
    }
}

void preorder(node *root)
{
    if(root)
    {   preorder(root->right);
        printf("%-34s- %.2f\n", root->val.teamName, root->val.totalPoints);
        preorder(root->left);
        
    }
}