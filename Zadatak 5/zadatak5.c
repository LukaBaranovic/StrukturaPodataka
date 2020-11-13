#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256


typedef struct list* position;
struct list {
	int x;
	position next;
};

position create_list(int);
void read_from_file(position*);
void insert(char*, position head);
void sorted_insert(int, position);
void show_specific(position);
void show_all_from_file(int, position*);
int line_counter();
void make_union(position, position);
void make_intersection(position, position);


int main() {
	int number = line_counter();
	int action, loop = 1;
	int first = 0, second = 0;
	position* head = create_list(number);
	read_from_file(head);

	show_all_from_file(number, head);
	
	printf(" (1) -prikazi uniju 2 skupa \n");
	printf(" (2) -prikazi presjek 2 skupa \n");
	printf(" (0) -izlaz iz programa \n");
		
	while (loop == 1) {
		printf("Unesite radnju: \n");
		scanf(" %d", &action);

		switch (action) {
		case 1:
			printf("Izaberi prvi skup za uniju: ");
			scanf(" %d", &first);
			printf("Izaberi drugi skup za uniju: ");
			scanf(" %d", &second);
			if (first > 0 && first < number + 1 && second > 0 && second < number + 1) {
				printf("Unija %d. i %d. skupa je: ", first, second);
				make_union(head[first - 1], head[second - 1]);
			}
			else
				printf("Ti skupovi ne postoje...\n");
			break;
		case 2:
			printf("Izaberi prvi skup za presjek: ");
			scanf(" %d", &first);
			printf("Izaberi drugi skup za presjek: ");
			scanf(" %d", &second);
			if (first > 0 && first < number + 1 && second > 0 && second < number + 1) {
				printf("Presjek %d. i %d. skupa je: ", first, second);
				make_intersection(head[first - 1], head[second - 1]);
			}
			else
				printf("Ti skupovi ne postoje...\n");
			break;
		case 0:
			loop = 0;
			break;
		default:
			break;
		}

	}


	system("pause");
}



position create_list(int number) {
	int i;

	position* head = (position*)malloc(number * sizeof(position));
	for (i = 0; i < number; i++) {
		position tmp = (position)malloc(sizeof(struct list));
		tmp->next = NULL;
		head[i] = tmp;
	}


	return head;
}

void read_from_file(position* head) {
	int x = 0;
	char str[MAX];
	FILE* filename = fopen("lista.txt", "r");
	if (filename == NULL) {
		printf("Eror opening file... \n");
		return NULL;
	}

	while (fgets(str, MAX, filename) != NULL) {
		insert(str, head[x]);
		x++;
	}
}

void insert(char* str, position head) {
	int br = 0, differ = 0;

	while (sscanf(str, " %d, %n%*[^\n]", &br, &differ) == 1) {
		str = str + differ;
		sorted_insert(br, head);
	}
}

void sorted_insert(int br, position head) {
	position tmp = (position)malloc(sizeof(struct list));
	tmp->next = NULL;

	while (head->next != NULL && head->next->x >= br) {
		head = head->next;
	}
	if (br != head->x) {
		tmp->x = br;
		tmp->next = head->next;
		head->next = tmp;
	}
}

void show_specific(position head) {
	position tmp = head;

	while (tmp->next != NULL) {
		tmp = tmp->next;
		printf(" %d", tmp->x);
	}
	printf("\n");
}

void show_all_from_file(int number, position* head) {
	int i;
	for (i = 0; i < number; i++) {
		printf("%d. skup: ", i + 1);
		show_specific(head[i]);
	}
}

int line_counter() {
	FILE* filename = fopen("lista.txt", "r");
	int counter = 1;
	while (!feof(filename)) {
		if (getc(filename) == '\n')
			counter++;
	}
	rewind(filename);
	fclose(filename);

	return counter;
}

void make_union(position list1, position list2) {
	position list_union = (position)malloc(sizeof(struct list));
	list_union->next = NULL;

	while (list1->next != NULL && list2->next != NULL) {
		if (list1->next->x == list2->next->x) {
			list1 = list1->next;
			list2 = list2->next;
			sorted_insert(list1->x, list_union);
		}
		else if (list1->next->x > list2->next->x) {
			list1 = list1->next;
			sorted_insert(list1->x, list_union);
		}
		else if (list2->next->x > list1->next->x) {
			list2 = list2->next;
			sorted_insert(list2->x, list_union);
		}
	}
	while (list1->next != NULL) {
		list1 = list1->next;
		sorted_insert(list1->x, list_union);
	}
	while (list2->next != NULL) {
		list2 = list2->next;
		sorted_insert(list2->x, list_union);
	}
	printf("Unija je: ");
	show_specific(list_union);
}

void make_intersection(position list1, position list2) {
	position list_intersection = (position)malloc(sizeof(struct list));
	list_intersection->next = NULL;

	while (list1->next != NULL && list2->next != NULL) {
		if (list1->next->x == list2->next->x) {
			list1 = list1->next;
			list2 = list2->next;
			sorted_insert(list1->x, list_intersection);
		}
		else if (list1->next->x > list2->next->x) {
			list1 = list1->next;
		}
		else if (list2->next->x > list1->next->x) {
			list2 = list2->next;
		}
	}
	printf("Presjek je:");
	show_specific(list_intersection);
}
