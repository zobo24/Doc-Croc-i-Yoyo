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

int Read_file(Position head_1, Position head_2);
Position Make_pol(int koef, int eks);
int Ispis(Position P); 
int Clean_up(Position head);

int main(){

    int answer = 1;

    Izraz head_1 = { .koef = 0, .eks = 0, .next = NULL};
    Izraz head_2 = { .koef = 0, .eks = 0, .next = NULL};

    //Tribaju nam 2 reda polinoma koje mozemo zbrajati i mnoziti
    Position P_1 = &head_1;
    Position P_2 = &head_2;

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
            
                if(Read_file(P_1,P_2) == 0 ) break;

                printf(" Polinomi iz datoteke :\n 1. red:\t");
                Ispis(P_1);
                printf("\n 2. red:\t");
                Ispis(P_2);
                break;
                //DODAJ JOS CISCENJE MEMORIJE 
            case 2:    
                    //Odma san ti kopira da provjerim radi li             
             if(Read_file(P_1,P_2) == 0 ) break;

                printf(" Polinomi iz datoteke :\n 1. red:\t");
                Ispis(P_1);
                printf("\n 2. red:\t");
                Ispis(P_2);
                break;

            default:
                printf("Niste unijeli ponudeni broj.");
                break;

        }
    }

    return EXIT_SUCCESS;

}

int Read_file(Position head_1, Position head_2){

    FILE* fp = NULL;
    
    fp= fopen("Polinom.txt","r");

    if(fp==NULL){   //!fp
        perror("Nije moguce otvoriti datoteku!!\n");
        return -1;    	
    }

    fclose(fp);

    return 0;
}


Position Make_pol(int ko, int e){

    Position New = NULL;

    New = (Position) malloc (sizeof(Izraz));

    New -> koef = ko;
    New -> eks = e;
    New -> next = NULL;

    return New;
}

int Ispis(Position P){

    Position temp = P -> next;

    while(temp){
        printf(" %d x^(%d)\n", temp -> koef, temp -> eks );
        temp = temp -> next ;//i++
    }

    return 0;
}

int Clean_up(Position head){

    Position P=head;
    Position temp = NULL;

    while( NULL != P-> next){
        temp = P -> next;
        P -> next = temp -> next;
        free(temp);
    }
    return 0;
}
