//Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
//Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i povratak u prethodni direktorij. 
//Točnije program treba preko menija simulirati korištenje DOS naredbi:
// 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 60

typedef struct Stablo* Position;
typedef struct Lista * lPosition;

typedef struct Stablo{
    char *name;
    Position brat;
    Position dite;
}stablo;


//lista je za STOG kako bi se mogli spremati root, braca  i dica
typedef struct Lista{
    Position direktorij;  //poveznica na stablo-lista

    lPosition next;
    lPosition prev;
}lista;

#pragma funkicje
int Izbornik(Position,lPosition);
int Line(lPosition,Position,Position);
lPosition FindLast(lPosition);
int StvoriStablo(Position);
Position OpenDirec(Position, lPosition); 
int Push(lPosition ,Position); 
Position FindByName(char*, Position);

#pragma end_funkcije


int main(){

    Position root;
    root = (Position) malloc (sizeof(stablo));
    root->brat=NULL;
    root->dite=NULL;

    lPosition head; //lista
    head = (lPosition) malloc (sizeof(lista));
    head->next=NULL;
    head->prev=NULL;

    root->name=(char*)malloc(MAX_SIZE*sizeof(char));
    root->name = "C:"; //pocetni, iza njega nema nista

    int s = 1;
    while(s){
        s=Izbornik(root,head); //glava stabla i pocetak liste
    }

    return 0;
}


int Izbornik(Position root, lPosition head){

    Position trenutni = root;
    char odabir[MAX_SIZE] = { 0 };

    printf("md [...] - Dodaj novi direktorij\n"); //dodaj dite i povezi dite s bratom
	printf("cd [...] - Otvori direktorij\n"); //dodaj dite poslije head-a, tako da je root uvik next na NULL 
	printf("cd.. - Vrati na prethodni direktorij\n"); //izbrisi mu svu dicu i vrati na na prethodni, na roditelja dice
	printf("dir - Ispis pod-direktorija trenutnog direktorija\n");//ispis dice trenutnog direktorija
	printf("exit - KRAJ\n\n");

    while(1) {

        Line(head,root,trenutni);
        scanf(" %s",odabir);

        if(strcmp(odabir,"md") == 0)
            StvoriStablo(trenutni);
        
        else if(strcmp(odabir,"cd") == 0)
            trenutni=OpenDirec(trenutni,head);

        //else if(strcmp(odabir,"cd..") == 0)


        //else if(strcmp(odabir,"dir") == 0)


        else if(strcmp(odabir,"exit") == 0)
            return 0;

        else 
            printf("Error! Try again!\n");
    }

    return 0;
}

//lista za ispis na konzolu
int Line(lPosition head, Position root, Position trenutni){

    lPosition clan; //clan liste

    clan = FindLast(head);

    //ispis zadnjeg unesenog direktorija
    if(head->next == NULL)
    {
        printf("%s>",root->name);
        return 0;
    }

    //ispis svih direktorija 
    while(NULL != clan->prev)
    {
        printf("%s>", clan->direktorij->name);
        clan = clan -> prev;
    }

    printf("%s>", trenutni->name);
    return 0;
}

lPosition FindLast (lPosition head){

    lPosition z;
    z = head -> next;

    if(NULL == z)
        return NULL;

    while(z -> next != NULL)
    {
        z = z -> next;
    }

    return z;
}

//stvaranj / dodavanje direktorija
//trenutni je postojeći, a directory stvaramo
int StvoriStablo(Position trenutni){

    Position directory;
    directory = (Position)malloc(sizeof(stablo));
    directory->name = (char*)malloc(MAX_SIZE*sizeof(char));

    if(!directory)
        perror("Cannot alocate memory!!\n");

    if(NULL != trenutni->dite ){
        trenutni = trenutni -> dite;  
        while (NULL != trenutni->brat)
        {
            trenutni = trenutni -> brat;
        }
        trenutni -> brat = directory;
    }    

    else 
        trenutni -> dite = directory;

    scanf(" %s", directory->name);
    directory->brat=NULL;
    directory->dite=NULL;    

    return 0;
}

//otvaranje -> postavljanje direktorija  cd
//dodavanje novog direktorija na pocetak liste
Position OpenDirec(Position trenutni, lPosition head){

    Position s;
    char *name;
    name = (char*)malloc(MAX_SIZE*sizeof(char));

    scanf(" %s", name);

    if(NULL == trenutni->dite ){
        printf("Nema tog direktorija!!\n");
        return trenutni;
    }

    s = FindByName(name,trenutni);
    if(!s){
        perror("Direktorij nije pronađen!!\n");
        return trenutni;
    }

    Push(head,trenutni);

    return s;
}

//Dodavanje direktorija na pocetak liste
//Zadnji clan liste je root direktorij, a ostali su pod-direktoriji
int Push(lPosition head,Position direktorij){

    lPosition p = (lPosition)malloc(sizeof(lista));

    p->next=head->next;
    p->prev=head;

    if(NULL != head->next)
    {
        head->next->prev=p;
    }

    head->next=p;
    p->direktorij=direktorij;

    return 0;
}

//trazenje stvorenog direktorija primjer: md ante 
//ako postoji postavljamo ga kao dite root-a
//
Position FindByName(char *name, Position trenutni){

    if(NULL == trenutni->dite)
    {
        printf("Direktorij je prazan!!");
        return 0;
    }

    trenutni = trenutni -> dite;
    //dok ne pronađe clana
    while(strcmp(name,trenutni->name)!=0 && trenutni->brat != NULL){
            trenutni = trenutni -> brat;
    }

    //ako nema brata
    if(NULL == trenutni->brat )
    {
        //ako nema brata i ne postoji uneseno ime 
        if(strcmp(name, trenutni->name) != 0)
            return NULL;

        else
            return trenutni;    
    }    

    else 
        return trenutni;

}
