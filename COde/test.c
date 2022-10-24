#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE (69)

struct _Person;
typedef struct _Person *Pose;

typedef struct _Person  {
    char name[SIZE];
    char su_name[SIZE];
    int birth_year;
    Pose next;
}Person;

int main(int argc, char** argv){

    // "dummy" element koji pokazuje na početak liste (Head)== prazna lista!!!
    Person Head = { .next = NULL , .name={0}, .su_name={0}, .birth_year = 0};    
    Pose P = &Head; //P je pokazivač na dummy element tj. početak liste

    int answer = 1; //inicijalizacija na 1 jer je početni odg
    char name[SIZE]= { 0 };
    char su_name [SIZE]={ 0 };
    int birth_year = 0;

    //Petlja za odabir opcija 
    while( answer != 0){
        printf("Odabirom broja program će učiti što se nalazi u opisu.\n");
        printf("Dodajete novu osobu na početak liste [ 1 ].\n");
        printf("Ipis liste [ 2 ].\n");
        printf("Dodajete novu osobu na kraj liste [ 3 ].\n");
        printf("Pronalazite osobu u listi po prezimenu [ 4 ].\n");
        printf("Brišete osobu iz liste [ 5 ].\n");
        printf("Unesite broj zeljene opcije:  ");
        scanf(" %d",&answer);

        switch(answer){
            
            case 1:
        }
    }

   // EXIT_SUCCESS je isto ka i 0 (nula) u return 
    return EXIT_SUCCESS;
}