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

Node* allocateNode()
{
    if (freeList == NULL)
    {
        return NULL;
    }
    Node* newNode = freeList;
    freeList = freeList->next;
    newNode->next = NULL;
    return newNode;
}

void freeNode(Node* node)
{
    node->next = freeList;
    freeList = node;
}

void addNode(Node** head, int food, int time)
{
    Node* newNode = allocateNode();
    if (newNode == NULL)
    {
        return;
    }
    newNode->icon.food = food;
    newNode->icon.time = time;
    newNode->icon.time_track = 0;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* temp = *head;
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
        temp->next = newNode;
    }
}

void removeNodesWithZeroTime(Node** head)
{
    Node* temp = *head;
    Node* prev = NULL;

    while (temp != NULL)
    {
        if (temp->icon.time == 0)
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