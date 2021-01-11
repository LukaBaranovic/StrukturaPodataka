/*
Source file koji racuna vrijednost senitmenta neke rijeci.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "getSentiment.h"
#include "declaration.h"
#define BUFFER 256

/*
Funkcija: is_interpunction_last
Provjerava je li se nalazi interpunkcijski znak na pocetku rijeci, a ako je mice ga za offset (%n).
Return: char*
*/

char* is_interpunction_first(char* source) {
	char caracter;
	int offset = 0;
	sscanf(source, " %c%n", &caracter, &offset);
	if (caracter == '.' || caracter == ',' || caracter == '!' || caracter == ';' || caracter == ':') {
		source += offset;
	}
	return source;
}

/*
Funkcija: is_interpunction_last
Provjerava je li se interpunkcijski znak nalazi na kraju rijeci. Morao sam razdvojiti funkcije zbog toga jer kod nastavlja 'setati'
po rijeci i ako prijedje na interpunkcijski znak onda nema sentiment za vratiti, tj bool == false.
Return: bool
*/

bool is_interpunction_last(position tmp, int offset, char* source) {
	char caracter = NULL;
	if (tmp->isEndOfWord == true) {
		int sentiment = tmp->sentiment;
		sscanf(source + offset, "%c", &caracter);
		if (caracter == '.' || caracter == ',' || caracter == ';' || caracter == ':' || caracter == '!' || caracter == '?') {
			return true;
		}
		else
			return false;
	}
	return false;
}

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

	source = is_interpunction_first(source);
	sscanf(source, " %c%n", &caracter, &offset);

	while (offset != 0) {
		source += offset;
		offset = 0;
		while (tmp != NULL && toupper(tmp->caracter) != toupper(caracter)) {
			tmp = tmp->next_brother;
		}  if (tmp == NULL) {
			return NULL;
		}	else {
			if (tmp->next_child != NULL) {
				tmp = tmp->next_child;
			}		else {
				sscanf(source, " %c%n", &caracter, &offset);
				if (offset != 0) {
					return NULL;	}
				break;
			}
		}
		sscanf(source, " %c%n", &caracter, &offset);
		if (is_interpunction_last(tmp, offset, source) == true)		return tmp->sentiment;
	}
	if (tmp->isEndOfWord == true)	return tmp->sentiment;
	else   return 0;
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
	if (source == NULL || word == NULL) {
		printf("malloc failed in: calculate_sentiment");
		return;
	}

	scanf(" %[^\n]", source);

	printf("\n Sentence '%s' \n has sentiment evaluation of:  ", source);

	sscanf(source, " %s  %n", word, &offset);
	while (offset != 0) {
		sentiment = sentiment + compare(head->next_child, word);
		source += offset;
		offset = 0;
		sscanf(source, " %s %n", word, &offset);
	}
	printf("%lf \n\n", sigmoid(sentiment));
}

/*
Funkcija: sigmoid
Racuna sigmoid sentimenta 
1 / (1 + e^(sentiment)
Return: float
*/

float sigmoid(int sentiment) {
	float result;
	float e = 2.71828;

	result = 1 / (1 + pow(e, -sentiment));
	return result;
}
