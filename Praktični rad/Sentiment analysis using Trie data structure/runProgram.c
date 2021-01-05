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
	position trie = (position)malloc(sizeof(struct Node));
	trie->next_brother = NULL;
	trie->next_child = NULL;
	int loop = 1;
	int action = 0;

	read_from_file(trie);

	printf("(1) Unesi recenicu na procjenu sentimenta \n");
	printf("(0) Izadji iz programa \n");

	while (loop == 1) {
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