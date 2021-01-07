/*
Header file za racunanje sentimenta.
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "declaration.h"


int compare(position);
char* is_interpunction_first(char*);
bool is_interpunction_last(position, int, char* );
void calculate_sentiment(position);
float sigmoid(int);
