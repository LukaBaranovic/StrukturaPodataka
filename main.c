#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Node* position;
struct Node {
	int value;
	position left, rigth;
};

position initialize();
position appendNew(position);
position append(position, int);
void display(position, int);
void printDifference(int);
void start();



void main(){
	start();
}

void start() {
	position binaryTree = initialize();
	binaryTree = appendNew(binaryTree);
	binaryTree = appendNew(binaryTree);
}





void display(position head, int difference) {
	if (head == NULL) return NULL;
	printf(" %d \n", head->value);
	if (NULL != head->left) {
		printDifference(difference);
		printf("Left part:  ");
		display(head->left, difference + 2);
	}
	if (NULL != head->rigth) {
		printDifference(difference);
		printf("Right part: ");
		display(head->rigth, difference + 2);
	}
}

void printDifference(int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" ");
	}
}

position appendNew(position head){
	int value = 0;
	printf("Unesite vrijednost: ");
	scanf(" %d", &value);
	return append(head, value);
}

position append(position head, int value) {
	if (head == NULL) {
		head = initialize();
		head->value = value;
		return value;
	}
	else {
		if (head->value > value)
			head->rigth = append(head->rigth, value);
		else if (head->value < value)
			head->left = append(head->left, value);
		else
			return NULL;
	}
	return head;
}


position initialize() {
	position new = (position)malloc(sizeof(struct Node));
	if (new == NULL) {
		printf("Malloc failed! \n");
		return NULL;
	}
	new->left = NULL;
	new->rigth = NULL;
	return new;
}