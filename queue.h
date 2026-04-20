#ifndef QUEUE_H
#define QUEUE_H

#include "pass.h"
#include "err.h"
#include "inp.h"

#define LIMIT 10

struct Queue;
typedef struct Queue Queue;

Queue *createQueue(const int);
void freeQueue(Queue *);
bool isFull(Queue *);
bool isEmpty(Queue *);
Err put(Queue *, Passenger *passenger);
Err get(Queue *);
Err printQueue(Queue *);
int getQueueLen(Queue *);
Passenger *getPass(Queue *);

#endif
