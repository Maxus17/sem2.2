#include <stdio.h>

#include "err.h"

void printErr(Err code)
{
	switch(code)
	{
		case ERR_OK:
			break;
		case ERR_MEM:
			printf("ошибка выделения памяти\n");
			break;
		case ERR_EMPTY:
			printf("пустая строка\n");
			break;
		case ERR_FULL:
			printf("переполнение\n");
			break;
		case ERR_EOF:
			printf("EOF - вы нажали ctrl + D\n");
			break;
		case ERR_FORMAT:
			printf("Неверный формат\n");
			break;
	}
}
