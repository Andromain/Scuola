/* Gabriele Multari 31/08/2021
Scrivere un programma che realizzi il gioco del Master Mind. Bisogna indovinare in 10 tentativi
un numero di 4 cifre pensato dal computer. Il numero in realtà sarà composto da 4 cifre singole
contenute in un vettore di tipo int di 4 posizioni. Ad ogni tiro il computer risponde indicando quante
cifre giuste al posto giusto e quante cifre giuste al posto sbagliato ci sono nel vostro numero.*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>

#define DIM 4   //dimensione del vettore
#define TENT 10  //tentativi disponibili al giocatore

//using namespace std;

void crea_vet(int vett[],int n,int win,int j)    //procedura che genera 4 numeri random non duplicati nel vettore
{
  srand (time(0));
  for(short i=0;i<DIM;i++)    //controllo per numeri duplicati nel vettore
  {
  vett[i]=rand()%9+1;
  for(j=0;j<i;j++) {
       	if(vett[i]==vett[j])
		{
        	i--;
        	break;
        }
     }
}
}
void cheat(int vet[DIM])      //procedura che ti permette di scoprire i numeri da indovinare
{
printf("\nI valori del vettore  sono --> ");  		
    for (short i=0;i<DIM;i++)
    {
        printf("%d ", vet[i]);
    }
}

void input(int n,int c[4],int win,int p,int i)
{
      printf("\n%d%c Turno\n",p,248);
      printf("\nInserisci quattro numeri:\n");
      for (short j=0;j<4;j++)
      {
     do{
          do
          scanf("%d",&n);
          while (n<0 || n>9);
          win=false;
          for (i=0;i<j;i++)
          {
            if (c[i]==n)     //controllo per numeri duplicati nell'input
			{
              win=true;
               printf("Il numero inserito c'%c gi%c inserirne un altro.\n",138,133);
            }
          }
	   }
		while (win==true);   
         c[i]=n;
      }
}

void output(int win,int aster,int zeri,int vet[DIM],int p,int c[4],int n,int i)  //procedura che stampa l'output e controlla la vittoria/sconfitta.
{
do{
input(n,c,win,p,i);
win=false;
aster=0;
      zeri=0;
      for (short i=0;i<4;i++)
      {
          for (short j=0;j<4;j++)
          if (vet[i]==c[j])
             if (i==j)
                aster=aster+1;
             else
                zeri=zeri+1;
      }
      printf("Numeri indovinati nella posizione giusta:%d\n",aster);     //il numero è nella posizione giusta
	  printf("\nNumeri indovinati:%d\n",zeri);                           //il numero è nella sequenza ma non nella posizione giusta
       if (aster==4){
          win=true;
          if (p==1)
		  {
          system("cls");
          printf("Congratulazioni!\n\nHai vinto in un solo turno\n");
          }
          else
		  {
          system("cls");
          printf("Congratulazioni!\n\nHai vinto in %d turni\n",p);
          }
        }
      p++;
      }while(win==false && p<=TENT); //se il numero di tentativi massimi viene superato il gioco termina e viene stampato il risultato.
      for(short i=0;i<=3;i++)
      printf("\n%d",vet[i]);
}

int main()
{
	int vet[DIM],zeri,aster,n,win,j,v,p=1,c[4],i;
	crea_vet(vet,n,win,j);
	//cheat(vet);
	output(win,aster,zeri,vet,p,c,n,i);
}
