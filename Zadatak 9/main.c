#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* position;

struct Node {
	int Number;
	position Left, Right;
};

position initialize();
void displayOptions();
void printDifference(int);
position appendNew(position);
position append(position, int);
void search(position);
position find(position, int);
position findMinimum(position);
position findMaximum(position);
void deleteAll(position);
void display(position, int);
void doOption(position);
position deleteSpecific(position);
position delete(position, int);
void start();


int main() {
	start();
}


void start() {
	position main = initialize();
	doOption(main);
}

position delete(position head, int number) {
	if (head == NULL) return NULL;
	if (head->Number < number)
		head->Right = delete(head->Right, number);
	else
		head->Left = delete(head->Left, number);
	if (head->Number == number) {
		if (head->Right == NULL) {
			position tmp = head->Left;
			free(head);
			return tmp;
		}
		else if (head->Left == NULL) {
			position tmp = head->Right;
			free(head);
			return tmp;
		}
		else {
			position tmp = findMinimum(head->Right);
			head->Number = tmp->Number;
			head->Right = delete(head->Right, tmp->Number);
		}
	}
	return head;
}

position deleteSpecific(position head) {
	int number = 0;
	printf("Insert element to delete: ");
	scanf(" %d", &number);
	return delete(head, number);
}

void doOption(position head) {
	int option = 0, loop = 1;

	while (loop == 1) {
		displayOptions();
		printf("Chose an option: ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			head = appendNew(head);
			break;
		case 2:
			display(head->Right, 0);
			break;
		case 3:
			search(head->Right);
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


void display(position head, int difference) {
	if (head == NULL) return;
	printf(" %d \n", head->Number);
	if (NULL != head->Left) {
		printDifference(difference);
		printf("Left part:  ");
		display(head->Left, difference + 2);
	}
	if (NULL != head->Right) {
		printDifference(difference);
		printf("Right part: ");
		display(head->Right, difference + 2);
	}
}


void deleteAll(position head) {
	if (head == NULL) return 0;
	deleteAll(head->Left);
	deleteAll(head->Right);
	free(head);
}

position findMinimum(position head) {
	if (head->Left != NULL) return findMinimum(head->Left);
	return head;
}

position findMaximum(position head) {
	if (head->Right != NULL) return findMaximum(head->Right);
	return head;
}


void search(position head) {
	int number = 0;
	printf("Insert a number to search for:  ");
	scanf(" %d", &number);

	if (find(head, number) == NULL)
		printf("Element does not exist! \n");
	else
		printf("Element does exist! \n");
}

position find(position head, int number) {
	if (head == NULL) return NULL;
	if (head->Number == number) return head;
	if (head->Right < number)
		return find(head->Right, number);
	else
		return find(head->Left, number);
	return head;
}

position append(position head, int number) {
	if (NULL == head) {
		head = initialize();
		head->Number = number;
		return head;
	}
	else {
		if (head->Number == number)
			return NULL;
		else if (head->Number < number)
			head->Right = append(head->Right, number);
		else if (head->Number > number)
			head->Left = append(head->Left, number);
	}
	return head;
}

position appendNew(position head) {
	int number = 0;
	printf("Insert new element: ");
	scanf(" %d", &number);
	return append(head, number);
}

void displayOptions() {
	printf("(1) Insert element \n");
	printf("(2) Display element/elements \n");
	printf("(3) Search for element \n");
	printf("(4) Delete element \n");
	printf("(0) Exit program \n");
}

position initialize() {
	position new = (position)malloc(sizeof(struct Node));
	if (new == NULL) {
		printf("Malloc failed! \n");
		return NULL;
	}
	new->Left = NULL;
	new->Right = NULL;
	return new;
}

void printDifference(int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" ");
	}
}
