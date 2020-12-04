#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

typedef struct stog *position;
struct stog {
	int x;
	position next;
};


void push_stog(position);
void pop_stog(position);
void push_red(position);


int main() {
	position head = (position)malloc(sizeof(struct stog));
	head->next = NULL;



	int action, loop = 1;
	printf("Unesite radnju za stog: \n");
	printf("(1) Push \n");
	printf("(2) Pop  \n");


	while (loop == 1) {
		scanf(" %d", &action);
		switch (action) {
		case 1:
			push_stog(head);
			break;

		case 2:
			pop_stog(head);
			break;

		default:
			break;
		}
	}




}

void push_stog(position head) {
	position tmp = NULL;
	tmp = (position)malloc(sizeof(struct stog));
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower;
	printf("Push broj: %d \n", num);

	tmp->x = num;

	tmp->next = head->next;
	head->next = tmp;
}

void pop_stog(position head) {
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

void push_red(position last) {
	int upper = 100, lower = 10;

	int num = (rand() % (upper - lower + 1)) + lower;
	printf("Push broj: %d \n", num);
	
	position tmp = (position)malloc(sizeof(struct stog));
	tmp->x = num;
	tmp->next = NULL;





	


}
