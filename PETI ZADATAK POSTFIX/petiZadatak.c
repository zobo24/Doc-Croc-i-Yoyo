#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50

/*Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna
rezultat.Stog je potrebno realizirati preko vezane liste.*/

struct Element;
typedef struct Element* Position;

typedef struct Element {
	double broj;
	Position next;
}El;

Position MakeElement(double broj);
int InsertAfter(Position P, Position newElement);
int Push(Position Head, double broj);
int DeleteAfter(Position P);
int Pop(double* trazeni, Position Head);
int Operacija(Position Head, char op);
int RacunDat(char *dat);
int CleanUp(Position Head);

int main()
{

	char dat[] = { 0 };
	printf("Unesite ime datoteke: ");
	scanf(" %s", dat);
	RacunDat(dat);
	return EXIT_SUCCESS;
}

Position MakeElement(double broj)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(El));
	if (!newElement)
	{
		perror("Nije moguce alocirati memoriju!\n");
		return NULL;
	}

	newElement->broj = broj;
	newElement->next = NULL;

	return newElement;

}

int InsertAfter(Position P, Position newElement)
{
	newElement->next = P->next;
	P->next = newElement;

	return EXIT_SUCCESS;
}
//Stavlja na pocetka poslije head-a
int Push(Position Head, double broj)
{
	Position newElement = NULL;

	newElement = MakeElement(broj);
	if (!newElement)
		return -1;

	InsertAfter(Head, newElement);
}

int DeleteAfter(Position P)
{
	Position temp = P->next;

	if (!temp)
		return EXIT_SUCCESS;

	P->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}
//skida vrijednost poslije head-a
int Pop(double* trazeni, Position Head)
{
	Position clan = Head->next;

	if (!clan) //clan == NULL
	{
		perror("\n Kraj :)!!\n");
		return -1;
	}

	*trazeni = clan->broj; 

	DeleteAfter(Head); 

	return EXIT_SUCCESS;
}

int CleanUp(Position Head)
{
	while (Head->next != NULL)
	{
		DeleteAfter(Head);
	}

	return EXIT_SUCCESS;
}

int Operacija(Position Head, char op)
{
	double varijabla1 = 0.0;
	double varijabla2 = 0.0;
	double rez = 0.0;
	int s_1 = EXIT_SUCCESS;
	int s_2 = EXIT_SUCCESS;


	s_2 = Pop(&varijabla2, Head);
	if (s_2 != EXIT_SUCCESS)
		return -1;

	s_1 = Pop(&varijabla1, Head);
	if (s_1 != EXIT_SUCCESS)
		return -1;

	switch (op)
	{
	case '+':
	{
		rez = varijabla1 + varijabla2;
		printf("%.3lf %c %.3lf = %.3lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	case '-':
	{
		rez = varijabla1 - varijabla2;
		printf("%.3lf %c %.3lf = %.3lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	case '*':
	{
		rez = varijabla1 * varijabla2;
		printf("%.3lf %c %.3lf = %.3lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	case '/':
	{
		if (varijabla2 == 0)
		{
			printf("Dijeljenje s 0 nije moguce!\n");
			return -1;
		}
		rez = varijabla1 / varijabla2;
		printf("%.3lf %c %.3lf = %.3lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	default:
	{
		printf("Operacija nije podrzana!\n");
		CleanUp(Head);
		return -1;
	}
	}
	Push(Head, rez);

	return EXIT_SUCCESS;
}

int RacunDat(char* dat)
{

	FILE* fp = NULL;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int procitan_bb = 0;
	char op = 0; //racunska operacija
	double vrijednost = 0;
	int brojac = 0;
	int status = 0;
	El Head = { .broj = 0, .next = NULL };

	fp = fopen( dat, "r");

	if (!fp)
	{
		perror("Nije moguce otvoriti datoteku!\n");
		return -1;
	}

	buffer = (char*)malloc( MAX_SIZE*sizeof(char));

	if (!buffer)
	{
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	fgets(buffer,MAX_SIZE,fp);

	printf("Postfixi iznose: \n");
	fclose(fp);

	currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		brojac = sscanf(currentBuffer, " %lf %n", &vrijednost, &procitan_bb); //the function returns the number of variables filled
																			//cita vijednost

		if (brojac == 1)
		{
			//stavlja vrijednost na pocetak liste ako je tipa double
			Push(&Head, vrijednost);
			currentBuffer += procitan_bb; //i++
		}

		else
		{
			sscanf(currentBuffer, " %c %n", &op, &procitan_bb);  //cita znak operacije
			status = Operacija(&Head, op); //Sa statusom napravit provjeru , ukoliko vrati -1 izbrisati listu 

			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				while (Head.next != NULL)
				{
					DeleteAfter(&Head);
				}
				return -1;
			}
				currentBuffer += procitan_bb; //i++
			}
		}
	
		free(buffer);

		return EXIT_SUCCESS;
}
