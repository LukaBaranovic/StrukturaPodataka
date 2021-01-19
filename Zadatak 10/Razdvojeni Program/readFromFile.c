#include "readFromFile.h"

position readFromFile() {
	FILE* fp = fopen("postfix.txt", "r");
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