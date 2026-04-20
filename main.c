#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>

#include "prog.h"

int main()
{
	Err code = ERR_OK;
	
	char *input = readline("> ");

	while (input != NULL)
	{	
		int cnt_pass = 0;
		Passenger *passengers = NULL;
		Airport airport = {NULL, 0};
		
		code = parse(&airport, &passengers, input, &cnt_pass);
		if (code != ERR_OK)
		{
			printErr(code);
			free(input);
			return 1;
		}
	
		code = createAirport(&airport);
		if (code != ERR_OK)
		{
			printErr(code);
			freePassengers(passengers, cnt_pass);
			free(input);
			return 1;
		}

		processAirport(&airport, passengers, cnt_pass);
		
		freeAirport(&airport, airport.cnt_desk);
		freePassengers(passengers, cnt_pass);
		free(input);
		
		input = readline("> ");
	}
	
	free(input);
	return 0;
}
