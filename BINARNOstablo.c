#include<stdio.h>
#include<stdlib.h>

typedef struct Stablo * Position;

typedef struct Stablo{
    int El;
    Position L;//pokazivac na livog
    Position D;//pokazivac na desnog
} stablo;

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

Position Unos(Position trenutni, int element);
//Position Unos(Position trenutni, Position q);
int PrintInOrder(Position trenutni);
int PrintPreOrder(Position trenutni);
int PrintPostorder(Position trenutni);


int main(){

    Position root =NULL;
    Position  q = NULL;
    int answer,number;

    do {
        printf("\n**********************\n");
        printf("\nOdaberite zeljenu operaciju:\n");
        printf(" 1 -dodaj element u stablo\n");//kako boldirati ili ukositi(italic) slova u c-u
        printf(" 2 -ispis elemenata <INORDER>\n");
        printf(" 3 -ispis elemenata <PREORDER>\n");
        printf(" 4 -ispis elemenata <POSTORDER>\n");
        printf(" 5 -ispis elemenata <LEVEL ORDER>\n");
        printf(" 6 -trazi element\n");
        printf(" 7 -brisi element\n");
        printf(" 8 -exit\n");
        printf("\n**********************\n");

        printf("Unos: ");
        scanf("%d", &answer);
        //System();
        system("cls");
        switch(answer){

            case 1:
                printf("Unesite broj koji zelite unijeti u stablo :\n");
                scanf("%d", &number);
                q = (Position)malloc(sizeof(stablo));
                q->El = number;
                root = Unos(root,number);
                //root = Unos (root,q);
                break;

            case 2:
                printf("\n****ISPIS****\n");
                PrintInOrder(root);
                break;
            
            case 3:
                PrintPreOrder(root);
                break;

            case 4:
                PrintPostorder(root);
                break;

            case 8:
                return 0;

            default:
                printf("Unijeli ste krivi broj, pokusajte ponovno! :)\n");
        }

    } while( answer != '8');

    return 0;
}

Position Unos(Position trenutni, int element){

    if(NULL == trenutni){
        trenutni =(Position)malloc(sizeof(stablo));//alokacija za novi el
        trenutni->El = element;
        trenutni->L = NULL;
        trenutni->D = NULL;
        return trenutni;
    } 

    //ako je veci ide DESNO
    else if(element > trenutni->El){
        trenutni->D = Unos(trenutni->D,element);
    }

    else if(element < trenutni->El){
        trenutni->L = Unos(trenutni->L,element);
    }

    else 
    free(trenutni->El); 

    return trenutni;
}

/*Position Unos(Position trenutni, Position q){

    if(NULL == trenutni){
        return q;
    }

    else if(trenutni -> El < q->El){
        trenutni->D = Unos(trenutni->D,q);
    }

    else if(trenutni->El > q->El){
        trenutni->L = Unos(trenutni->L, q);
    }
    else
    free (q->EL);

    return trenutni;
}*/

//Livo gori desno  od manjeg prema vecem
int PrintInOrder(Position trenutni){

    if(trenutni != NULL){
        PrintInOrder(trenutni->L);
        printf(" \t\t%d\n", trenutni->El);
        PrintInOrder(trenutni->D);
    }
    return 0;
}

//gori livo desno 
int PrintPreOrder(Position trenutni){

    if(trenutni != NULL){
        printf(" %d\n", trenutni->El);
        PrintPreOrder(trenutni->L);
        PrintPreOrder(trenutni->D);
    }
    return 0;
}

//livo desno gori
int PrintPostorder(Position trenutni){

   if(trenutni){
        PrintPreOrder(trenutni->L);
        PrintPreOrder(trenutni->D);
        printf(" %d\n", trenutni->El);
    }
    return 0;
}