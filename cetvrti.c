#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128

struct Polinom;
typedef struct Polinom * Position;

typedef struct Polinom{

    int koef;
    int eks;
    Position  next;

} Poli;

int Read_file(Position P1, Position P2);
Position MakePol(int koef, int eks);
int ReadLine(Position head, char *buffer);
int ClearZero(Position head);
int InsertSorted(Position head, Position NewElement);
int InsertAfter(Position head, Position NewElement);
int Print(Position P);
int CleanUp(Position P);



int main(){

    
    Poli head1 = { .koef = 0 , .eks = 0, .next = NULL };
    Poli head2 = { .koef = 0, .eks = 0, .next = NULL };

    Position P1 = &head1;
    Position P2 = &head2;

    int answer = 1;


    while( answer != 0){

        
        printf("\nOdaberite broj ovisno o zeljenoj vrsti racunanja: \n");
        printf("ZBROJ (1)\n");
        printf("UMNOZAK (2)\n");
        printf(" Kraj (0)\n");
        printf("Unesite vas odabir:  ");
        scanf(" %d", &answer);



    switch (answer)
    {

        case 0:
            printf("Program je prekinut !!");
            break; 

        case 1:
            if( Read_file(P1,P2) != 0) break;
            printf("\nPolinomi iz datoteke su :\n");
            printf("\n 1. RED: \n");
            Print(P1);
            printf("\n 2. RED: \n");
            Print(P2);
            
    CleanUp(P1);
    CleanUp(P2);

            break;

        case 2:
            if(Read_file(P1,P2) != 0) break;
            printf("\nPolinomi iz datoteke su :\n");
            printf("\n 1. RED: \n");
            Print(P1);
            printf("\n 2. RED: \n");
            Print(P2);

    CleanUp(P1);
    CleanUp(P2);
            break;


        default:
         printf("\nUnijeli ste broj koji nije poduden!\n");
         break;
        }
    }


    return 0;
}


int CleanUp(Position P){

    Position temp = NULL;

    while(NULL != P -> next){
        temp = P -> next;
        P -> next = temp -> next;
        free(temp);
    }

    return 0;
}

Position MakePol( int koef, int eks){

    Position New  = NULL;

    New = (Position) malloc (sizeof(Poli));

    New -> koef = koef;
    New -> eks = eks;
    New -> next = NULL;

    return New;
}


int Read_file(Position P1,Position P2){

    FILE *fp = NULL;
    char buffer[MAX_SIZE] = { 0 };

    fp = fopen("polinom.txt","r");

    if( fp == NULL){
        printf("Datoteku nije moguce otvoriti!!");
        return -1;
    }


    //citanje retka/ ima 2 retka
    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P1,buffer);
    ClearZero(P1);

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P2,buffer);
    ClearZero(P2);

    
    fclose(fp);

    return 0;
}

int ReadLine(Position head, char*buffer){

    int koef,eks;
    int brojac = 0;
    int procitan_bb=0;

    //dok ima brojeva 

    while( strlen(buffer) > 0){
        procitan_bb = sscanf(buffer, " %d  %d  %n ", &koef, &eks, &brojac);

        if(procitan_bb == 2 && koef != 0)
            InsertSorted(head, MakePol(koef,eks));  //treba sortirat kako bi se program brze izvodio

         buffer += brojac;
        
    }

    return 0;
}

int InsertSorted( Position head, Position NewElement){

    //treba sortirati po potencijama od najvece do najmanje
    int n=0; //varijabla koja nam treba za provjeru je li koeficijent nula

    while( head -> next != NULL && head->next->eks > NewElement->eks){
        head = head -> next;
    }

    //ako su potencije iste odmah zbrjiti koeficijente
    if( head-> next != NULL && head->next->eks == NewElement->eks){
        head->next->koef += NewElement->koef;
        n=head->koef;

            if(n==0)
              ClearZero(head);  
    }

    //Ako je novi element manjeg eksponenta od ostalih samo ga stavi na pocetak liste
    else {
        MakePol(NewElement->koef, NewElement->eks );
        InsertAfter(head, NewElement);
    }

    return 0;
}


int ClearZero(Position head){
    Position temp = head;

    //Pomocna za brisanje
    Position Temp1 = NULL;

    while ( temp -> next != NULL){

        if (temp -> next -> koef == 0)
        {
            //DELETE == CleanUp
            Temp1 = temp -> next;
            temp -> next = Temp1 -> next;
            free(Temp1);
        }

        else{
            temp = temp -> next; //i++
        } 
        
    }
    return 0;
}

int InsertAfter(Position head, Position NewElement){

    NewElement -> next = head -> next;
    head -> next = NewElement;

    return 0;
}

int Print(Position P){
    //from first memeber
    Position temp = P -> next;

    //dok postoji 
    while(temp){
        printf(" %dx^%d  \n", temp->koef , temp->eks);
        temp = temp-> next;  //i++
    }

    return 0;
}
