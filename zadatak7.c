/*
Program prima postfix izraz iz datoteke te se dok se to prima on paralelno racuna rezultat pomocu rada stoga.
Program sprema integer dok ne dodje do nekog operatora (+,-,*,/) te onda ovisno o operatoru radi matematicku 
operaciju zadnja 2 elementa te rezultat sprema na prvog a drugog brise. Program se ponavlja dok ne dobijemo konacni rezultat.
---Prvi put sam koristio funkciju strtok i pri pisanju u datoteci granica izmedju vise elemenata je ','.---
Elementi stoga se postepeno ispisuju dok se ocitavaju te takoder njihove operacije koje se dogadjaju (ukratko imamo
neki pregled kojim se redosljedom program izvrsava.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#define BUFFER 256


typedef struct Node* position;

struct Node {
	int number;
	position next;
};

position read_from_file();
void insert_as_integer(position,int);
void insert_as_char(position, char[]);
void calculate(position, char);
void display(position);


int main() {
	position postfix = read_from_file();



	printf("Rezultat postfix izraza je: "); display(postfix);
	printf("\n");
}

/* 
Funkcija: main
Nikakva posebna svrha u main-u, sluzi samo za poziv funkcije. */

position read_from_file() {
	FILE* f = fopen("postfix.txt", "r");
	char source[BUFFER];
	char border[4] = ",";
	char *token;
	char digit;

	if (f == NULL) {
		printf("Eror reading file!!");
		return NULL;
	}

	position head = (position)malloc(sizeof(struct Node));
	head->next = NULL;

	fgets(source, BUFFER, f);
	token = strtok(source, border);
	

	while (token != NULL) {
		printf(" %s\n", token);

		digit = token[0];

		if (isdigit(digit) != 0)
			insert_as_integer(head, atoi(token));
		else if (digit == '+' || digit == '-' || digit == '*' || digit == '/')
			calculate(head, digit);
		else
			printf("Eror: read_from_file! \n");

		token = strtok(NULL, border);
	}

	printf(" \n");
	return head;
}

/*  
Funkcija: read_from_file
Koristeci strtok razdvajam elemente upisanje u datoteci te ih dok ne dodjem do nekog operatora upisujem u stog.
Kada se dodje do nekog operatora vrsi se poziv funkcije 'calculate'.
Elementi stoga se ispisuje dok se ocitavaju.
*/

void insert_as_integer(position head,int x) {
	position tmp = (position)malloc(sizeof(struct Node));

	tmp->number = x;

	tmp->next = head->next;
	head->next = tmp;
}

/*
Funkcija: insert_as_integer
Sprema integer u stog na pocetak, pomocu atoi() funkcije string se pretvara u integer, a to je li neki char
integer smo provjerili pomocu isdigit() u funkciji read_from_file.
*/

void display(position head) {
	position tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
		printf(" %d  ", tmp->number);
	}
}

/*
Funkcija: display
Inace prikazuje cijelu vezanu listu,a u ovom programu pokazuje samo rezultat.
*/

void calculate(position head, char operand) {
	if (operand == '+') {
		printf(" %d + %d = %d \n", head->next->next->number, head->next->number, head->next->next->number + head->next->number);
		head->next->number = head->next->next->number + head->next->number;
	}
	else if (operand == '-') {
		printf(" %d - %d = %d \n", head->next->next->number, head->next->number, head->next->next->number - head->next->number);
		head->next->number = head->next->next->number - head->next->number;
	}
	else if (operand == '*') {
		printf(" %d * %d = %d \n", head->next->next->number, head->next->number, head->next->next->number * head->next->number);
		head->next->number = head->next->next->number * head->next->number;
	}
	else if (operand == '/') {
		printf(" %d / %d = %d \n", head->next->next->number, head->next->number, head->next->next->number / head->next->number);
		head->next->number = head->next->next->number / head->next->number;
	}
	else
		printf("Eror in calculating!!");

	position tmp = head->next->next;
	if (head->next->next->next != NULL)
		head->next->next = head->next->next->next;
	else
		head->next->next = NULL;
	free(tmp);
}

/*
Funkcija: calculate.
Provjerava o kojem se operatoru radi i vrsi matematicku operaciju ovisno o istom.
Nakon toga rezultat sprema na prvi od dva elementa u listi, a drugi se brise.
Ispisuju se operacije dok se program izvrsava.
*/

