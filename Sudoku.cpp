#include <stdio.h>
#include <conio.h>

int  CercaCertezze (int Tav[][9][10], int *Nvuote );
int  CercaSudoku   (int Tav[][9][10], int Nvuote );
int  Congruenza    (int Tav[][9][10] );
void CopiaTavola   (int Source[][9][10], int Destin[][9][10]);
void InitTavola    (int Tav[][9][10], int *Nvuote );
void LeggiTavola   (int Tav[][9][10], int *Nvuote );
void ScriviCella   (int Tav[][9][10], int r, int c, int n, int *Nvuote);
void StampaTavola  (int Tav[][9][10], int Nvuote );

/*=============================================================================
             S U - D O K U
            ^^^^^^^^^^^^^^^ 
Un Sudoku è una griglia quadrata di 81 celle: 9 righe orizzontali per 9 
colonne verticali; inoltre, la griglia è divisa in 9 riquadri 3x3 (gruppi, 
col bordo più spesso) di 9 celle ciascuno. 

Ciascuna riga orizzontale, colonna verticale e riquadro di 3x3 celle 
contiene una sola volta tutti i numeri da 1 a 9; pertanto in nessuna riga, 
colonna e riquadro può esserci un numero ripetuto. 

TAVOLA DI GIOCO
^^^^^^^^^^^^^^^     0   1   2   3   4   5   6   7   8 
                  *===*===*===*===*===*===*===*===*===*
                0 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---*
                1 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---*
                2 H   |   |   H   |   |   H   |   |   H
                  *===*===*===*===*===*===*===*===*===*
                3 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---* 
                4 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---* 
                5 H   |   |   H   |   |   H   |   |   H
                  *===*===*===*===*===*===*===*===*===*
                6 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---* 
                7 H   |   |   H   |   |   H   |   |   H
                  *---+---+---*---+---+---*---+---+---* 
                8 H   |   |   H   |   |   H   |   |   H
                  *===*===*===*===*===*===*===*===*===*

CELLA
^^^^^ Ogni Cella della Tavola di gioco è un array di 10 caselle
      *---+---+---+---+---+---+---+---+---+---+
      |   |   |   |   |   |   |   |   |   |   | 
      *---+---+---+---+---+---+---+---+---+---+
        0   1   2   3   4   5   6   7   8   9
La casella 0 indica se la cella è libera (0) o occupata (1..9).
Le nove caselle successive indicano ciascuna la possibilità di inserire 
nella cella il valore corrispondente (Flag 1=inserimento possibile).

GRUPPI
^^^^^^
Chiameremo Gruppi i 9 Riquadri 3x3 interni. 
Detta (i,j) una cella della Tavola, le coordinate della cella in alto a 
sinistra del suo gruppo di appartenenza saranno:
ig = (i / 3) * 3 = i - i % 3
jg = (j / 3) * 3 = j - j % 3
Il gruppo sarà composto dalle nove celle (y,x) con 
ig <= y <= ig+2 e jg <= x <= jg+2 
----------------------------------------------------------------- 9.10.2005 -*/ 

int main ()
{
  int Tav [9][9][10], // 1° riga, 2° colonna, 3° campi della cella
      Nvuote;         // Numero di caselle vuote nella tavola 

  InitTavola (Tav, &Nvuote);
  LeggiTavola (Tav, &Nvuote);
  StampaTavola (Tav, Nvuote);
  printf("\nbatti un tasto per iniziare l'analisi ...\n"); _getch();

  // Dapprima cerca di risolvere il gioco con posizioni certe
  while ( CercaCertezze (Tav, &Nvuote) ); 
  StampaTavola (Tav, Nvuote);

  // In seconda battuta esegue una ricerca combinatoria ricorsiva
  if ( ! Nvuote )
    printf ("\nSoluzione trovata.\n");
  else 
  { printf("\nbatti un tasto per la ricerca combinatoria ...\n"); 
    _getch();
    if ( CercaSudoku(Tav,Nvuote) ) 
    { StampaTavola (Tav, 0);
      printf ("\nSoluzione trovata.\n");
    } 
    else
      printf("\nNON esistono soluzioni\n"); 
  }
  _getch();
}

/*=============================================================================
 Cerca di completare la tavola da gioco, ALMENO con una cella vuota, provando 
 ad inserire un valore in una cella vuota, ove il valore sia possibile.
 Se non sorgono incongruenze 
   se esitono altre caselle vuote, chiama ricorsivamente se stessa 
   se sono finite le caselle vuote, trovata una soluzione.
 Se non è stata trovata una soluzione, prova con un altro valore nella stessa 
 cella. Al termine dei valori possibili, senza successo, restituisce 0: 
 ( è inutile ricominciare con un'altra cella ! )

 OUTPUT: 1 soluzione trovata e copiata sulla Tavola da gioco
         0 nessuna soluzione
-----------------------------------------------------------------------------*/
int CercaSudoku
( int Tav[][9][10], 
  int Nvuote           // Numero di caselle vuote nella tavola 
)
{ int r, c,            // riga e colonna della cella da occupare 
      N,               // valore da inserire 
      Tav2 [9][9][10], // Tavola di appoggio 
      Nv2,             // numero delle caselle vuote da riempire 
      i, j,
      Trovato;         // 0 nessuna soluzione possibile; 
                       // 1 soluzione trovata e copiata su Tav 

  for (i=9; i; )       // cerca una cella vuota, che CERTAMENTE ESISTE
    for (i--, j=9; j; ) 
      if ( ! Tav[i][--j][0] ) r=i, c=j;

  for (N=9, Trovato=0; N && !Trovato; N--)
  if ( Tav[r][c][N] )  // se è possibile inserire il valore N 
  { 
    CopiaTavola (Tav, Tav2);
    Nv2 = Nvuote;
    ScriviCella(Tav2, r, c, N, &Nv2); 
    while ( CercaCertezze(Tav2, &Nv2) );

    if ( Congruenza(Tav2) )
    { Trovato = Nv2 ? CercaSudoku (Tav2, Nv2) : 1;
      if (Trovato) CopiaTavola (Tav2, Tav); //copia la soluzione
    } 
  }
  return Trovato;
}

/*=============================================================================
 Cerca i valori CERTI da inserire sulla tavola di gioco, esaminando le Flag 
 "possibilità" delle celle: 
 -) se una cella vuota possiede una sola flag==1, inseriamo quel valore;
 -) per ogni riga, colonna e gruppo, se un valore è disponibile in una sola 
 posizione vuota, inseriamo il valore.

 OUTPUT: quantità dei valori inseriti
------------------------------------------------------------------------------*/
int CercaCertezze
( int Tav[][9][10],
  int *Nvuote 
)
{ int i, j, k, 
      r, c,       // riga e colonna della cella da occupare 
      rg, cg,     // angolo in alto a sinistra del gruppo di appartenenza 
      N,          // valore da inserire 
      Flag,       // numero di Flag alte per ciascuna cella. 
      Tot;        // Totale dei numeri inseriti nella sessione 

  Tot = 0;
  for (i=0; i<9; i++) // ricerca ed analisi delle celle vuote 
    for (j=0; j<9; j++) 
      if (! Tav [i][j][0]) // se Cella vuota
      { for (Flag=0, k=9; k; k--) 
          if (Tav[i][j][k]) Flag++, N=k; // conta Flag possibilità
        if (Flag == 1) 
          ScriviCella(Tav, i, j, N, Nvuote), Tot ++; // se unico possibile
      }
  for (N=9; N; N--) // Ricerca per ogni valore da inserire
  { 
    for (i=0; i<9; i++) // esamina ciascuna riga della tavola 
    { for (Flag= j= 0; j<9; j++) 
        if (Tav[i][j][N]) Flag++, c=j; // conta Flag possibilità
      if (Flag==1 && !Tav[i][c][0])    // se unico possibile e cella vuota
        ScriviCella(Tav, i, c, N, Nvuote), Tot ++; 
    }
    for (j=0; j<9; j++) // esamina ciascuna colonna della tavola 
    { for (Flag= i= 0; i<9; i++) 
        if (Tav[i][j][N]) Flag++, r=i; // conta Flag possibilità
      if (Flag==1 && !Tav[r][j][0])    // se unico possibile e cella vuota
        ScriviCella(Tav, r, j, N, Nvuote), Tot ++; 
    }
    for (rg=0; rg<9; rg+=3) // esamina ciascun riquadro della tavola 
      for (cg=0; cg<9; cg+=3) 
      { for (Flag= i= 0; i<3; i++) 
          for (j=0; j<3; j++) 
            if (Tav[rg+i][cg+j][N]) Flag++, r=rg+i, c=cg+j; // conta Flag
        if (Flag==1 && !Tav[r][c][0])  // se unico possibile e cella vuota
          ScriviCella(Tav, r, c, N, Nvuote), Tot ++; 
      }
  }
  return Tot;
}

/*=============================================================================
 Valuta la congruenza di uno schema di gioco: per ogni riga, ogni colonna e
 ogni riquadro ciascun valore da 1 a 9 deve essere o già presente o possibile
 in almeno una cella. 
 Poiché i valori inseriti conservano la flag di possibilità, è sufficiente
 esaminare le caselle delle flag possibilità.

 OUTPUT: 0 la tavola è inconguente e NON è possibile trovare una soluzione
         1 il gioco può proseguire alla ricerca di soluzioni.
-----------------------------------------------------------------------------*/
int Congruenza
( int Tav[][9][10]
)
{ int i, j,
      N,         // valore da inserire 
      Flag,      // numero di flag == 1 
      rg, cg,    // angolo in alto a sinistra del gruppo di appartenenza 
      Congrua;   // 0 = tavola inconguente

  Congrua = 1;
                               // ogni valore da inserire deve essere o già
  for (N=9; N && Congrua; N--) // presente o possibile in almeno una cella
  {
    for (i=0; i<9; i++)        // esamina ciascuna riga della tavola 
    { for (Flag= j= 0; j<9; Flag += Tav[i][j++][N]); // conta le flag alte
      if (! Flag) Congrua = 0;
    }
    for (j=0; j<9 && Congrua; j++) // esamina ciascuna colonna della tavola 
    { for (Flag= i= 0; i<9; Flag += Tav[i++][j][N]); // conta le flag alte
      if (! Flag) Congrua = 0;
    }
    for (rg=0; rg<9 && Congrua; rg+=3) // esamina ciascun riquadro 
      for (cg=0; cg<9 && Congrua; cg+=3)
      { for (Flag= i= 0; i<3; i++)
          for (j=0; j<3; Flag += Tav[rg+i][cg+j][N], j++);
        if (! Flag) Congrua = 0;
      }
  }
  return Congrua;
}

/*=============================================================================
 Duplica una tavola da gioco.
-----------------------------------------------------------------------------*/
void CopiaTavola
( int Source[][9][10], 
  int Destin[][9][10]  
)
{ int i, j, k; 

  for (i=9; i; )
    for (i--, j=9; j; ) 
      for (j--, k=10; k; k--, Destin[i][j][k] = Source[i][j][k]);
}

/*=============================================================================
 Inizializza la Tavola di gioco del Sudoku, svuotando le celle e 
 rendendo potenzialmente inseribili tutti i valori da 1 a 9.
-----------------------------------------------------------------------------*/
void InitTavola
( int Tav[][9][10],
  int *Nvuote         // Numero di caselle vuote nella tavola 
)
{ int i, j, k;
 
  for (*Nvuote = 81, i=0; i<9; i++) 
    for (j=0; j<9; j++) 
    { Tav [i][j][0] = 0;
      for (k=9; k; Tav [i][j][k--] = 1 );
    } 
}

/*=============================================================================
 Carica un gioco da risolvere (sodoku parziale) dal file Sudoku.txt
 Saranno esaminati solo i primi 9 records del file e, di questi, solo i 
 primi 9 caratteri: il resto del file può essere occupato da commenti.
 Tutti i caratteri diversi da 1,2,3,4,5,6,7,8 e 9, sono considerati Spazi.

 ...7..4..
 .3..9..2.
 4....5...
 ..8.....5
 .9..3..7.
 6.....3..
 ...4....1
 .7..2..9.
 ..5..8...

-----------------------------------------------------------------------------*/
void LeggiTavola
( int  Tav[][9][10], 
  int  *Nvuote
)
{ int  i, j;
  FILE *Pf;
  char Buf[200];

  Pf = fopen ("Sudoku.txt", "r");
  if (Pf)
  { for (*Nvuote=81, i=0; i<9; i++)
    { fscanf(Pf,"%s",Buf);
      for (j=0; j<9; j++) 
        if (Buf[j]>=49 && Buf[j]<=57) 
          ScriviCella (Tav, i, j, Buf[j]-48, Nvuote);
    } 
    fclose (Pf);
  } 
}

/*=============================================================================
 Inserisce un valore da 1 a 9 in una cella vuota.
 Tutte le celle della stessa riga, stessa colonna e stesso gruppo (riquardo)
 perdono la possibilità di ricevere quel valore.
-----------------------------------------------------------------------------*/
void ScriviCella
( int Tav[][9][10],  // Tavola di gioco
  int r,             // riga dell'inserimento
  int c,             // colonna dell'inserimento
  int n,             // numero da inserire: 1 <= n <= 9
  int *Nvuote        // Numero di caselle vuote nella tavola 
)
{ int i, j, k,
      rg, cg;        // angolo in alto a sinistra del gruppo di appartenenza 

  (*Nvuote) --;
  Tav [r][c][0] = n;                 // inserisce il numero
  for (k=9; k; Tav [r][c][k--] = 0); // ovviamente, esclude tutti gli altri

  for (j=9; j; Tav [r][--j][n] = 0); // elimina flag dalle celle della riga
  for (i=9; i; Tav [--i][c][n] = 0); // elimina flag dalle celle della colonna

  rg = (r / 3) * 3;                  // angolo in alto a sinistra del gruppo 
  cg = (c / 3) * 3;
  for (i=0; i<3; i++)                // elimina flag dalle celle del gruppo
    for (j=0; j<3; j++) 
      Tav [rg+i][cg+j][n] = 0;

  Tav [r][c][n] = 1;                 // conferma la flag sulla stessa cella 
}

/*=============================================================================
 Visualizza la matrice del campo di gioco.
-----------------------------------------------------------------------------*/
void StampaTavola
( int Tav[][9][10], 
  int Nvuote
)
{ int i, j;

  for (i=0; i<9; i++) 
  { if (i%3) printf ("\n +---+---+---H---+---+---H---+---+---+\n |");
    else printf ("\n *===========H===========H===========*\n |");
    for (j=0; j<9; j++) 
    { if (Tav [i][j][0]) printf (" %d ",Tav [i][j][0]);
      else               printf (" "); 
      if (j==2 || j==5)  printf ("H"); 
      else               printf ("|"); 
    } 
  }
  printf ("\n *===========H===========H===========* Vuote = %d\n", Nvuote);
}
