#ifndef ERR_H
#define ERR_H

typedef enum Err{
	ERR_OK = 0,
	ERR_MEM = -1,
	ERR_EMPTY = -2,
	ERR_FULL = -3,
	ERR_EOF = -4,
	ERR_FORMAT = -5,
}Err;

void printErr(Err code);

#endif
