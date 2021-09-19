/*
Gabriele Multari
Realizzare un programma che, data una matrice di n righe ed m colonne, permetta di
visualizzare il massimo degli elementi di ciascuna riga, il minimo di tutti gli elementi della matrice
e la media di ciascuna colonna
*/

#include <stdlib.h>
#include <stdio.h>
#define RIGA 4          //costante che determina il numero di righe nella matrice
#define COLONNA 4       //costante che determina il numero di colonne nella matrice


int Massimo_Righe(int matrice[RIGA][COLONNA],int riga)		//funzione che ritorna all'utente il numero maggiore di ogni riga
{
int Massimo_Righe,i;
 Massimo_Righe=matrice[riga][0];

for(i=0;i<COLONNA;i++)										//ciclo che determina il numero maggiore in ogni riga per una determinata colonna
	if(matrice[riga][i]>Massimo_Righe)
     Massimo_Righe=matrice[riga][i];
return Massimo_Righe;
}

int Valore_Minimo(int matrice[RIGA][COLONNA])				//funzione che ritorna il valore minore della matrice
{
int Valore_Minimo,i,j;
 Valore_Minimo=matrice[0][0];
 
for(i=0;i<RIGA;i++)											//ciclo che determina in numero minimo in ogni riga e colonna
    for(j=0;j<COLONNA;j++)
        if(matrice[i][j]<Valore_Minimo)
         Valore_Minimo=matrice[i][j];
return Valore_Minimo;
}


double Media_Colonne(int matrice[RIGA][COLONNA],int colonna)			//funzione che ritorna all'utente la media dei valori nelle colonne (double perchè la variabile ritornata è un double)
{
int somma,i;
double media;
somma=0;

for(i=0;i<RIGA;i++)
 somma+=matrice[i][colonna];
  media=(double)somma/RIGA;
return media;
}


void RiempiMatrice(int matrice[RIGA][COLONNA])			//procedura che chiede l'input dei valori
{
printf("Inserisci i numeri\n\n");
	for(int i=0;i<RIGA;i++)
     for(int j=0;j<COLONNA;j++)
    {
    printf("Riga %d Colonna %d: ",i+1,j+1);
    scanf("%d",&matrice[i][j]);
    }
}


void StampaMatrice(int matrice[RIGA][COLONNA])			//procedura che stampa la griglia dei numeri
{
int i, j;
system("cls");
 for(i=0;i<RIGA;i++)												//ciclo per stampare i valori nella riga
  {
    for(j=0;j<COLONNA;j++)											//ciclo per stampare i valori nella colonna
     printf("%4d",matrice[i][j]);									//output dei valori nella matrice
     printf("\n");
  }

printf("\nValore maggiore\n");										//stampa il valore più grande in ogni riga
	for(i=0;i<RIGA;i++)
     printf("\nIl valore maggiore nella Riga %d %c %d.",i+1,138,Massimo_Righe(matrice,i));

printf("\n\nIl valore pi%c piccolo di tutta la griglia %c %d.\n",151,138,Valore_Minimo(matrice));					//stampa il valore più piccolo di tutta la griglia
								
    for(i=0;i<COLONNA;i++)
     printf("\nLa media della colonna %d %c %.2f.",i+1,138,Media_Colonne(matrice,i));				//stampa la media dei valori di ogni riga 
}


int main()
{
int matrice[RIGA][COLONNA];
 RiempiMatrice(matrice);
 StampaMatrice(matrice);
return 0;
}
