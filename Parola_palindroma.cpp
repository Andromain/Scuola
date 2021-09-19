/* Gabriele Multari  31 agosto 2021
	Scrivere un programma che acquisisca da tastiera una parola (cioè una stringa di caratteri priva di
	separatori) e dica se tale parola è palindroma, ossia leggibile nello stesso modo da destra a sinistra e
	viceversa
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#define DIM 20

void input_parola(char word[DIM])   //funzione che prende in input la parola
{
  int i;
  int errore = 0;
  do{
  	if(errore==1)
  	{
  	printf("Non hai inserito una parola valida");
  	getch();
  	system("cls");
  	errore=0;
    }
    printf ("Inserisci una parola palindroma --> ");
  	gets (word);
  for (i = 0; i < strlen (word); i++)
  	word[i] = toupper (word[i]);   //trasforma tutte le lettere da minuscole a maiuscole
  i = 0;
  do
  {
  	if ((word[i] < 'A' || word[i] > 'Z' ) && word[i] != ' ')   //controlla che i caratteri inseriti siano validi
  		errore = 1;
  	i++;
  }
  while (i < strlen (word) && errore == 0);
	}while(errore==1);
	system("cls");
}

void controlla_palindro(char word[DIM], char word2 [DIM])     //funzione che controlla se la parola inserita sia palindroma
{
    strcpy(word2, word);
    for (int i = 0; i < strlen (word); i++) 
        word2[i] = word[strlen (word)-i-1];

    if (strcmp(word,word2) == 0)    //se le stringhe sono uguali
        printf("La parola inserita %c palindroma.\n\n",138);
    else
        printf("La parola digitata non %c palindroma.\n\n",138);

    system("pause");
}

int main ()
{
 char word[DIM];
 char word2[DIM];
 input_parola(word);
 controlla_palindro(word,word2);
}
