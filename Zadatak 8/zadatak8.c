#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 256

typedef struct directory* position;

struct directory {
	char name[BUFFER];
	position next_child;
	position prev_child;
	position next_brother;
	position prev_brother;
};

void append_brother(position);
void display_brother(position);
int count_brother(position);

void chose_directory(position);
void create_child(position);
void display_child(position);



int main() {
	position tree = (position)malloc(sizeof(struct directory));
	tree->next_child = NULL;
	tree->next_brother = NULL;
	int loop = 1;
	int action;



	printf("Unesite prvi direktorij: \n");
	append_brother(tree);


	printf("Unesite radnju: \n");
	printf("(1) Unesite direktorij \n");
	printf("(2) Prikazite direktorije \n");
	printf("(3) Prikazite poddirektorije \n");
	printf("(4) Unesi poddirektorij");
	printf("(0) Izlaz iz programa\n");

	while (loop == 1) {
		scanf(" %d", &action);

		switch (action) {
		case 1:
			append_brother(tree);
			break;
		case 2:
			display_brother(tree);
			break;
		case 4:
			chose_directory(tree);
			break;
		case 0:
			loop = 0;
			break;
		default:
			printf("Nepostojeca akcija!! \n\n");
			break;
		}

	}


	display_child(tree);



}


void append_brother(position head) {
	position tmp = (position)malloc(sizeof(struct directory));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;
	int loop = 1;

	printf("Unesite ime za direktorij:  ");
	scanf(" %[^\n]", tmp->name);

	
	while (head->next_brother != NULL && loop == 1) {
		if (strcmp(tmp->name, head->next_brother->name) > 0)
			head = head->next_brother;
		else
			loop = 0;
	}
	

	if (head->next_brother != NULL) {
		tmp->next_brother = head->next_brother;
		tmp->next_brother->prev_brother = tmp;
		tmp->prev_brother = head;
		head->next_brother = tmp;
	}
	else {
		head->next_brother = tmp;
		tmp->prev_brother = head;
	}
}


void display_brother(position head) {
	position tmp = head;
	int counter = 1;
	while (tmp->next_brother != NULL) {
		tmp = tmp->next_brother;
		printf("(%d)  %s  ",counter++, tmp->name);
	}
	printf(" \n");
}


int count_brother(position head) {
	position tmp = head;
	int count = 0;
	while (tmp->next_brother != NULL) {
		tmp = tmp->next_brother;
		count++;
	}
	return count;
}


void chose_directory(position head) {
	int loop = 1;
	int selection;
	printf("Kada birate morate unijeti broj lijevo od direktorija!! \n");
	display_brother(head);
	printf("Unesite pod kojim direktorijem zelite napraviti poddirektorij: \n");

	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Odabrali ste nevaljani direktorij, molimo vas pokusajte ponovno: ");
		scanf(" %d", &selection);
	}
	while (selection > 0) {
		head = head->next_brother;
		selection--;
	}

	create_child(head);
}


void create_child(position head) {
	position tmp = (position)malloc(sizeof(struct directory));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	printf("Unesite naziv za poddirektorij:  ");
	scanf(" %[^\n]", tmp->name);

	head->next_child = tmp;
	tmp->prev_child = head;

}

void display_child(position head) {
	position tmp = head;
	int selection;
	printf("Od kojeg direktorija zelite vidjeti poddirektorije: \n");
	display_brother(head);
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Odabrali ste nevaljani direktorij, molimo vas pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		head = head->next_brother;
		selection--;
	}

	if (head->next_child == NULL)
		printf("U %s direktoriju nema poddirektorija!! \n", head->name);
	else {
		printf("Poddirektorij %s direktorija: \n", head->name);
		head = head->next_child;
		display_brother(head);
	}


}
