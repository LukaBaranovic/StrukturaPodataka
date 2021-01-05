/*
Source file koji postavlja slovo na odredeno mjesto.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fileReading.h"
#include "declaration.h"
#define BUFFER 256


/*
Funckija: append_brother
pomocna funkcija funkcije append_caracter
Funkcija postavlja slovo abecedno u 'siblings'.
Return: position
*/

position append_brother(position head, char caracter) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;
	tmp->caracter = caracter;

	if (head->next_child->caracter > caracter) {
		tmp->next_brother = head->next_child;
		head->next_child = tmp;
		head = head->next_child;
		return head;
	}
	else {
		head = head->next_child;
		while (head->next_brother != NULL && (head->next_brother->caracter < caracter)) {
			head = head->next_brother;
		}
		if (head->caracter == caracter)
			return head;
		else {
			tmp->next_brother = head->next_brother;
			head->next_brother = tmp;
			head = head->next_brother;
			return head;
		}
	}
}

/*
Funkcija: create_child
pomocna funkcija funkcije append_caracter
Ako je 'child' prazan on ga kreira i postavlja slovo na prvo mijesto.
Return: position
*/

position create_child(position head, char caracter) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	tmp->caracter = caracter;
	head->next_child = tmp;

	return head->next_child;
}