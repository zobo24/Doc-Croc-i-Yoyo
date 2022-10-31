//Definirati strukturu osoba(ime, prezime, godina ro enja) i napisati program koji :
//D.pronalazi element u listi(po prezimenu),
//E.bri e odre eni element iz liste,

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

void CleanUp(Position Head);
int UnosP(Position Head, char* name, char* surname, int birthYear);
int PrintList(Position Head);
int UnosK(Position Head, char* name, char* surname, int birthYear);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position Last, Position newPerson);
Position FindLast(Position Head);
Position trazenje_po_prezimenu(Position head,char* surname_trazenog);// vraca pointer na osobu s tin prezimenon
Position trazenje_po_prezimenu_osobe_ispred(Position head,char* surname_trazenog);//vraca pointer na osobu prije osobe sa trazenim prezimenon
int brisanje_clana(Position head,char* surname_trazenog);
int dodavanje_iza_odredenog_elementa(Position head,char* surname_trazenog,char* name,char* surname,int birthYear);
int dodavanje_prije_odredenog_elementa(Position head,char* surname_trazenog,char* name,char* surname,int birthYear);
int zamjena_pozicija(Position temp_temp, Position temp_1,Position temp_2);
int broj_clanova_niza(Position head);
int jebeni_buble_sort(Position head);
int jebeni_buble_sort_2(Position head);
int jebeni_buble_sort_3(Position head);
int zamjena(Position temp_1,Position temp_2);
int main(int argc, char** argv)
{
    //stvaranje pocetnog clana koji ne sadrzi sadrzaj
	Person Head = { .next = NULL, .name = {0}, .surname = {0},	.birthYear = 0 }; 
    //Pointer na pocetni clan
	Position P = &Head;

	int answer = 1;
	char name[MAX_SIZE] = { ' ' };
	char surname[MAX_SIZE] = { ' ' };
	char surname_trazenog[MAX_SIZE] = { ' ' };
	int birthYear = 0;

    //Kada je odgovor nula program se prekida
	while (answer != 0)
	{
		system("cls"); // nadodaj ovo da se "refresha" pojava narednih printf linija a lista se spremi i pise iznova !!!
                        // korisniku je lista citljivija i unos je jednostavniji

		PrintList(P);
		printf("\t\nSto zelite uciniti?\n\n");
		printf("\tUnijeti osobu na pocetak liste (1)\n");
		printf("\tUnijeti osobu na kraj liste (2)\n");
		printf("\tPretraziti osobu po prezimenu (3)\n");
		printf("\tIzbrisati osobu iz liste (4)\n");
		printf("\tUnesite iza neke osobe (5)\n");
		printf("\tUnesite prije neke osobe(6)\n");
		printf("\tSortirajte listu abecedno(7)\n");
        printf("\tKraj (0) \n");
		printf("Unesite vas odabir:  ");
		scanf(" %d", &answer);

		switch (answer)
		{
		case 1:
			printf("\nUnesite ime i prezime studenta na pocetak liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
			UnosP(P, name, surname, birthYear);
			break;

		case 2:
			printf("\nUnesite ime i prezime studenta na kraj liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
			UnosK(P, name, surname, birthYear);
			break; 
		case 3:
			printf("unesite prezime zeljenog studenta:");
			scanf(" %s",surname_trazenog);
			Position temp=trazenje_po_prezimenu(P,surname_trazenog);
			printf("Ime_trazenog_studenta: %s  Prezime: %s  Godina izdavanja: %d\n",
			temp->name, temp->surname, temp->birthYear);
			break;
		case 4:
			printf("unesite prezime studenta kojeg zelite obristai:");
			scanf(" %s",surname_trazenog);
			brisanje_clana(P,surname_trazenog);
		case 5:
		    printf("unesite prezime studenta iza kojeg zelite unijeti novog clana:");
		    scanf(" %s",surname_trazenog);
		    printf("\nUnesite ime i prezime studenta na pocetak liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
		    dodavanje_iza_odredenog_elementa(P,surname_trazenog,name,surname,birthYear);
		case 6:
			printf("unesite prezime studenta prije kojeg zelite unijeti novog clana:");
		    scanf(" %s",surname_trazenog);
		    printf("\nUnesite ime i prezime studenta na pocetak liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
		    dodavanje_prije_odredenog_elementa(P,surname_trazenog,name,surname,birthYear);
		case 7:
			jebeni_buble_sort_3(P); 
		case 8:
			Position temp_temp= P;
			Position temp_1=P->next;
			zamjena(temp_temp,temp_1);
		}
	}
    //Ciscenje memorije od pokazivaca
    CleanUp(P);
	//mozemo jos nadodati da se ispisuje greska ukoliko se upise broj koji nije u intervalu od 1-4 ili prezime koje ne postoji

	return EXIT_SUCCESS;
}


//Funkcija za ciscenje memorije
void CleanUp(Position Head){
    Position nextone;

    while(Head)
    {
        nextone = Head -> next;
        free(Head);
        Head = nextone;
    }
}

//No. 1
//stvaranje osobe u memoriji
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson ) {
		perror("Can't allocate memory!\n");
        //You're returning an integer.
        //Since the function returns a pointer, the usual error value is NULL
        //Zato ode ide NULL, a ne -1
		return NULL;
	}

    //novi podaci upisani u strukturu se kopiraju u varjablu
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
    //Zatvaranje unosa
	newPerson->next = NULL;

	return newPerson;
}

//No. 2
//ispis osobe koje su unesene 
int PrintList(Position Head)
{
	Position temp = Head->next;
    
    if(temp==NULL){
        printf("\tLista je prazna!");
    }
    else
    {
        //dok temp nije NULL petlja se izvršava
        //temp pokazuje na adresu clana poslije head-a, a ispisom petlja odmah prenosi adrseu na slijedeci clan
	while (temp) {
		printf("Ime: %s  Prezime: %s  Godina izdavanja: %d\n",
			temp->name, temp->surname, temp->birthYear);
         //ide na slijedecu osobu, poput i++ u brojevima   
		temp = temp->next;
	}
    }

	return EXIT_SUCCESS;
}

//No. 3
//Unos osobe na pocetak liste
int UnosP(Position Head, char* name, char* surname, int birthYear)
{
    //uvjet !!
	Position newPerson = NULL;

    //newPerson smo postavili na funkciju koja "stvara" člana
	newPerson = CreatePerson(name, surname, birthYear);
    
    //Ne postoji.
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	InsertAfter(Head, newPerson);

	return EXIT_SUCCESS;
}

//Funkcija u kojoj mijenjamo pozicije adresa clanova
//Zadnji pokazuje na prethodnog
int InsertAfter(Position Last, Position newPerson)
{
	newPerson->next = Last->next;
	Last->next = newPerson;

	return EXIT_SUCCESS;
}


//No. 4
//Unos osobe na kraj liste
int UnosK(Position Head, char* name, char* surname, int birthYear)
{
    //Treba nam novi clan koji unosimo i trebamo pronaci zadnji clan na mjesto kojeg unosimo
    //postavljanje na početak
	Position newPerson = NULL;
	Position Last = NULL;

    //Treba nam osoba koju stavljamo na kraj
	newPerson = CreatePerson(name, surname, birthYear);

    //Ako ne postoji
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

    //Posljednji clan
	Last = FindLast(Head);

    //Zamjena clanova kao sto se trazi
	InsertAfter(Last, newPerson);

	return EXIT_SUCCESS;
}

//Trazenje zadnjeg clana
//funkcija je oblika struct
Position FindLast(Position Head)
{
	Position temp = Head;
    //dok temp ne dode do NULL znaka koji je povezan sa zadnjim clanom
	while (temp->next)
	{
        //prelazi na sljedeci clan u nizu
		temp = temp->next;
	}

    //funkcija vraca posljenji clan niza
	return temp;
}
Position trazenje_po_prezimenu(Position head,char* surname_trazenog){
	Position temp = head->next;
	do{
		if(strcmp(temp->surname,surname_trazenog)==0)
		{
			return temp;
		}	
		temp = temp->next;
		
	}while (temp!=NULL);
	return NULL;
}
Position trazenje_po_prezimenu_osobe_ispred(Position head,char* surname_trazenog){
	Position temp = head->next;
	Position temp_prije = head;
	do{
		if(strcmp(temp->surname,surname_trazenog)==0)
		{
			return temp_prije;
		}	
		temp = temp->next;
		temp_prije = temp_prije->next;
		
	}while (temp!=NULL);
	return NULL;
}


int brisanje_clana(Position head,char* surname_trazenog){
	Position temp = head->next;
	Position temp_prije = head;
	do{
		if(strcmp(temp->surname,surname_trazenog)==0)
		{
			temp_prije->next=temp->next;
			free(temp);
		}	
		temp = temp->next;
		temp_prije = temp_prije->next;
		
	}while (temp!=NULL);
	PrintList(head);
	
	return EXIT_SUCCESS;
}
int dodavanje_iza_odredenog_elementa(Position head,char* surname_trazenog,char* name,char* surname,int birthYear){
    Position newPerson = CreatePerson(name, surname, birthYear);
    Position temp=trazenje_po_prezimenu(head,surname_trazenog);
    newPerson->next =  temp->next;
    temp->next = newPerson; 
    PrintList(head);
    return 0;
}
int dodavanje_prije_odredenog_elementa(Position head,char* surname_trazenog,char* name,char* surname,int birthYear){
	Position newPerson = CreatePerson(name, surname, birthYear);
    Position temp=trazenje_po_prezimenu_osobe_ispred(head,surname_trazenog);
    newPerson->next =  temp->next;
    temp->next = newPerson; 
    PrintList(head);
    return 0;

}
int zamjena_pozicija(Position temp_temp,Position temp_1,Position temp_2){
	temp_temp->next=temp_2;
	temp_1->next=temp_2->next;
	temp_2->next=temp_1;
	
	return 0;
}
int broj_clanova_niza(Position head){
    int brojac=0;
	while (head->next != NULL)
	{
        //prelazi na sljedeci clan u nizu
		head = head->next;
		brojac++;
	}
	return brojac;
}

int jebeni_buble_sort(Position head){
	Position temp_temp= head;
	Position temp_1=head->next;
	Position temp_2=temp_1->next;//ovo isto radi
	printf("test1");
	if(head->next=NULL){
		perror("prazna lista se nemore soritati koga budalon pravis!");//provjera liste
		return 0;
	}
	if(head->next->next=NULL){
	perror("Ne mores samo jedan clan sortirati koji ti je bog!");//provjera liste
	return 0;	
	}
	printf("test 2");
	int br_clanova = broj_clanova_niza(head);
	
	for(int i=0;i<br_clanova;i++)
      for(int j=i;j<br_clanova-1;j++){
         if(strcmp(temp_1->surname,temp_2->surname)>0){
            zamjena_pozicija(temp_temp,temp_1,temp_2);//funkcija radi provjeria san
            temp_temp=temp_temp->next;
            temp_1=temp_1->next;
            temp_2=temp_2->next;
         }
         printf("test 3");
    	temp_temp= head;
		temp_1=head->next;
		temp_2=head->next->next;
         
      }
}

int jebeni_buble_sort_2(Position head){
	Position temp_1= head;
	Position temp_2=head->next;
	int br_clanova = broj_clanova_niza(head);
	
	for(int i=0;i<br_clanova-1;i++){
      do{
         if(strcmp(temp_1->surname,temp_2->surname)<0){
				Position temp = CreatePerson(temp_1->name,temp_1->surname,temp_1->birthYear);	         
        	 	strcpy(temp_1->name,temp_2->name);
        	 	strcpy(temp_1->surname,temp_2->surname);
        	 	temp_1->birthYear = temp_2->birthYear;
        	 	strcpy(temp_2->name,temp->name);
        	 	strcpy(temp_2->surname,temp->surname);
        	 	temp_2->birthYear = temp->birthYear;
            }
            temp_1=temp_1->next;
            temp_2=temp_2->next;
            	
            }while(temp_2 != NULL);
            
		temp_1=head;
		temp_2=head->next;
		}
         
}
/*
int zamjena(Position temp_1,Position temp_2){

	char temp_name[MAX_SIZE] = { ' ' };
	char temp_surname[MAX_SIZE] = { ' ' };
	int temp_birthYear = 0;
	strcpy(temp_name,temp_1->name);
    strcpy(temp_surname,temp_1->surname);
    temp_birthYear = temp_1->birthYear;
  	strcpy(temp_1->name,temp_2->name);
    strcpy(temp_1->surname,temp_2->surname);
    temp_1->birthYear = temp_2->birthYear;
    strcpy(temp_2->name,temp_name);
    strcpy(temp_2->surname,temp_surname);
    temp_2->birthYear = temp_birthYear;
		
}*/
int jebeni_buble_sort_3(Position head) 
{ 
    int zamjena_provjera, i; 
    Position temp; 
    Position zadnji = NULL; 
  
    /* Checking for empty list */
  
    do
    { 
        zamjena_provjera = 0; 
        temp = head; 
  
        while (temp->next != zadnji) 
        { 
            if (temp->surname > temp->next->surname) 
            { 
                zamjena(temp, temp->next); 
                zamjena_provjera = 1; 
            } 
            temp = temp->next; 
        } 
        zadnji = temp; 
    } 
    while (zamjena_provjera); 
    return 0;
} 
	
	

