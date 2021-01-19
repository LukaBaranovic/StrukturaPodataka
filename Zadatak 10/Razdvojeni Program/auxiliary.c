#include "auxiliary.h"

void start() {
	position main = readFromFile();
	infixToFile(main);
}

position initialize() {
	position new = (position)malloc(sizeof(struct Node));
	if (new == NULL)  return NULL;
	new->Right = NULL;
	new->Left = NULL;
	new->Next = NULL;
	return new;
}