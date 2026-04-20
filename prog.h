#ifndef PROG_H
#define PROG_H

#include "queue.h"

typedef struct Desk{
	Passenger *current;
	int timer;
	Queue *queue;
}Desk;

typedef struct Airport{
	Desk *desks;
	int cnt_desk;
}Airport;

void freeAirport(Airport *, const int);
void freePassengers(Passenger *, const int);
Err parse(Airport *, Passenger **, const char *, int *);
Err createAirport(Airport *);
void printAirport(Airport *, int);
int leastConections(Airport *);
void processAirport(Airport *, Passenger *, const int);


#endif
