#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define BUFFER 256


typedef struct Node* position;
struct Node {
	int Number;
	char Operand;
	position Left, Right, Next;
};