/*
U RECENICAMA/RIJECIMA SE MOGU KORISTITI I VELIKA I MALA SLOVA I INTERPUNKCIJSKI ZNAKOVI

U datoteci predifiniramo vrijednost sentimenta odredenih rijeci koji program iscitaje i sprema u 'Trie'.
Zatim nas program pita da unesemo recenicu iz koje racuna vrijednost sentimenta s obzirom na rijeci.
Vrijednosti mogu bit pozitivne (+) za pozitvne rijeci, negativne (-) za negativne rijeci, a neutralne (0)
za sve rijeci koje nisu predifinirane u datoteci.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER 256


typedef struct Node* position;
struct Node {
	char caracter;
	int sentiment;
	bool isEndOfWord; 
	position next_brother;
	position next_child;
};



void read_from_file(position);
void append_word(position, char*, int);
void display_directory_main(position, int);
position append_caracter(position, char);
position create_child(position, char);
position append_brother(position, char);
int compare(position);
void calculate_sentiment(position head);
void delete_all(position);


int main() {
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
			loop = 0;
			break;
		}
	}

	delete_all(trie);
}


void read_from_file(position head) {
	FILE* fp = fopen("rijeci.txt", "r");
	char* source = NULL;
	source = (char*)malloc(BUFFER * sizeof(char));
	char* word = NULL;
	word = (char*)malloc(BUFFER * sizeof(char));

	if (fp == NULL) {
		printf("Eror reading file!! ");
		return NULL;
	}

	int offset = 0;
	int  sentiment = 0;

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
Funkcija: read_from_file
Funkcija cita iz datoteke rijeci i vrijednosti njihovih sentimenta sprema u strukturu 'Trie' 
po abecednom redu. Program vadi rijeci i sentiment jedno po jedno i salje u drugu funkciju 'append_word'
za daljnu obradu.
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

	head->sentiment = sentiment;
	head->isEndOfWord = true;
}

/*
Funckija: append_word 
pomocna funkcija funkcije read_from_file
Funckija prima rijec i sentiment te razdvaja rijec na slova te ih salje u drugu funkciju za spremanje
rijeci u strukturu 'Trie' slovo po slovo. Kada se dodje na kraj rijeci, sprema se sentiment na zadnje mjesto 
i njegov tip (1 za kraj recenice),
Return: /
*/

position append_caracter(position head, char caracter) {
	if (head->next_child == NULL)
		head = create_child(head, caracter);
	else if (head->next_child != NULL)
		head = append_brother(head, caracter);

	return head;
}

/*
Funkcija: append_caracter 
pomocna funkcija funkcije append_word
Funkcija prima slovo i ovisno o vrijednosti 'child' salje na daljnu obradu slovo u funciju 'create_child'
ili 'append_brother'. Pokazivac head se postavlja na mjesto gdje smo stavili rijec.
Return: position
*/

position append_brother(position head, char caracter) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;
	tmp->caracter = caracter;

	if (head->next_child->caracter > caracter) {
		tmp->next_brother = head->next_child;
		head->next_child = tmp;
		head = head->next_child;
		return head;
	}
	else {
		head = head->next_child;
		while (head->next_brother != NULL && (head->next_brother->caracter < caracter)) {
			head = head->next_brother;
		}
		if (head->caracter == caracter)
			return head;
		else {
			tmp->next_brother = head->next_brother;
			head->next_brother = tmp;
			head = head->next_brother;
			return head;
		}
	}
}

/*
Funckija: append_brother 
pomocna funkcija funkcije append_caracter
Funkcija postavlja slovo abecedno u 'siblings'.
Return: position
*/

position create_child(position head, char caracter) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	tmp->caracter = caracter;
	head->next_child = tmp;

	return head->next_child;
}

/*
Funkcija: create_child 
pomocna funkcija funkcije append_caracter
Ako je 'child' prazan on ga kreira i postavlja slovo na prvo mijesto.
Return: position
*/

void display_directory_main(position head, int offset) {
	position tmp = head;
	int i;

	while (tmp != NULL) {
		for (i = 0; i < offset; i++) {
			printf("  ");
		}
		printf("-%c \n", tmp->caracter);
		if (tmp->next_child != NULL)
			display_directory_main(tmp->next_child, offset + 1);

		if (tmp->isEndOfWord == true) {
			printf("Kraj rijeci!, sentiment: %d \n", tmp->sentiment);
		}
		tmp = tmp->next_brother;
	}
}

/*
Funckija: display_directory_main
Jedna od funkcija iz zadatka 8 koja mi je olaksala vizualizirati slova pri upisu.
Nema svrhe u ovom programu,
*/

int compare(position head,char *source) {
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
Funcija: compare
Funckija usporeduje neku rijec sa podaticima u strukturi Trie tako sto uzima slovo po slovo i tako
seta po strukturi Trie trazeci je li ta rijec upisana. Ako je onda vraca vrijednost sentimenta, a ako
nije vraca NULL.
Return: int
*/

void calculate_sentiment(position head) {
	int sentiment = 0;
	int offset = 0;
	char* source = NULL;
	source = (char*)malloc(BUFFER * sizeof(char));
	char* word = NULL;
	word = (char*)malloc(BUFFER * sizeof(char));

	scanf(" %[^\n]", source);

	sscanf(source, " %s  %n", word,  &offset);
	while (offset != 0) {
		sentiment = sentiment + compare(head->next_child, word);
		source += offset;
		offset = 0;
		sscanf(source, " %s %n", word, &offset);
	}
	printf(" Sentiment recenice je: %d \n", sentiment);
}

/*
Funkcija: calculate_sentiment
Funckija nas pita za unos recenice te potom razdvaja rijeci iz receneice i koristeci funkciju 'compare'
dobivamo sentimentalnu vrijednost svake rijeci i funkcija ispisuje zbroj.
Return: /
*/


void delete_all(position head) {
	if (head == NULL)
		return;
	delete_all(head->next_brother);
	delete_all(head->next_child);
	free(head);
}
