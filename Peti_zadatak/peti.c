#include <stdio.h>
#include<stdlib.h>
#define MAX_SIZE 128

struct Element;
typedef struct Element * Stog; //Position
typedef struct Element {
    
    double broj; //double zbog djeljenja
    Stog next;

} El;

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

    //Stavit cu da korisnik unosi ime datoteke jer je Duje reka prosli put

    char dat [MAX_SIZE] = { 0 };

    printf("Unesite ime datoteke: ");
    scanf(" %s", dat);

    System();//Da bude urednije


    return 0;
}