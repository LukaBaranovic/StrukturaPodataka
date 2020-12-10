/*
Program ima funkcije:
-kreiraj direktorij
-kreiraj poddirektorijj
-promjeniti ime direktorija
-ulaz u odredeni direktorij, i njegov izlaz (setanje po direktorijima)
-prikaz direktorija (ovisi gdje se nalazimo)
-prikaz svih direktorija i njegovih poddirektorija (ovisi gdje se nalaimo) na nacin uvljacenja poddirektorija
-ispis svih direktorija u datoteku po default-u na kraju programa


-trenutno radim na funkcijama brisanja direktorija

*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 256

typedef struct Node* position;

struct Node {
	int data;
	position next_brother;
	position next_child;
};

position create_root(int);
void append_brother(position);
void display_brother(position);
int count_brother(position);
void display_directory_main(position, int);
void rename_directory(position);
void create_child(position);
void enter_child(position);
void print_in_file(position);
void print_in_file_auxiliary(FILE*, position, int);



void chose_delete_brother(position);
void delete_brother(position);



int main() {
	position directory = create_root(0);
	int loop = 1, action;
	int repeat = 1;


	while (loop == 1) {
		if (repeat == 1) {
			printf("(1) Dodaj direktorij \n");
			printf("(2) Dodaj poddirektorij \n");
			printf("(3) Udji u odredjeni direktorij \n");
			printf("(4) Prikazi direktorij \n");
			printf("(5) Prikazi sve direktorije i sve njihove poddirektorije \n");
			printf("(6) Preimenuj direktorij \n");
			printf("(00) Izadji iz programa \n\n");
			repeat = 0;
		}


		printf("Izaberi radnju: ");
		scanf("%d", &action);

		switch (action) {
		case 1:
			append_brother(directory);
			break;
		case 2:
			create_child(directory);
			break;
		case 3:
			enter_child(directory);
			repeat = 1;
			break;
		case 4:
			display_brother(directory);
			break;
		case 5:
			display_directory_main(directory, 0);
			break;
		case 6:
			rename_directory(directory);
			break;
		case 00:
			loop = 0;
			break;
		default:
			printf("Nepostojeca radnja!!\n");
			break;
		}
	}

	print_in_file(directory);
}

/*
Funkcija: main
Na pocetku programa se po defalt-u pita za unos prvog 'glavnog' direktorija.
Nakon toga ulazimo while petlju gdje imamo razne funkcjie koje mozemo birati za izvrsavanje programa.
Izlaz iz programa se vrsi upisom '00' s kojim izlazimo iz while petlje (while loop == 1).
*/




position create_root(int x) {
	position head = (position)malloc(sizeof(struct Node));
	head->next_brother = NULL;
	head->next_child = NULL;
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	if (x == 0) {
		printf("Unesite direktorij: ");
	}
	if (x == 1) {
		printf("Unesite poddirektorij: ");
	}

	scanf(" %d", &tmp->data);
	head->next_brother = tmp;
	return head;
}

/*
Funkcija: create_root
Kreira 'korijen stabla' za upis naseg prvog elementa u direktorij, te za kreiranje poddirektorija.
Vrsi se alociranje memorije te nan vraca listu 'head' u kojem u prvi element 'dummy' element za svaki novi poddirektorij.
Return: position
*/

void append_brother(position head) {
	position tmp = (position)malloc(sizeof(struct Node));
	tmp->next_brother = NULL;
	tmp->next_child = NULL;

	printf("Unesite direktorij: ");
	scanf(" %d", &tmp->data);

	tmp->next_brother = head->next_brother;
	head->next_brother = tmp;
}

/*
Funkcija: append_brother
Dodaje direktorij, odnosno 'brata', do onog direktorija ovisno gdje se nalazimo u direktoriju.
Return: /
*/

void display_brother(position head) {
	position tmp = head;
	int counter = 1;

	tmp = tmp->next_brother;
	while (NULL != tmp) {
		printf("<%d>  %d  ",counter++, tmp->data);
		tmp = tmp->next_brother;
	}
	printf(" \n");
}

/*
Funkcija display_brother
Vrsi ispis svih direktorija, svih 'braca' direktorija, ovisno gdje se nalazimo u direktoriju.
Return: /
*/

int count_brother(position head) {
	position tmp = head;
	int count = 0;
	while (NULL != tmp->next_brother) {
		count++;
		tmp = tmp->next_brother;
	}
	return count;
}

/*
Funkcija: count_brother
Broji direktorije, svih 'braca', koja nam sluzi u funkcijama kada biramo odredenu randnju za direktorij da 
ne bi upisali direktorij koji ne postoji. (npr. funkcija enter_child,create_child o kojoj ce biti objasnjeno o tome).
Return: int 
*/

void create_child(position head) {
	int selection;
	display_brother(head);
	printf("Izaberite broj gdje zelite napraviti poddirektorij: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		head = head->next_brother;
		selection--;
	}
	if (head->next_child != NULL) {
		append_brother(head->next_child);
	}
	else
	{
		head->next_child = create_root(1);
	}
}

/*
Funkcija: create_child
Ispisuje nam sve direktorije ovisno o tome gdje se nalazimo, te nam daje na odabir kojem od direktorija zelimo napraviti poddirektorij. 
Program vrsi provjeru je li taj direktorij postoji (mora biti broj izmedju 1 i count_brother(direktorij), a ako nije pita nas da 
pokusamo ponovno).
Ako smo ispravno unijeli direktorij program uz pomoc funkcije 'create_root' kreira poddirektorij direktorija.
NAPOMENA: funkcija je pametna jer ako uoci da u tom direktoriju vec postoje poddirektoriji ona koristi funkciju 'append_brother' da
bi mu dodala brata, odnosno novi direktorij tom poddirektoriju.
Return: /
*/
 
void enter_child(position head) {
	int selection;
	int loop = 1, action;
	int repeat = 1;

	display_brother(head);
	printf("Od kojeg direktorija zelite pogleadi poddirektorije: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	head = head->next_child;

	if (head == NULL) {
		printf("Vas direktorij ne sadrzi poddirektorije!!!\n");
	}
	else {
		printf("Sadrzaj poddirektorija:  ");
		display_brother(head);
		printf("\n");


		while (loop == 1) {

			if (repeat == 1) {
				printf("(1) Dodaj direktorij \n");
				printf("(2) Dodaj poddirektorij \n");
				printf("(3) Udji u odredjeni direktorij \n");
				printf("(4) Prikazi direktorij \n");
				printf("(5) Prikazi sve direktorije i sve njihove poddirektorije \n");
				printf("(6) Preimenuj direktorij \n");
				printf("(00) Povratak na prosli direktorij \n");
				repeat = 0;
			}
			printf("Izaberi radnju: ");
			scanf("%d", &action);

			switch (action) {
			case 1:
				append_brother(head);
				break;
			case 2:
				create_child(head);
				break;
			case 3:
				enter_child(head);
				repeat = 1;
				break;
			case 4:
				display_brother(head);
				break;
			case 5:
				display_directory_main(head, 0);
				break;
			case 6:
				rename_directory(head);
				break;
			case 00:
				loop = 0;
				break;
			default:
				printf("Nepostojeca radnja!!\n");
				break;
			}
		}

	}
}

/*
Funkcija enter_child
Jedna od bitnijih funkcija programa koja nam omogucava 'setanje' po direktorijima i poddirektorijima.
Program nas pita u koji direktorij zelimo uc, te nam stavlja taj direktorij kao 'glavni' dok ne napravimo povrat na prethodne 
direktorije upisom '00'.
Vrsi provjeru je li postoji direktorij u koji zelimo uc (mora biti broj izmedju 1 i count_brother()).
Sadrzi while petlju kao i u funkciji 'main' jer ostajemo na trenutnom direktoriju kako bi mogli raditi odredene 
radnje tu gdje se nalazimo (dodati jos direktorija, poddirektorija, preimonovanja i brisanja)
Return: /
*/

void display_directory_main(position head,int offset) {
	position tmp = head;
	int i;
	

	while (tmp->next_brother != NULL) {
		tmp = tmp->next_brother;
		for (i = 0; i < offset; i++) {
			printf("  ");
		}
		printf("-%d \n", tmp->data);

		if (tmp->next_child != NULL)
			display_directory_main(tmp->next_child, offset + 1);

	}
}

/*
Funkcija display_directory_main
Vrsi ispis svih direktorija i svih njegovij poddirektorija i poddirektorija poddirektorija...
Kada ispis direktorij, za ispis poddirektorija se tekst uvlaci na nacin:
 DIREKTORIJ 1
 DIREKTORIJ 2
	-DIREKTORIJ 2.1
		-DIREKTORIJ 2.1.1
			-DIREKTORIJ 2.1.1.1
		-DIREKTORIJ 2.1.2
	-DIREKTORIJ 2.2
		-DIREKTORIJ 2.2.1
	DIREKTORIJ 2.3
 DIREKTORIJ 3
Return: /
*/

void rename_directory(position head) {
	int selection;
	int renamed;
	display_brother(head);
	printf("Koji direktorij zelite preimenovati: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}
	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	printf("Upisite novu vrijednost: ");
	scanf(" %d", &renamed);
	head->data = renamed;
}

/*
Funkcija: rename_directory
Biramo koji direktorij zelimo preimenovati, te provjarava ispravnost naseg unosa( je li taj direktorij uopce postoji).
Return: /
*/

void print_in_file(position head){
	FILE* fp = fopen("direktorij.txt", "w");

	if (NULL == fp)
		printf("could not open file!\n");

	fprintf(fp, "----DATOTEKA DIREKTORIJA----\n\n");

	print_in_file_auxiliary(fp, head, 0);

	fclose(fp);
}

/*
Funkcija: print_in_file
Kreira datoteku 'direktorij' i otvara ju za pisanje te se poziva pomocna funkcija 'print_in_file_auxuliary.
Return: /
*/

void print_in_file_auxiliary(FILE* fp, position head,int offset) {
	position tmp = head;
	int i = 0;

	while (tmp->next_brother != NULL) {
		tmp = tmp->next_brother;
		for (i = 0; i < offset; i++) {
			fprintf(fp,"  ");
		}
		fprintf(fp,"-%d \n", tmp->data);

		if (tmp->next_child != NULL)
			print_in_file_auxiliary(fp,tmp->next_child, offset + 1);
	}
}

/*
Funkcija: print_in_file_auxiliary 
Pomocna funkcija funkcije 'print_in_file' koja prima pointer na datoteku i upise sadrzaj svih direktorija na isti nacin 
kako funkcija 'display_directory_main' vrsi ispis na konzolu. 
Po default-u se poziva na kraju programa.
Return: /
*/




void chose_delete_brother(position head) {
	int selection;
	display_brother(head);
	printf("Izaberite koji direktorij zelite obrisati: ");
	scanf(" %d", &selection);

	while (selection < 1 || selection > count_brother(head)) {
		printf("Nevazeci direktorij, pokusajte ponovno: ");
		scanf(" %d", &selection);
	}

	while (selection > 0) {
		selection--;
		head = head->next_brother;
	}
	
	
	delete_brother(head); 
	position tmp = head;
	free(tmp);
	head = head->next_brother;
	
}

void delete_brother(position head) {
	position tmp;


	if (head->next_child != NULL) {	
		tmp = head;
		head = head->next_child;
		free(tmp);
		delete_brother(head->next_child);
	}
	if (head->next_brother != NULL) {
		tmp = head;
		head = head->next_brother;
		free(tmp);
		delete_brother(head->next_brother);
	}
}
