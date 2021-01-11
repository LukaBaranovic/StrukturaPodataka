/*
Source file za pokretanje programa.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "declaration.h"
#define BUFFER 256

/*
Funkcija: run_program
Inicijalizacija trie strukture, te pitanje za unos recenice.
Return: /
*/


void run_program() {
	position trie = initialize();
	if (trie == NULL) {
		printf("malloc failed in: run_program !!");
		return;
	}
	int loop = 1;
	int action = 0;

	read_from_file(trie);

	while (loop == 1) {
		printf("(1) Insert an sentence for sentiment evaluation \n");
		printf("(0) Exit  \n");
		printf("Chose an action: ");
		scanf("%d", &action);

		switch (action) {
		case 1:
			printf("Unesite recenicu za procjenu sentimenta:  ");
			calculate_sentiment(trie);
			break;
		case 0:
			loop = 0;
			break;
		default:
			printf("Nepostojeca radnja!!! ");
			loop = 0;
			break;
		}
	}
	delete_all(trie);
}

/*
Funkcija: initialize
Inicijalizira novu listu
Return: position
*/

position initialize() {
	position new = (position)malloc(sizeof(struct Node));
	new->next_brother = NULL;
	new->next_child = NULL;
	return new;
}
