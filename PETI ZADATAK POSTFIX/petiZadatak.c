#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50

//Napisati program koji iz datoteke cita postfiks izraz 
//zatim koristenjem stoga racuna rezultat.
//Stog je potrebno realizirati preko vezane liste.

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
int Pop(double* destinacija, Position Head);
int Operacija(Position Head, char op);
int RacunDat();
int CleanUp(Position Head);

int main()
{
	RacunDat();
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

//Stavi na pocetak poslije head-a UnosPocetak
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

//BrisiPrvi
int Pop(double* trazeni, Position Head)
{
	Position prvi = Head->next;

	if (!prvi) //prvi == NULL
	{
		perror("\n Operacije su izvrsene ili nesto nije u redu sa zadanim postfix-om :)!!\n");
		return -1;
	}

	*trazeni = prvi->broj;

	DeleteAfter(Head); 

	return EXIT_SUCCESS;
}

int CleanUp(Position Head)
{
	Position temp = Head;

	while (temp->next != NULL)
	{
		DeleteAfter(temp);
	}

	return EXIT_SUCCESS;
}

int Operacija(Position Head, char op)
{
	double varijabla2 = 0.0;
	double varijabla1 = 0.0;
	double rez = 0.0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;


	status2 = Pop(&varijabla2, Head); //kada ga makne funkcija vraca 0, ako nije makla program se prekida
	if (status2 != EXIT_SUCCESS)
		return -1;

	status1 = Pop(&varijabla1, Head);
	if (status1 != EXIT_SUCCESS)
		return -1;

	switch (op)
	{
	case '+':
	{
		rez = varijabla1 + varijabla2;
		printf("%lf %c %lf = %lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	case '-':
	{
		rez = varijabla1 - varijabla2;
		printf("%lf %c %lf = %lf\n", varijabla1, op, varijabla2, rez);
		break;
	}

	case '*':
	{
		rez = varijabla1 * varijabla2;
		printf("%lf %c %lf = %lf\n", varijabla1, op, varijabla2, rez);
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
		printf("%lf %c %lf = %lf\n", varijabla1, op, varijabla2, rez);
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
	int fpDuljina = 0;
	char* buffer = NULL;
	char* readingBuffer = NULL;
	int procitan_bb = 0;
	char op = 0; //racunska operacija
	double vrijednost = 0;
	int status = 0;
	int brojac = 0;
	El Head = { .broj = 0, .next = NULL };
	fp = fopen("input.txt", "r");

	if (!fp)
	{
		perror("Nije moguce otvoriti datoteku!\n");
		return -1;
	}

	
	fseek(fp, 0, SEEK_END);//sets the file position of the stream to a given offset. 
                        //The pointer associated with the file is moved to that offset.
                        //ide na kraj jer se tamo nalazi clan kojeg prvo trazimo

	fpDuljina = ftell(fp); //used to get the total size of file
                          // after moving the file pointer at the end of the file

	buffer = (char*)malloc((fpDuljina)*sizeof(char));

	if (!buffer)
	{
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	rewind(fp);//sets the file position to the beginning of the file of the given stream.

	fread(buffer, sizeof(char), fpDuljina, fp);//reads up to count items of size length from the input stream and stores them in the given buffer

	printf("Postfixi iznose: \n");
	fclose(fp);

	readingBuffer = buffer;
	while (strlen(readingBuffer) > 0)
	{
		brojac = sscanf(readingBuffer, " %lf %n", &vrijednost, &procitan_bb); //the function returns the number of variables filled
																			//cita vijednost

		if (brojac == 1)
		{
			//stavlja vrijednost na pocetak liste ako je tipa double
			Push(&Head, vrijednost);
			readingBuffer += procitan_bb; //i++
		}

		else
		{
			sscanf(readingBuffer, " %c %n", &op, &procitan_bb);  //cita znak operacije
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
				readingBuffer += procitan_bb; //i++
			}
		}
	
		free(buffer);

		return EXIT_SUCCESS;
}
