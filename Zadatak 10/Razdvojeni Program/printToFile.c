#include "printToFile.h"

bool isOperand(char operand) {
	if (operand >= 40 && operand <= 47)
		return true;
	else
		return false;
}

void infixToFile(position head) {
	if (head == NULL) return;
	FILE* fp = fopen("infix.txt", "w");
	if (fp == NULL) return;

	printToFile(head->Next, fp);

	fclose(fp);
}

void printToFile(position head, FILE* fp) {
	if (head == NULL) return;
	printToFile(head->Left, fp);

	if (isOperand(head->Operand))
		fprintf(fp, " %c ", head->Operand);
	else
		fprintf(fp, " %d ", head->Number);

	printToFile(head->Right, fp);
}