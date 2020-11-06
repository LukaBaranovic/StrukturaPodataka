#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polynom* position;
struct polynom {
	int value;
	int exponent;
	position next;
};

int line_counter(FILE*);
void read_from_file(FILE*, int, position *);
void insert_to_list(int, int, position);
void show(int, position *);
position create_list(int);
void polynom_sum(position* head, int);

int main() {
	int i, j, n;
	FILE* file_1;
	file_1 = fopen("4zadatak.txt", "r");
	if (file_1 == NULL)
		printf("file reading eror...\n");
	int number_of_polynom = line_counter(file_1);

	position* head = create_list(number_of_polynom);


	read_from_file(file_1, number_of_polynom, head);

	show(number_of_polynom , head);

	polynom_sum(number_of_polynom, head);

	show(number_of_polynom, head);




	


	fclose(file_1);
}


int line_counter(FILE* f) {
	int counter = 0;

	while (!feof(f)) {
		if (getc(f) == '\n')
			counter = counter + 1;
	}
	rewind(f);
	return counter;
}

void read_from_file(FILE* f, int n, position *head) {
	int i = 0,val,e;

	for (i = 0; i < n; i++) {
		fscanf(f, "%d %d", &val, &e);
		insert_to_list(val, e, head[i]);
		fscanf(f, "%d %d", &val, &e);
		insert_to_list(val, e, head[i]);
	}
	


}

void insert_to_list(int val, int e, position head) {
	position tmp = NULL;
	tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;

	tmp->value = val;
	tmp->exponent = e;

	tmp->next = head->next;
	head->next = tmp;
}

void show(int n, position *head) {
	int i;
	position tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;

	for (i = 0; i < n + 2; i++) {
		tmp = head[i];

		if (tmp->next != 0) {
			printf("%d. polinom: ", i + 1);
		}

		while (tmp->next != NULL) {
			tmp = tmp->next;
			printf(" %d^(%d) ",tmp->value, tmp->exponent);
		}
		printf(" \n");
		
	}

}

position create_list(int n) {
	n = n + 2;
	int i;

	position* head = (position*)malloc(n * sizeof(position));
	for (i = 0; i < n; i++) {
		position tmp = (position)malloc(sizeof(struct polynom));
		tmp->next = NULL;
		head[i] = tmp;
	}
	return head;
}

void polynom_sum(position *head,int n) {
	position tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;
	int i;

	
	for (i = 0; i < n; i++) {
		tmp = head[i];
		tmp = tmp->next;

		while (tmp != NULL) {
			insert_to_list(tmp->value, tmp->exponent, head[n]);
		}
	}
}