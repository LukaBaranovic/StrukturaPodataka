/*
Header file za citanje iz datoteke.
*/

#pragma once
#include <stdio.h>
#include "declaration.h"


void read_from_file(position);
void append_word(position, char*, int);
position append_caracter(position, char);
void delete_All(position);
