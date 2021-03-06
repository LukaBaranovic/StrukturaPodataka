/*
Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se čitaju iz datoteke.

U program se polinomi ne unose rucno vec preko datoteke. Kada radimo datoteku izmedu baze i exponenta
stavljama razmak kojeg takoder stavljamo izmedu dva clana. Za novi polinom predemo u novi red.

Kada program, on nam ispisuje sve polinome koji su nam dostupni za operacije zbrajanja i mnozenja.
Kada izaberemo koju operaciju zelimo izvrsiti program nas pita koja 2 polinoma zelimo zbrojiti/pomnoziti,
a ako izaberemo polinome koji ne postoje program nam to kaze i vrati nas na pocetak programa.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polynom* position;
struct polynom {
	int value;
	int exponent;
	position next;
};

int line_counter(FILE*);
position create_list(int);
void read_from_file(FILE *, position*, int);
void sorted_insert(int,int,position);
void show(int, position *);
position polynom_sum (position,position);
position polynom_multiply(position, position);
void sort_double(position);                      
void show_specific(position);



int main() {
	int first, second;
	int i, j, n;
	int loop = 1;
	int action;
	FILE* file_1;
	file_1 = fopen("kraj4zad.txt", "r");
	if (file_1 == NULL)
		printf("file reading eror...\n");
	int number_of_polynom = line_counter(file_1);

	position* head = create_list(number_of_polynom);
	read_from_file(file_1, head, number_of_polynom);


	show(number_of_polynom, head);
	printf("Unesite radnju: \n");
	printf("Prikazi polinome    (1)	    \n");
	printf("Zbroji polinome     (2)     \n");
	printf("Pomnozi polinome    (3)     \n");
	printf("Prekini program	    (0)  	\n");

	while (loop == 1) {
		
		scanf(" %d", &action);

		switch (action) {
		case 1:
			show(number_of_polynom, head);
			break;
		case 2:
			printf("Unesite koje polinome zelite zbrojiti?  ");
			for (i = 0; i < number_of_polynom; i++) {
				printf(" (%d)", i + 1);
			}
			printf("\n");
			scanf(" %d %d", &first, &second);
			if (first > 0 && second > 0 && first < number_of_polynom + 1 && second < number_of_polynom + 1) {
				printf("Zbroj %d. i %d. polinoma:  ", first, second);
				show_specific(polynom_sum(head[first - 1], head[second - 1]));
			}
			else
				printf("Takvi polinomi ne postoje, pokusajte ponovno...\n");
			first = NULL;
			second = NULL;
			break;
		case 3:
			printf("Unesite koje polinome zelite pomnoziti? ");
			for (i = 0; i < number_of_polynom; i++) {
				printf(" (%d)", i + 1);
			}
			printf("\n");
			scanf(" %d %d", &first, &second);
			if (first > 0 && second > 0 && first < number_of_polynom + 1 && second < number_of_polynom + 1) {
				printf("Umnozak %d. i %d. polinoma:  ", first, second);
				show_specific(polynom_multiply(head[first - 1], head[second - 1]));
			}
			else
				printf("Takvi polinomi ne postoje, pokusajte ponovno...\n");
			first = NULL;
			second = NULL;
			break;
		case 0:
			loop = 0;
			break;
		default:
			printf("Takva radnja ne postoji... \n");
			break;
		}
		if(loop == 1)
			printf("Unesite radnju: \n");

	}
	
	fclose(file_1);
	system("pause");
}




int line_counter(FILE* f) {
	int counter = 0;												

	while (!feof(f)) {
		if (getc(f) == '\n')
			counter = counter + 1;
	}
	rewind(f);
	return counter+1;
}

/* funckija koja broji linije iz file-a, odnosno broj polinoma datoteke*/

position create_list(int n) {								//kreira niz u kojoj je svaki clan vezana lista
	int i;										//kreira onoliko koliko zelimo polioma unijeti

	position* head = (position*)malloc(n * sizeof(position));
	for (i = 0; i < n; i++) {
		position tmp = (position)malloc(sizeof(struct polynom));
		tmp->next = NULL;
		head[i] = tmp;
	}
	return head;
}

/* Kreira niz od onoliko clanova koliko je u datoteci upisano.
   Svaki clan niza je vezana lista.  */

void read_from_file(FILE *f, position *head, int n) {
	int i, j, val, exp;
	int mat[10];
	int enter = 0;
	int space = 1;
	char c;

	while (!feof(f)) {
		c = getc(f);

		if (c == '\n') {							//ovaj algoritam trazi razmake, broj clanova u polinomu je (broj razmaka + 1) / 2
			mat[enter] = space / 2;						//enter oznacava broj polinoma/linija
			space = 1;
			enter = enter + 1;
		}
		if (c == ' ')
			space = space + 1;

	}
	mat[enter] = space / 2;
	rewind(f);

	for (i = 0; i < n; i++) {
		for (j = 0; j < mat[i]; j++) {
			fscanf(f, "%d %d", &val, &exp);
			sorted_insert(val ,exp, head[i]);
		}
	}
}

/* Funkcija koja cita polinome iz datoteke i upisuje ih u vezanu listu. */

void sorted_insert(int val, int exp, position head) {						//sortira unos od prema padajucim vrijednostima
	position tmp;										//podrazumijeva se da se exponenti u istom polinomu ne ponavljaju
	tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;
	
	while ((head->next != NULL) && (exp < head->next->exponent))
		head = head->next;

	tmp->value = val;
	tmp->exponent = exp;

	tmp->next = head->next;
	head->next = tmp;
}

/* Funkcija koja sortira polinome, od clana s najvecin koeficijentom do clana sa najmanjim. */

void show(int n, position* head) {								//ispisuje polinome na 3 nacina:
	int i;											// x=0 ne prikazuje x nego samo ispise njegovu vrijednost
	position tmp;										// x=1 napise samo x bez ikakvog exponenta
												// x>1 napise exponent uz svaki x
	for(i=0;i<n;i++){
		
			printf("%d. polinom: ", i + 1);
			tmp = head[i];
			while (tmp->next != NULL) {
				tmp = tmp->next;

				if (tmp->exponent > 1)
					printf(" %dx^(%d) ", tmp->value, tmp->exponent);
				if (tmp->exponent == 1)
					printf(" %dx ", tmp->value);
				if (tmp->exponent == 0)
					printf(" %d ", tmp->value);
			}
			printf("\n");
		}
	
}

/* Funkcija koja prikazuje sve polinome ucitane iz datoteke.  */

void show_specific(position head) {
	position tmp = head;

	while (tmp->next != NULL) {
		tmp = tmp->next;
		
		if (tmp->exponent > 1)
			printf(" %dx^(%d) ", tmp->value, tmp->exponent);
		if (tmp->exponent == 1)
			printf(" %dx ", tmp->value);
		if (tmp->exponent == 0)
			printf(" %d ", tmp->value);
	}
	printf("\n");
}

/* Funkcija koja prikazuje specificni polinom. Koristi se za ispis zbroja/umnoska. */

position polynom_sum(position pol1, position pol2) {
	int i, j;
	position pol_sum = (position)malloc(sizeof(struct polynom));
	pol_sum->next = NULL;
	int val, exp;

	pol1 = pol1->next;
	pol2 = pol2->next;

	while ((pol1 != NULL) && (pol2 != NULL)) {
		if (pol1->exponent == pol2->exponent) {							//trazi clanove sa istim exponentom
			val = pol1->value + pol2->value;
			exp = pol1->exponent;
			if(val != 0)									//ako je njihov zbroj 0 samo ga zanemari
				sorted_insert(val, exp, pol_sum);
			pol1 = pol1->next;
			pol2 = pol2->next;
		}
		else if (pol1->exponent > pol2->exponent) {						//ako ne pronade iste exponente ispisuje veci
			sorted_insert(pol1->value, pol1->exponent, pol_sum);
			pol1 = pol1->next;
		}
		else {
			sorted_insert(pol2->value, pol2->exponent, pol_sum);
			pol2 = pol2->next;
		}
	}

	while (pol1 != NULL) {										//kad jedan polinom dodje do 0, drugog prepise dokraja
		sorted_insert(pol1->value, pol1->exponent, pol_sum);
		pol1 = pol1->next;
	}
	while (pol2 != NULL) {
		sorted_insert(pol2->value, pol2->exponent, pol_sum);
		pol2 = pol2->next;
	}

return pol_sum;												//vraca sorirani zbroj kojeg dobijemo u main funkciji
}

/* Funkcija koja vraca sortiranu sumu dvaju polinoma koja mi posaljemo. */

position polynom_multiply(position pol1, position pol2) {
	position result = (position)malloc(sizeof(struct polynom));
	result->next = NULL;
	position tmp;
	
	while (pol1->next != NULL) {
		pol1 = pol1->next;
		tmp = pol2;

		while (tmp->next != NULL) {
			tmp = tmp->next;

			sorted_insert(pol1->value * tmp->value, pol1->exponent + tmp->exponent, result);
		}
	}	
	sort_double(result);
return result;
}

/* Funkcija koja vraca sortirani umnozak dvaju polinoma koja mi posaljemo. */

void sort_double(position head) {
	position tmp = (position)malloc(sizeof(struct polynom));
	tmp->next = NULL;
	int val,exp;

	while (head->next != NULL) {
		head = head->next;
		if (head->next != NULL) {
			if (head->exponent == head->next->exponent) {			//trazi duplikate i zbraja ih u jednog
				val = head->value + head->next->value;				
				exp = head->exponent;
				tmp->next = head->next->next;
				free(head->next);
				head->next = tmp;
				head->value = val;
			}
		}
	}
}

/* Funkcija koja trazi duple polinome nakon funkcije polynom_multiply i spaja u jedno. */
