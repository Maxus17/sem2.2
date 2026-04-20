#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isNumber(const char *str)
{
	if (str == NULL)
	{
		printf("пустая строка\n");
		return false;
	}
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]))
		{
			printf("ошибка ввода\n");
			return false;
		}
	}

	return true;
}
