#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node* position;
struct Node {
	int value;
	position left, rigth;
};

position initialize();
position appendNew(position);
position append(position, int);

void display(position, int);
void displayOptions();
void printDifference(int);
void start();
void doOption(position);


void searchSpecific(position);
bool search(position, int);

position findMin(position);
position findMax(position);

void deleteSpecific(position);
position delete(position, int);
position find(position, int);


void main(){
	start();
}


void doOption(position head) {
	int option, loop = 1;

	while (loop == 1) {
		displayOptions();
		printf("Chose an option: ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			head = appendNew(head);
			break;
		case 2:
			display(head->rigth, 0);
			break;
		case 3:
			searchSpecific(head->rigth);
			break;
		case 4:
			deleteSpecific(head);
			break;
		case 0:
			loop = 0;
			break;
		default:
			break;
		}
	}
}

void displayOptions() {
	printf("(1) Insert element \n");
	printf("(2) Display element/elements \n");
	printf("(3) Search for element \n");
	printf("(4) Delete element \n");
	printf("(0) Exit program \n");
}

void start() {
	position binaryTree = initialize();
	doOption(binaryTree);
}


position delete(position head,int number){
	if (NULL == head) return;

	if (head->value == number) {
		if (NULL != head->left) {
			position new = findMax(head->left);
			head->value = new->value;
			head->left = delete(head->left, new->value);
		}
		else if (NULL != head->rigth) {
			position new = findMin(head->left);
			head->value = new->value;
			head->rigth = delete(head->rigth, new->value);
		}
		else {
			free(head);
			return NULL;
		}
	}
}

void deleteSpecific(position head) {
	int number = 0;
	printf("Insert number to delete: ");
	scanf(" %d", &number);
	if (search(head->rigth, number) == true) 
		delete(find(head->rigth, number), number);
	else
		printf("Inserted element does not exist! \n");
		
}

position findMin(position head) {
	if (NULL == head) return NULL;
	while (NULL != head->left)
		head = head->left;
	return head;
}

position findMax(position head){
	if (NULL == head) return NULL;
	while (NULL != head->rigth)
		head = head->rigth;
	return head;
}


void searchSpecific(position head) {
	int number;
	printf("Insert a number for search:  ");
	scanf(" %d", &number);
	if (search(head->rigth, number) == true)
		printf("Element exists! \n");
	else
		printf("Element does not exist! \n");
	return;
}


position find(position head, int number) {
	if (NULL == head)
		return NULL;
	if (head->value == number)
		return	head;
	if (head->value < number)
		find(head->rigth, number);
	else
		find(head->left, number);
}

bool search(position head, int number) {

	if (NULL == head)
		return false;
	if (head->value == number)	
		return	true;
	if (head->value < number)	
		search(head->rigth, number);
	else    
		search(head->left, number);
}


void display(position head, int difference) {
	if (head == NULL) return;
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
	printf("Insert value: ");
	scanf(" %d", &value);
	return append(head, value);
}


position append(position head, int value) {
	if (head == NULL) {
		head = initialize();
		head->value = value;
		return head;
	}
	else {
		if (head->value < value)
			head->rigth = append(head->rigth, value);
		else if (head->value > value)
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
