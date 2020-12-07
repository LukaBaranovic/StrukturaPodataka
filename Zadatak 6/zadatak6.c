/*
Program pita korisnika sto zeli stimulirat (rad stoga,rad reda ili izlaz iz programa).
Kada se izabere rad stoga/reda mozemo birati je li zelimo napraviti push ili pop funkciju.
Kada zelimo se vratit na pocetak onda izaberemo (0) i potom se svi preostali elementi
iz stoga/reda ispisuju te opet mozemo birati radnju.
Vracamo se na pocetak i opet mozemo birati sto zelimo stimulirati ili sa (0) se izlazi iz programa.
Unosom neke radnje koja ne postoji (razlicito od (0) (1) (2) program nam to kaze i opet biramo.
*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

typedef struct Node* position;
struct Node {
	int x;
	position next;
};

void push_stog(position);
void pop(position);
void push_red(position);


int main() {
	position stog = (position)malloc(sizeof(struct Node));
	stog->next = NULL;
	position red = (position)malloc(sizeof(struct Node));
	position last = (position)malloc(sizeof(struct Node));
	red->next = NULL;
	last->next = red;

	int action,loop1=1, loop2 = 1;


	while (loop1 == 1) {
		printf("Unesite sto zelite stimulirati: \n");
		printf("(1) Stog \n");
		printf("(2) Red  \n");
		printf("(0) Exit \n\n");
		scanf(" %d", &action);


		switch (action) {

		case 1:
			loop2 = 1;
			printf("Unesite radnju za stog: \n");
			printf("(1) Push \n");
			printf("(2) Pop  \n");
			printf("(0) Return \n");
			while (loop2 == 1) {
				scanf(" %d", &action);
				switch (action) {
				case 1:
					push_stog(stog);
					break;

				case 2:
					pop(stog);
					break;

				case 0:
					loop2 = 0;
					while (stog->next != NULL)
						pop(stog);
					break;

				default:
					printf("Ta radnja ne postoji! ");
					break;
				}
			}
			break;

		case 2:
			loop2 = 1;
			printf("Unesite radnju za red: \n");
			printf("(1) Push \n");
			printf("(2) Pop  \n");
			printf("(0) Return \n");

			while (loop2 == 1) {
				scanf(" %d", &action);
				switch (action) {
				case 1:
					push_red(last);
					break;

				case 2:
					pop(red);
					break;

				case 0:
					loop2 = 0;
					while (red->next != NULL)
						pop(red);
					break;

				default:
					printf("Ta radnja ne postoji! ");
					break;
				}
			}
			break;

		case 0:
			loop1 = 0;
			break;

		default:
			printf("Ta radnja ne postoji! ");
			break;
		}
	}
}

/*Funckija push_stog koja postavlja slucajno generirani broj na pocetak stoga.
STOG - LAST IN - FIRST OUT
*/

void push_stog(position head) {
	position tmp = NULL;
	tmp = (position)malloc(sizeof(struct Node));
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower;
	printf("Push broj: %d \n", num);

	tmp->x = num;

	tmp->next = head->next;
	head->next = tmp;
}

/*Funkcija pop koja skida slucajno generirani broj sa vrha (pocetka) stoga ili red. */

void pop(position head) {
	if (NULL != head->next) {

		position tmp;
		tmp = head->next;
		head->next = tmp->next;

		printf("Pop broj:  %d \n", tmp->x);
		free(tmp);
	}
	else
		printf("Stog/red je prazan!!! \n");
}

/*Funckija push_red koja prima adresu zadnjeg elementa reda uz pomoc pomocne liste postavlja
slucajno generirani broj na kraj reda.
RED - FIRST IN - FIRST OUT
*/

void push_red(position last) {
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower;
	printf("Push broj: %d \n", num);

	position tmp = (position)malloc(sizeof(struct Node));
	tmp->x = num;
	tmp->next = NULL;

	last->next->next = tmp;
	last->next = last->next->next;
}
