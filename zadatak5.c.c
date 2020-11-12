#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256


typedef struct list* position;
struct list {
	int x;
	position next;
};

position create_list();
void read_from_file(position *);
void insert(char*, position head);
void sorted_insert(int, position);
void show_specific(position);



int main() {
	int i, j;

	position* head = create_list();
	read_from_file(head);

	printf("\n\n 1.lista: ");
	show_specific(head[0]);

}

position create_list() {
	int i;

	position* head = (position*)malloc(2 * sizeof(position));
	for (i = 0; i < 2; i++) {
		position tmp = (position)malloc(sizeof(struct list));
		tmp->next = NULL;
		head[i] = tmp;
	}
return head;
}

void read_from_file(position *head) {
	int x = 0;
	char str[MAX];
	FILE* filename = fopen("lista.txt", "r");
	if (filename == NULL) {
		printf("Eror opening file... \n");
		return NULL;
	}

	while (fgets(str, MAX, filename) != NULL) {
		insert(str, head[x]);
		x++;
	}
}

void insert(char *str, position head) {
	int br = 0, compare = NULL;
	while (sscanf(str, " %d", &br) != NULL) {
		if (compare != br) {
			printf(" %d", br);
			sorted_insert(br, head);
		}
		str += 1;
		compare = br;
	}
}


/*ovdje imam pitanje:  jesam li dobro napravio ovo sa skeniranjem varijable i opcenito ovo sve sa funkcijom fgets jer
ju prvi put korisitm a predlozili ste mi je na proslom satu. Takoder neznam kako preskocit razmake pa mi ispisuje duple brojeve
tj. ispisuje mi brojeve po 2,3 puta (onoliko koliko razmaka ima). Tu sam napravio neki svoj algoritam koji usporedjuje zadnja 2 
broja al mislim da takav nacin nije najbolje pa ako znate kako to izvest da mi preskoci taj string na sljedeci broj da mi malo 
objasnite. Hvala. */

void sorted_insert(int br, position head) {
	position tmp = (position)malloc(sizeof(struct list));
	tmp->next = NULL;

	while (head->next != NULL && head->next->x >= br) {
		head = head->next;
	}

	if (br != head->x) {
		tmp->x = br;
		tmp->next = head->next;
		head->next = tmp;
	}

}

void show_specific(position head) {
	position tmp = head;

	while (tmp->next != NULL) {
		tmp = tmp->next;
		printf(" %d", tmp->x);
	}
	printf("\n");
}