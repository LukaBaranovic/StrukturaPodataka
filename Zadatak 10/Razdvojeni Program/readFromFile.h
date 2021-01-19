#include "declaration.h"

position readFromFile();
position separate(char*);
void pushNumber(position, int);
void pushOperand(position, char);
position popNumber(position);