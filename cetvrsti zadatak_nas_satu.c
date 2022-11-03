//Napisati program za zbrajanje i mnozenje polinoma.
//Koeficijenti i eksponenti se citaju iz datoteke.
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

struct Polinom;
typedef struct Polinom* Position;

typedef struct Polinom{
    int koef; //koeficijent
    int eks; //eksponent ili potencija
    Position next;  
}Izraz;

int Read_file(Position head);
Position Make_pol(int koef, int eks);
int Ispis(Position P); 
int InsertAfter(Position Last,Position new_number);

int System(){
 #ifdef LINUX_KEY_WORD
    system("clear");
  #elif WINDOWS_KEY_WORD
    system("cls");
  #else 
     "OS not supported!";
  #endif
  return 0;
  
}

int main(){

    System();
    int answer = 1;

    Izraz head_1 = { .koef = 0, .eks = 0, .next = NULL};
		
		//Tribaju nam 2 reda polinoma koje mozemo zbrajati i mnoziti
    Position P_1 = &head_1;

    while (answer != 0)
    {
        system("cls");
        printf("Odaberite broj ovisno o zeljenoj vrsti racunanja: \n");
        printf("ZBROJ (1)\n");
        printf("UMNOZAK (2)\n");
        printf(" Kraj (0)\n");
        printf("Unesite vas odabir:  ");
        scanf(" %d", &answer);

        switch(answer)
        {
            case 0:
                break;
            
            case 1:
            
                Read_file(P_1);

                printf(" Polinomi iz datoteke :\n 1. red:\t");
              	Ispis(P_1);
                break;
                //DODAJ JOS CISCENJE MEMORIJE 
            case 2:    
                    //Odma san ti kopira da provjerim radi li             
             if(Read_file(P_1) == 0 ) break;


            default:
                printf("Niste unijeli ponudeni broj.");
                break;

        }
    }

    return EXIT_SUCCESS;

}
int Read_file(Position head){
    Position p = head;
    int koeficijent=0,eksponent=0,n=0;
    
    Position q = NULL;
    FILE *fp= NULL;
    char buffer[MAX_SIZE]={0};
    fp = fopen("binomi.txt","r");
    
    if(fp==NULL){  
        perror("Nije moguce otvoriti datoteku!!\n");
        return -1;    	
    }
    while(!feof)
    {
        fgets(buffer,MAX_SIZE,fp);
        sscanf(q,"%d %d %n",&koeficijent,&eksponent,&n);

        
    
    }

    
    
}

int InsertAfter(Position Last, Position new_number)
{
	new_number->next = Last->next;
	Last->next = new_number;

	return 0;
}

Position Make_pol(int ko, int e){

    Position New = NULL;

    New = (Position) malloc (sizeof(Izraz));

    New -> koef = ko;
    New -> eks = e;
    New -> next = NULL;
    printf("provjera novi clan:%d",New->eks);

    return New;
}

int Ispis(Position P){
	Position temp = P->next;
    
    if(temp==NULL){
        printf("\tLista je prazna!\n");
    }
    else
    {

    while(temp){
        printf(" %d x^(%d)\n", temp->koef, temp->eks );
        temp = temp -> next ;//i++
    }

    return 0;
}
