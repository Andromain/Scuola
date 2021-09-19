/* Gabriele Multari 31 agosto 2021
	Scrivere un programma che permetta all’utente di inserire un’intera frase. Il programma
	successivamente visualizzi il numero di parole che compone la frase. Si supponga che una frase sia
	costituita di parole, dove una parola è una sequenza di caratteri diversi dallo spazio e delimitata da
	uno o più spazi a destra e sinistra. Uno o più spazi possono aprire o chiudere la frase.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 100

void input(char frase[DIM])
{
printf("Digitare una frase --> ");
gets(frase);
}

void conta_spazi(char frase[DIM],int *space)
{
for(int i=0;i<strlen(frase);i++)
if(frase[i] == ' ')
*space=*space+1;
}

void output(int *space)
{
if(*space>0)
printf("\nNella frase sono presenti %d parole.\n\n", *space+1);
else
printf("\nNella frase %c presente una parola.\n\n",138);
}



int main()
{
int spazio;
char frase[DIM];
input(frase);
conta_spazi(frase,&spazio);
output(&spazio);
system("pause");
/*
printf("Digitare una frase -->  ");
gets(frase);
fflush(stdin);
*/
/*
spazio = 0;

for(i=0;i<strlen(frase);i++)

if(frase[i] == ' ')
spazio++;
*/


/*
if(spazio>0)
printf("\nNella frase sono presenti %d parole.\n\n", spazio+1);
else
printf("\nLa frase %c formata da una parola sola.\n\n",138);

system("pause");
*/
}
