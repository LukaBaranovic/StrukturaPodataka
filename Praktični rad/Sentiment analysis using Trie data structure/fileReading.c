/*
Source file za citanje rijeci iz datoteke te razdvajanje na slova i slanje na unos u trie strukturu.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fileReading.h"
#include "declaration.h"
#define BUFFER 256

/*
Funkcija: read_from_file
Funkcija cita iz datoteke rijeci i vrijednosti njihovih sentimenta sprema u strukturu 'Trie'
po abecednom redu. Program vadi rijeci i sentiment jedno po jedno i salje u drugu funkciju 'append_word'
za daljnu obradu.
Return: /
*/

void read_from_file(position head) {
	FILE* fp = fopen("rijeci.txt", "r");
	char* source = NULL;
	source = (char*)malloc(BUFFER * sizeof(char));
	char* word = NULL;
	word = (char*)malloc(BUFFER * sizeof(char));
	int offset = 0;
	int  sentiment = 0;

	if (source == NULL || word == NULL) {
		printf("malloc failed in: read_from_file !");
		return;
	}
	if (fp == NULL) {
		printf("Eror reading file!! ");
		return NULL;
	}

	printf("Rijeci sa sentimentom: \n");

	while (!feof(fp)) {
		fgets(source, BUFFER, fp);
		sscanf(source, " %s %d %n", word, &sentiment, &offset);
		while (offset != 0) {
			append_word(head, word, sentiment);
			printf(" %s : %d \n", word, sentiment);
			source += offset;
			offset = 0;
			sscanf(source, " %s %d %n", word, &sentiment, &offset);
		}
	}
	printf("\n");
}


/*
Funckija: append_word
pomocna funkcija funkcije read_from_file
Funckija prima rijec i sentiment te razdvaja rijec na slova te ih salje u drugu funkciju za spremanje
rijeci u strukturu 'Trie' slovo po slovo. Kada se dodje na kraj rijeci, sprema se sentiment na zadnje mjesto
i njegov tip (1 za kraj recenice),
Return: /
*/

void append_word(position head, char* word, int sentiment) {
	char caracter;
	int type = 0;
	int offset = 0;

	if (NULL == word) {
		printf("Eror appending word! \n");
		return NULL;
	}

	sscanf(word, " %c%n", &caracter, &offset);
	while (offset != 0) {
		head = append_caracter(head, caracter);
		word += offset;
		offset = 0;
		sscanf(word, " %c%n", &caracter, &offset);

	}
	sscanf(word, " %d%n", &type, &offset);
	word += offset;

	if (sentiment > 1 || sentiment < -1) {
		printf("Eror reading sentiment!! It must be in range <-1,1> and will not be included in trie:  ");
	}
	else {
		head->sentiment = sentiment;
		head->isEndOfWord = true;
	}
}


/*
Funkcija: append_caracter
pomocna funkcija funkcije append_word
Funkcija prima slovo i ovisno o vrijednosti 'child' salje na daljnu obradu slovo u funciju 'create_child'
ili 'append_brother'. Pokazivac head se postavlja na mjesto gdje smo stavili rijec.
Return: position
*/

position append_caracter(position head, char caracter) {
	if (head->next_child == NULL)
		head = create_child(head, caracter);
	else if (head->next_child != NULL)
		head = append_brother(head, caracter);

	return head;
}


void delete_all(position head) {
	if (head == NULL)
		return;
	delete_all(head->next_brother);
	delete_all(head->next_child);
	free(head);
}
