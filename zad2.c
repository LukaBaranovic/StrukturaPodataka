#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX 200

typedef struct student* position;

struct student{
	char first_name[MAX];
	char last_name[MAX];
	int year_date;
	position next;
};

position create_student();
void insert_first(position);
void show(position);
void insert_last(position);
position search_by_last_name_prev(position);
position search_by_last_name(position);

void delete_from_list(position);

int main() {
	position head = NULL;
	head = (position)malloc(sizeof(struct student));
	head->next = NULL;

	  
	insert_first(head);
	insert_last(head);	  

	delete_from_list(head);

	show(head);



}


position create_student() {
	position p = NULL;
	p = (position)malloc(sizeof(struct student));

	printf("Insert first name: ");
	scanf(" %s", p->first_name);
	printf("Insert last name: ");
	scanf(" %s", p->last_name);
	printf("Insert birth year: ");
	scanf(" %d", &p->year_date);

	return p;
}

void insert_first(position head) {

	position tmp = NULL;
	tmp = (position)malloc(sizeof(struct student));
	tmp = create_student();

	tmp->next = head->next;
	head->next = tmp;

}

void show(position head) {
	head = head->next;

	while (head != NULL) {
		printf("\nFirst name: %s \n", head->first_name);
		printf("Last name: %s \n", head->last_name);
		printf("Birth year: %d \n", head->year_date);

		head = head->next;
	}
}

void insert_last(position head) {
	
	while (head->next != NULL) {
		head = head->next;
	}
	
	insert_first(head);
}

position search_by_last_name_prev(position head) {
	if (head->next == NULL) 
		printf("failed to find by last name");
	
	int br = NULL;
	char last_name[MAX];
	printf("Insert last name:  ");
	scanf(" %s", last_name);

	while (head->next != NULL) {
		if (strcmp (last_name ,head->next->last_name) == 0) {
			// printf("The student with this last name is:  \n");
			// printf(" %s %s", head->next->first_name, head->next->last_name);
			return head;
		}

		head = head->next;
	}

	if (br == NULL)
		printf("No student with such last name in list. \n");
}

position search_by_last_name(position head) {
	if (head->next == NULL)
		printf("failed to find by last name");

	int br = NULL;
	char last_name[MAX];
	printf("Insert last name:  ");
	scanf(" %s", last_name);

	while (head->next != NULL) {
		if (strcmp(last_name, head->next->last_name) == 0) {
			// printf("The student with this last name is:  \n");
			// printf(" %s %s", head->next->first_name, head->next->last_name);
			return head->next;
		}

		head = head->next;
	}

	if (br == NULL)
		printf("No student with such last name in list. \n");
}

void delete_from_list(position head) {

	position prev;
	prev = (position)malloc(sizeof(struct student));
	prev = search_by_last_name_prev(head);
	
	head = prev->next;
	prev->next = head->next;
	free(head);	
}
