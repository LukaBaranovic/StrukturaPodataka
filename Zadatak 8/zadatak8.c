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

void display_directory_main(position, int);
void rename_directory(position);

void create_child(position);
void enter_child(position);



void chose_delete_brother(position);
void delete_brother(position);



int main() {
	position directory = create_root(0);
	int loop = 1, action;

	printf("(1) Dodaj direktorij \n");
	printf("(2) Dodaj poddirektorij \n");
	printf("(3) Udji u odredjeni direktorij \n");
	printf("(4) Prikazi direktorij \n");
	printf("(5) Prikazi sve direktorije i sve njihove poddirektorije \n");
	printf("(6) Preimenuj direktorij \n");
	printf("(00) Izadji iz programa \n");

	while (loop == 1) {
		printf("\n Izaberi radnju: ");
		scanf("%d", &action);

		switch (action) {
		case 1:
			append_brother(directory);
			break;
		case 2:
			create_child(directory);
			break;
		case 3:
			enter_child(directory);
			break;
		case 4:
			display_brother(directory);
			break;
		case 5:
			display_directory_main(directory, 0);
			break;
		case 6:
			rename_directory(directory);
			break;
		case 00:
			loop = 0;
			break;
		default:
			printf("Nepostojeca radnja!!\n");
			break;
		}
	}
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
	if (head->next_child != NULL) {
		append_brother(head->next_child);
	}
	else
	{
		head->next_child = create_root(1);
	}
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


	}
}

void display_directory_main(position head,int offset) {
	position tmp = head;
	int i;
	

	while (tmp->next_brother != NULL) {
		tmp = tmp->next_brother;
		for (i = 0; i < offset; i++) {
			printf("  ");
		}
		printf("-%d \n", tmp->data);

		if (tmp->next_child != NULL)
			display_directory_main(tmp->next_child, offset + 1);

	}
}

void rename_directory(position head) {
	int selection;
	int renamed;
	display_brother(head);
	printf("Koji direktorij zelite preimenovati: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}
	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	printf("Upisite novu vrijednost: ");
	scanf(" %d", &renamed);
	head->data = renamed;
}






/*neradi trenutno*/


void chose_delete_brother(position head) {
	int selection;
	display_brother(head);
	printf("Izaberite koji direktorij zelite obrisati: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	
	
	delete_brother(head); 
	position tmp = head;
	free(tmp);
	head = head->next_brother;
	
}

void delete_brother(position head) {
	position tmp;


	if (head->next_child != NULL) {	
		tmp = head;
		head = head->next_child;
		free(tmp);
		delete_brother(head->next_child);
	}
	if (head->next_brother != NULL) {
		tmp = head;
		head = head->next_brother;
		free(tmp);
		delete_brother(head->next_brother);
	}
}
