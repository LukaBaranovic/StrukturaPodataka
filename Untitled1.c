#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#define MAX 50


typedef struct{
    char ime[25];
    char prezime[25];
    int bodovi;
}student;




int main(){

    student *s;

    int i,j,n,br;                                                           /*   par varijabli koje mi mozda zatrebaju, a mozda ne */
    br=0;
    char tmp;
    double rel;

    FILE *dat1;

    dat1=fopen("datoteka243.txt","r");

    if((dat1==NULL)){
        printf("Greska pri ucitavanju datoteka!!!");                       /*provjera otvaranja datoteke*/
            }

    while(!feof(dat1)){
        if(fgetc(dat1)=='\n'){                                             /*funkcija koja broji koliko ima studenata tj. redova u datoteci */
            br=br+1;
        }
        }

    rewind(dat1);                                                          /*vraca se na pocetak datoteke */

    s=(student *)malloc(br * sizeof(student));                             /* dinamicka alokacija strukture */

    for(i=0;i<br;i++){
        fscanf(dat1," %s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);    /*prijepis iz datoteke u strukturu*/
    }

    printf("\n\n%d\n\n", br);

    for(i=0;i<br;i++){
        printf("%d. student: \n", i+1);                                                 /*ispis*/
        printf("Ime i prezime: %s %s \n", s[i].ime, s[i].prezime);                      /*stavio sam da je broj bodova 100 jer nije zadano i nije mi bilo*/
        printf("Broj ostvarenih bodova: %d  \n", s[i].bodovi);                      /*jasno sta da stavim pod relativne bodove*/
        rel=(float)s[i].bodovi*100/MAX;
        printf("Broj relativnih bodova: %.2f \n\n\n", rel);
    }


    fclose(dat1);                                                                       /*zatvaranje datoteke*/


return 0;
}
















