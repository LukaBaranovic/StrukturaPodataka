/*
Trentuno u radu.
Funkcije:
-napravi direktorij
-napravi poddirektorij
-ispisi direktorije
-ispisi poddirektorije
*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 256

typedef struct Node* position;

struct Node {
	int data;
	position next_brother;
	position next_child;
};

position create_root(int);
void append_brother(position);
void display_brother(position);
int count_brother(position);

void create_child(position);
void enter_child(position);

int main() {
	position directory = create_root(0);
	create_child(directory);
	enter_child(directory);

}







position create_root(int x) {
	position head = (position)malloc(sizeof(struct Node));
	head->next_brother = NULL;
	head->next_child = NULL;
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	if (x == 0) {
		printf("Unesite direktorij: ");
	}
	if (x == 1) {
		printf("Unesite poddirektorij: ");
	}

	scanf(" %d", &tmp->data);
	head->next_brother = tmp;
	return head;
}


void append_brother(position head) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	printf("Unesite direktorij: ");
	scanf(" %d", &tmp->data);

	tmp->next_brother = head->next_brother;
	head->next_brother = tmp;
}

void display_brother(position head) {
	position tmp = head;
	int counter = 1;

	tmp = tmp->next_brother;
	while (NULL != tmp) {
		printf("<%d>  %d  ",counter++, tmp->data);
		tmp = tmp->next_brother;
	}
	printf(" \n");
}


int count_brother(position head) {
	position tmp = head;
	int count = 0;
	while (NULL != tmp->next_brother) {
		count++;
		tmp = tmp->next_brother;
	}
	return count;
}

void create_child(position head) {
	int selection;
	display_brother(head);
	printf("Izaberite broj gdje zelite napraviti poddirektorij: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		head = head->next_brother;
		selection--;
	}
	head->next_child = create_root(1);
}
 

void enter_child(position head) {
	int selection;
	display_brother(head);
	printf("Od kojeg direktorija zelite pogleadi poddirektorije: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	
	head = head->next_child;

	if (head == NULL) {
		printf("Vas direktorij ne sadrzi poddirektorije!!!\n");
	}
	else {
		printf("Poddirektoriji: ");
		display_brother(head);
	}
}

