#include "queue.h"

// Function to initialize the queue
void initialize_queue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Function to check if the queue is empty
int is_queue_empty(Queue *queue) {
    return queue->size == 0;
}

// Function to check if the queue is full
int is_queue_full(Queue *queue) {
    return queue->size == MAX_SIZE;
}

// Function to add an element to the queue (enqueue)
void enqueue(Queue *queue, Point item) {
    if (is_queue_full(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->items[queue->rear] = item;
    queue->size++;
}

// Function to remove an element from the queue (dequeue)
Point dequeue(Queue *queue) {
    Point item;
    if (is_queue_empty(queue)) {
        item.row = -1; // Return a dummy value indicating empty queue
        item.col = -1;
        return item;
    }
    item = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;
    return item;
}

int is_point_equal(Point p1, Point p2){
    if(p1.row == p2.row && p1.col == p2.col){
        return 0;
    }
    return 1;
}

void reverse_queue(Queue *queue) {
    if (is_queue_empty(queue)) {
        return; // Nothing to reverse if the queue is empty
    }

    // Create a stack to temporarily store elements
    Point stack[MAX_SIZE];
    int top = -1;

    // Dequeue elements from the queue and push them onto the stack
    while (!is_queue_empty(queue)) {
        Point item = dequeue(queue);
        stack[++top] = item;
    }

    // Pop elements from the stack and enqueue them back into the queue
    while (top >= 0) {
        Point item = stack[top--];
        enqueue(queue, item);
    }
}


