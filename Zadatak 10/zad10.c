#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define BUFFER 256

typedef struct Node* position;
struct Node {
	int Number;
	char Operand;
	position Left, Right, Next;
};

position initialize();
position readFromFile();
position separate(char*);
bool isOperand(char);
void pushNumber(position, int);
void pushOperand(position, char);
position popNumber(position);

int main() {
	position main = readFromFile();
}

position initialize() {
	position new = (position)malloc(sizeof(struct Node));
	if (new == NULL)  return NULL;
	new->Right = NULL;
	new->Left = NULL;
	new->Next = NULL;
	return new;
}

position readFromFile() {
	FILE* fp = fopen("postfix.txt","r");
	if (fp == NULL) return NULL;

	char postfix[BUFFER];
	fgets(postfix, BUFFER, fp);

	fclose(fp);
	return separate(postfix);
}

position separate(char* postfix) {
	position head = initialize();
	int number = 0;
	int offset = 0;
	int i = 0;

	while (sscanf(postfix, "%d%n ", &number, &offset) > 0) {
		postfix += offset;
		pushNumber(head, number);
		i = 0;
		while (postfix[i] != '\0' && !isdigit(postfix[i])) {
			if (isOperand(postfix[i]))
				pushOperand(head, postfix[i]);
			i++;
		}
		postfix += i;
	}
	return head;
}

bool isOperand(char operand) {
	if (operand >= 40 && operand <= 47)
		return true;
	else
		return false;
}

void pushNumber(position head, int number) {
	if (head == NULL) return;
	position tmp = initialize();
	if (tmp == NULL) return;

	tmp->Number = number;
	tmp->Operand = '\0';

	tmp->Next = head->Next;
	head->Next = tmp;
}

void pushOperand(position head, char operand) {
	if (head == NULL) return;
	position tmp = initialize();
	if (tmp == NULL) return;

	tmp->Right = popNumber(head);
	tmp->Left = popNumber(head);
	tmp->Operand = operand;

	tmp->Next = head->Next;
	head->Next = tmp;
}

position popNumber(position head) {
	if (head == NULL || head->Next == NULL) return NULL;
	position tmp = head->Next;
	head->Next = head->Next->Next;
	tmp->Next = NULL;
	return tmp;
}


