/*
Source file koji racuna vrijednost senitmenta neke rijeci.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "getSentiment.h"
#include "declaration.h"
#define BUFFER 256



/*
Funcija: compare
Funckija usporeduje neku rijec sa podaticima u strukturi Trie tako sto uzima slovo po slovo i tako
seta po strukturi Trie trazeci je li ta rijec upisana. Ako je onda vraca vrijednost sentimenta, a ako
nije vraca NULL.
Return: int
*/

int compare(position head, char* source) {
	position tmp = head;
	char caracter = NULL;
	char checker = NULL;
	int offset = 0;
	int sentiment = 0;


	sscanf(source, " %c%n", &caracter, &offset);
	while (caracter == '.' || caracter == ',' || caracter == '!' || caracter == ';' || caracter == ':') {
		source += offset;
		sscanf(source, " %c%n", &caracter, &offset);
	}

	while (offset != 0) {
		source += offset;
		offset = 0;

		while (tmp != NULL && toupper(tmp->caracter) != toupper(caracter)) {
			tmp = tmp->next_brother;
		}
		if (tmp == NULL) {
			return NULL;
		}
		else {
			if (tmp->next_child != NULL) {
				tmp = tmp->next_child;
			}
			else {
				sscanf(source, " %c%n", &caracter, &offset);
				if (offset != 0) {
					return NULL;
				}
				break;
			}
		}

		sscanf(source, " %c%n", &caracter, &offset);

		if (tmp->isEndOfWord == true) {
			sentiment = tmp->sentiment;
		}
		if (sentiment != 0) {
			sscanf(source + offset, "%c", &checker);
			if (checker == '.' || checker == ',' || checker == ';' || checker == ':' || checker == '!' || checker == '?') {
				return sentiment;
			}
			else
				sentiment = 0;
		}
	}

	if (tmp->isEndOfWord == true)
		return tmp->sentiment;
	else
		return NULL;
}

/*
Funkcija: calculate_sentiment
Funckija nas pita za unos recenice te potom razdvaja rijeci iz receneice i koristeci funkciju 'compare'
dobivamo sentimentalnu vrijednost svake rijeci i funkcija ispisuje zbroj.
Return: /
*/


void calculate_sentiment(position head) {
	int sentiment = 0;
	int offset = 0;
	char* source = NULL;
	source = (char*)malloc(BUFFER * sizeof(char));
	char* word = NULL;
	word = (char*)malloc(BUFFER * sizeof(char));

	scanf(" %[^\n]", source);

	sscanf(source, " %s  %n", word, &offset);
	while (offset != 0) {
		sentiment = sentiment + compare(head->next_child, word);
		source += offset;
		offset = 0;
		sscanf(source, " %s %n", word, &offset);
	}
	printf(" Sentiment recenice je: %d \n", sentiment);
}