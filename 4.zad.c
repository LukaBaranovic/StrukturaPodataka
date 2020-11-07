/* 4. zadatak -trenutno samo za ispis iz datoteke i sortirani upis u listu */



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
position create_list(int);
void read_from_file(FILE *, position*, int);
void sorted_insert(int,int,position);
void show(int, position *);
void polynom_sum(int ,position);

int main() {
	int i, j, n;
	FILE* file_1;
	file_1 = fopen("kraj4zad.txt", "r");
	if (file_1 == NULL)
		printf("file reading eror...\n");
	int number_of_polynom = line_counter(file_1);

	position* head = create_list(number_of_polynom);

	read_from_file(file_1, head, number_of_polynom);

	show(number_of_polynom, head);


	system("pause");
}








int line_counter(FILE* f) {
	int counter = 0;

	while (!feof(f)) {
		if (getc(f) == '\n')
			counter = counter + 1;
	}
	rewind(f);
	return counter+1;
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

void read_from_file(FILE *f, position *head, int n) {

	int i, j,val,exp, mat[2];
	int enter = 0;
	int space = 1;
	char c;

	while (!feof(f)) {
		c = getc(f);

		if (c == '\n') {
			mat[enter] = space / 2;
			space = 1;
			enter = enter + 1;
		}
		if (c == ' ')
			space = space + 1;

	}
	mat[enter] = space / 2;
	rewind(f);

	for (i = 0; i < n; i++) {
		for (j = 0; j < mat[i]; j++) {
			fscanf(f, "%d %d", &val, &exp);
			sorted_insert(val ,exp, head[i]);
		}
	}


}

void sorted_insert(int val, int exp, position head) {
	position tmp;
	tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;

	
	while ((head->next != NULL) && (exp < head->next->exponent))
		head = head->next;

	tmp->value = val;
	tmp->exponent = exp;

	tmp->next = head->next;
	head->next = tmp;
}

void show(int n, position* head) {
	int i;
	position tmp;

	for(i=0;i<n;i++){
		printf("%d. polinom: ", i + 1);
		tmp = head[i];
		while (tmp->next != NULL) {
			tmp = tmp->next;
			
			if (tmp->exponent > 1) 
				printf(" %dx^(%d) ", tmp->value, tmp->exponent);
			if (tmp->exponent == 1) 
				printf(" %dx ", tmp->value);
			if (tmp->exponent == 0) 
				printf(" %d ", tmp->value);
			
		}
		printf("\n");
	}
}


