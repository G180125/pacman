//------------------------------queue.h---------------------
#ifndef POINT_H
#define POINT_H

typedef struct {
    int row;
    int col;
} Point;


#define MAX_SIZE 500

typedef struct {
    Point items[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

#endif /* POINT_H */

void initialize_queue(Queue *queue);
int is_queue_empty(Queue *queue);
void enqueue(Queue *queue, Point item);
Point dequeue(Queue *queue);
int is_point_equal(Point p1, Point p2);
void reverse_queue(Queue *queue);