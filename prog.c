#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>

#include "prog.h"

void freeAirport(Airport *airport, const int cnt)
{
	if (airport->desks != NULL)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (airport->desks[i].queue != NULL)
			{
				freeQueue(airport->desks[i].queue);
			}
		}
		free(airport->desks);
	}
}

void freePassengers(Passenger *passengers, const int cnt)
{
	if (passengers != NULL)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (passengers[i].id != NULL)
			{
				free(passengers[i].id);
			}
		}
		free(passengers);
	}
}

Err parse(Airport*airport, Passenger **passengers, const char *input, int *cnt_pass)
{
	char *str = strdup(input);
	
	char *word = strtok(str, " ");

	if (isNumber(word) == false)
	{
		free(str);
		return ERR_FORMAT;
	}
	airport->cnt_desk = atoi(word);

	*cnt_pass = 0;
	*passengers = NULL;
	
	word = strtok(NULL, " ");
	
	while (word != NULL)
	{	
		char *cpy = strdup(word);
		char id[2], ta_str[100], ts_str[100];

		if (sscanf(cpy, "%[^/]/%[^/]/%[^/]", id, ta_str, ts_str) != 3)
		{
			free(str);
			free(cpy);
			return ERR_FORMAT;
		}

		if (!isNumber(ta_str) || !isNumber(ts_str))
		{
			free(str);
			free(cpy);
			return ERR_FORMAT;
		}
		
		*passengers = (Passenger *)realloc(*passengers, (*cnt_pass + 1) * sizeof(Passenger));
		if (*passengers == NULL)
		{
			free(str);
			return ERR_MEM;
		}

		(*passengers)[*cnt_pass].id = strdup(id);
		(*passengers)[*cnt_pass].ta = atoi(ta_str);
		(*passengers)[*cnt_pass].ts = atoi(ts_str);
		(*cnt_pass)++;
		free(cpy);
		word = strtok(NULL, " ");
	}
	free(str);
	return ERR_OK;	
}

Err createAirport(Airport *airport)
{
	airport->desks = (Desk *)calloc(airport->cnt_desk, sizeof(Desk));
	if (airport->desks == NULL)
	{
		return ERR_MEM;
	}
	for (int i = 0; i < airport->cnt_desk; i++)
	{
		airport->desks[i].queue = createQueue(LIMIT);
		if (airport->desks[i].queue == NULL)
		{
			freeAirport(airport, i);
			return ERR_EMPTY;
		}
	}
	return ERR_OK;
}

void printAirport(Airport *airport, int time)
{
	printf("%d \n", time);
	for (int i = 0; i < airport->cnt_desk; i++)
	{	
		printf("№%d ", i + 1);
		printQueue(airport->desks[i].queue);
		printf("\n");
	}
	printf("\n\n");
}

int leastConections(Airport *airport)
{
	int min_index = -1;
	int min_len = INT_MAX;
	for (int i = 0; i < airport->cnt_desk; i++)
	{
		if (getQueueLen(airport->desks[i].queue) < min_len)
		{
			min_len = getQueueLen(airport->desks[i].queue);
			min_index = i;
		}
	}

	return min_index;
}

int cmpPass(const void *a, const void *b)
{
	const Passenger *x = (const Passenger *)a;
	const Passenger *y = (const Passenger *)b;
	return x->ta - y->ta;
}

void processAirport(Airport *airport, Passenger *passengers, const int cnt_pass)
{
	qsort(passengers, cnt_pass, sizeof(Passenger), cmpPass);
	
	int pass = 0;
	int time = 0;
	int flag = 0;
	Err code = ERR_OK;
	while (pass != cnt_pass)
	{
		for (int i = 0; i < airport->cnt_desk; i++)
		{
			if (!isEmpty(airport->desks[i].queue))
			{
				airport->desks[i].current = getPass(airport->desks[i].queue);
				airport->desks[i].timer++;
				if (airport->desks[i].timer == airport->desks[i].current->ts)
				{
					code = get(airport->desks[i].queue);
					if (code != ERR_OK)
					{
						printErr(code);
						return;
					}
					flag = 1;
					airport->desks[i].timer = 0;
					pass++;
				}
			}
		}
		
		for (int i = 0; i < cnt_pass; i++)
		{
			if (passengers[i].ta == time)
			{
				int min_index = leastConections(airport);
				code = put(airport->desks[min_index].queue, passengers + i);
				if (code != ERR_OK)
				{
					printErr(code);
					return;
				}
				flag = 1;
			}
		}

		if (flag == 1)
		{
			printAirport(airport, time);
			flag = 0;
		}
		time++;
	}
}
