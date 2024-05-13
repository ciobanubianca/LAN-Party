#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

node *newNode(int nr_players, char *team_name, player *players, float totalPoints)
{
    node *new = (node *)malloc(sizeof(node));
    if (new == NULL)
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
    strcpy(new->val.teamName, team_name);

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
    if (node == NULL)
    {
        return newNode(key->nrPlayers, key->teamName, key->players, key->totalPoints);
    }

    if (key->totalPoints < node->val.totalPoints)
    {
        node->left = insert(node->left, key);
    }
    else if (key->totalPoints > node->val.totalPoints)
    {
        node->right = insert(node->right, key);
    }
    if (key->totalPoints == node->val.totalPoints)
    {
        if (strcmp(key->teamName, node->val.teamName) > 0)
        {
            node->right = insert(node->right, key);
        }

        else if (strcmp(key->teamName, node->val.teamName) < 0)
        {
            node->left = insert(node->left, key);
        }
    }

    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;

    return node;
}

void printBST(node *root, FILE *f1)
{
    if (root)
    {
        printBST(root->right, f1);
        fprintf(f1, "%-34s-  %.2f\n", root->val.teamName, root->val.totalPoints);
        printBST(root->left, f1);
    }
}

void preorder(node *root)
{
    if (root)
    {
        preorder(root->right);
        printf("%-34s- %.2f\n", root->val.teamName, root->val.totalPoints);
        preorder(root->left);
    }
}

// === AVL ===

int nodeHeight(node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    else
    {
        return root->height;
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

node *rightRotation(node *z)
{
    node *y = z->left;
    node *T = y->right;

    y->right = z; // roteste
    z->left = T;

    // modificam inaltimile
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y; // noua radacina
}

node *leftRotation(node *z)
{
    node *y = z->right;
    node *T = y->left;

    y->left = z; // roteste
    z->right = T;

    // modificam inaltimile
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y; // noua radacina
}

node *LRRotation(node *z)
{
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

node *RLRotation(node *z)
{
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

node *insertAVL(node *nod, team *key)
{
    if (nod == NULL)
    {
        return newNode(key->nrPlayers, key->teamName, key->players, key->totalPoints);
    }

    if (key->totalPoints < nod->val.totalPoints)
    {
        nod->left = insertAVL(nod->left, key);
    }
    else if (key->totalPoints > nod->val.totalPoints)
    {
        nod->right = insertAVL(nod->right, key);
    }
    else if (key->totalPoints == nod->val.totalPoints)
    {
        if (strcmp(key->teamName, nod->val.teamName) > 0)
        {
            nod->right = insertAVL(nod->right, key);
        }
        else if (strcmp(key->teamName, nod->val.teamName) < 0)
        {
            nod->left = insertAVL(nod->left, key);
        }
    }

    // updateaza inaltimea nodurilor stramos, de jos in sus
    nod->height = 1 + max(nodeHeight(nod->left), nodeHeight(nod->right));
    int k = (nodeHeight(nod->left) - nodeHeight(nod->right)); // factorul de echilibru

    // verificam ce rotatie trebuie efectuata

    // y in stanga, x in stanga lui y
    if (k > 1 && key->totalPoints < nod->left->val.totalPoints) // LL
    {
        return rightRotation(nod);
    }
    else if (k > 1 && key->totalPoints == nod->left->val.totalPoints)
    {
        if (strcmp(key->teamName, nod->left->val.teamName) < 0)
        {
            return rightRotation(nod);
        }
    }
    // y in dreapta, x in dreapta lui y
    if (k < -1 && key->totalPoints > nod->right->val.totalPoints) // RR
    {
        return leftRotation(nod);
    }
    else if (k < -1 && key->totalPoints == nod->left->val.totalPoints)
    {
        if (strcmp(key->teamName, nod->left->val.teamName) > 0)
        {
            return leftRotation(nod);
        }
    }

    if (k < -1 && key->totalPoints < nod->left->val.totalPoints) // LR
    {
        return RLRotation(nod);
    }
    
    if (k > 1 && key->totalPoints > nod->right->val.totalPoints) // RL
    {
        return LRRotation(nod);
    }
    return nod;
}

void createAVL(node **AVL, node *root)
{
    if (root)
    {
        createAVL(AVL, root->right);
        *AVL = insertAVL(*AVL, &(root->val));
        createAVL(AVL, root->left);
    }
}

void printAVL(FILE *f1, node *root)
{
    if (root)
    {
        printAVL(f1, root->right);
        if (root->height == 2)
        {
            fprintf(f1, "%s\n", root->val.teamName);
        }
        printAVL(f1, root->left);
    }
}
