#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>

#include "queue.h"

typedef struct Queue{
	Passenger *passengers;
	int head;
	int tail;
	int len;
}Queue;

Queue *createQueue(const int limit)
{	
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->passengers = (Passenger *)calloc(limit, sizeof(Passenger));
	if (queue->passengers == NULL)
	{
		return NULL;
	}
	queue->head = queue->tail = 0;
	queue->len = 0;
	return queue;
}

void freeQueue(Queue *queue)
{
	if (queue->passengers != NULL)
	{
		free(queue->passengers);
	}
	free(queue);
}

bool isFull(Queue *queue)
{
	if (queue->len >= LIMIT)
	{
		return true;
	}
	return false;
}

bool isEmpty(Queue *queue)
{
	if (queue->len == 0)
	{
		return true;
	}
	return false;
}

Err put(Queue *queue, Passenger *passenger)
{
	if (isFull(queue))
	{
		return ERR_FULL;
	}
	queue->passengers[queue->tail++] = *passenger;
	queue->len++;
	return ERR_OK;
}

Err get(Queue *queue)
{
	if (isEmpty(queue))
	{
		return ERR_EMPTY;
	}
	queue->head++;
	queue->len--;
	return ERR_OK;
}

Err printQueue(Queue *queue)
{	
	if (isEmpty(queue))
	{
		return ERR_EMPTY;
	}
	for (int i = queue->head; i < queue->tail; i++)
	{
		printf("%s", queue->passengers[i].id);
	}
	return ERR_OK;
}

int getQueueLen(Queue *queue)
{
	return queue->len;
}

Passenger *getPass(Queue *queue)
{
	return queue->passengers + queue->head;
}
