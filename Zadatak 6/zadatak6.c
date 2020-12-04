#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

typedef struct stog *position1;
struct stog {
	int x;
	position1 next;
};

typedef struct red *position2;
struct red {
	int x;
	position2 next;
};

void push(position1);
void pop(position1);


int main() {
	position1 head_stog = NULL;
	head_stog = (position1)malloc(sizeof(struct stog));
	head_stog->next = NULL;
	int action, loop = 1;
	printf("Unesite radnju: \n");
	printf("(1) Push \n");
	printf("(2) Pop  \n");


	while (loop == 1) {
		scanf(" %d", &action);
		switch (action) {
		case 1:
			push(head_stog);
			break;

		case 2:
			pop(head_stog);
			break;

		default:
			break;

		}
	}


}

void push(position1 head) {
	position1 tmp = NULL;
	tmp = (position1)malloc(sizeof(struct stog));
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower;
	printf("Push broj: %d \n", num);

	tmp->x = num;

	tmp->next = head->next;
	head->next = tmp;
}

void pop(position1 head) {
	if (NULL != head->next) {

		position1 tmp;
		tmp = head->next;
		head->next = tmp->next;

		printf("Pop broj:  %d \n", tmp->x);
		free(tmp);
	}
	else
		printf("Stog je prazan!!! \n");
}
