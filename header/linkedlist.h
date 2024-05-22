#define MAX_NODES 100
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "uart0.h"
#ifndef NULL
#define NULL ((void*)0) // Define NULL if it's not already defined
#endif
#endif

typedef struct Icon{
    int food;
    int time;
    int time_track;
} Icon;

typedef struct Node{
    Icon icon;
    struct Node* next;
} Node;

extern Node nodes[MAX_NODES];
extern Node *freeList;

void initializeFreeList();
Node* allocateNode();
void freeNode(Node* node);
void addNode(Node** head, int food, int time);
void removeNodesWithZeroTime(Node** head);