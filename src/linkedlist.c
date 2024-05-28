#include "linkedlist.h"

void initializeFreeList()
{
    for (int i = 0; i < MAX_NODES - 1; i++)
    {
        nodes[i].next = &nodes[i + 1];
    }
    nodes[MAX_NODES - 1].next = NULL;
    freeList = &nodes[0];
}

Node *allocateNode()
{
    if (freeList == NULL)
    {
        return NULL;
    }
    Node *newNode = freeList;
    freeList = freeList->next;
    newNode->next = NULL;
    return newNode;
}

void freeNode(Node *node)
{
    node->next = freeList;
    freeList = node;
}

void addNode(Node **head, int food, int time, int game_time)
{
    // char *str_total_moves = "";
    //     copyString(str_total_moves, numDisplay(game_time));
    //     uart_puts(reverseString(str_total_moves));
    Node *newNode = allocateNode();
    if (newNode == NULL)
    {
        return;
    }
    newNode->icon.food = food;
    newNode->icon.time = time + game_time;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp != NULL && temp->next != NULL)
        {
            if (temp->icon.food == food)
            {
                temp->icon.time += time;
                freeNode(newNode); // Free the allocated node if not needed
                return;
            }
            temp = temp->next;
        }
        // If not exist
        temp->next = newNode;
    }
}

void removeNodesWithZeroTime(Node **head, int game_time)
{
    Node *temp = *head;
    Node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->icon.time <= game_time)
        {
            if (prev == NULL)
            {
                // Node to be deleted is the head node
                *head = temp->next;
                freeNode(temp);
                temp = *head;
            }
            else
            {
                prev->next = temp->next;
                freeNode(temp);
                temp = prev->next;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
}