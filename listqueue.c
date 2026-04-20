#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>

#include "queue.h"

typedef struct Node{
	Passenger *passenger;
	struct Node *next;
}Node;

typedef struct Queue{
	Node *head;
	Node *tail;
	int len;
}Queue;

Queue *createQueue(const int limit)
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	queue->len = 0;
	return queue;
}

void freeQueue(Queue *queue)
{
	if (queue)
	{
		Node *cur = queue->head;
		Node *next;
		while (cur != NULL)
		{
			next = cur->next;
			free(cur);
			cur = next;
		}
		free(queue);
	}
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
	Node *ptr = (Node *)malloc(sizeof(Node));
	if (!ptr)
	{
	  	return ERR_MEM;
	}
	ptr->passenger = passenger;
	ptr->next = NULL;
	
	if (queue->tail == NULL)
	{
		queue->head = queue->tail = ptr;
	}
	else
	{
		queue->tail->next = ptr;
		queue->tail = ptr;
	}
	queue->len++;
	return ERR_OK;
}

Err get(Queue *queue)
{
	if (isEmpty(queue))
	{
		return ERR_EMPTY;
	}
	Node *tmp = queue->head;
	queue->head = queue->head->next;
	if (queue->head == NULL)
	{
		queue->tail = NULL;
	}
	free(tmp);
	queue->len--;
	return ERR_OK;
}

Err printQueue(Queue *queue)
{	
	if (isEmpty(queue))
	{
		return ERR_EMPTY;
	}
	Node *cur = queue->head;
	while (cur != NULL)
	{
		printf("%s", cur->passenger->id);
		cur = cur->next;
	}
	return ERR_OK;
}

int getQueueLen(Queue *queue)
{
	return queue->len;
}

Passenger *getPass(Queue *queue)
{
	return queue->head->passenger;
}
