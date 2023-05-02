//
// Created by mestan on 1.05.2023.
//

#include "structs.h"
#include "token.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front, rear;
    int size;
    unsigned capacity;
    struct element* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
            sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (struct element*)malloc(
            queue->capacity * sizeof(struct element));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int qIsEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, struct element item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
struct element dequeue(struct Queue* queue)
{
    struct element empty_el;
    empty_el.type = -666;
    if (qIsEmpty(queue))
        return empty_el;
    struct element item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
struct element front(struct Queue* queue)
{
    struct element empty_el;
    empty_el.type = -666;
    if (qIsEmpty(queue))
        return empty_el;
    return queue->array[queue->front];
}

// Function to get rear of queue
struct element rear(struct Queue* queue)
{
    struct element empty_el;
    empty_el.type = -666;
    if (qIsEmpty(queue))
        return empty_el;
    return queue->array[queue->rear];
}