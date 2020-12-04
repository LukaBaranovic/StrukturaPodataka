#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

typedef struct stog *position;
struct stog {
	int x;
	position next;
};

void push(position);
void pop(position);


int main() {
	position head = NULL;
	head = (position)malloc(sizeof(struct stog));
	int action, loop=1;
	printf("Unesite radnju: \n");
	printf("(1) Push \n");
	printf("(2) Pop  \n");
	

	while (loop == 1) {
		scanf(" %d", &action);
		switch (action) {
		case 1:
			push(head);
			break;

		case 2:
			pop(head);
			break;

		default:
			break;

		}
	}


}

void push(position head) {
	position tmp = NULL;
	tmp = (position)malloc(sizeof(struct stog));
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower; 
        printf("Push broj: %d \n", num); 

	tmp->x = num;

	tmp->next = head->next;
	head->next = tmp;
}

void pop(position head) {
	if (NULL != head->next) {

		position tmp;
		tmp = head->next;
		head->next = tmp->next;

		printf("Pop broj:  %d \n", tmp->x);
		free(tmp);
	}
	else
		printf("Stog je prazan!!! \n");
}
