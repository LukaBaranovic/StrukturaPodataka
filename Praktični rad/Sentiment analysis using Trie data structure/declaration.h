/*
Header file, (glavni) koji inicijalizira strukturu te sadrzi funkciju za pokretanje programa.
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node* position;
struct Node {
	char caracter;
	int sentiment;
	bool isEndOfWord;
	position next_brother;
	position next_child;
};

void run_program();
position initialize();
