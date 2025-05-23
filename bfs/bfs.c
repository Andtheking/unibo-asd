/****************************************************************************
 *
 * bfs.c -- Visita in ampiezza di grafi orientati
 *
 * Copyright (C) 2021--2025 Moreno Marzolla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/***
% LabASD - Visita in ampiezza (BFS)
% [Moreno Marzolla](https://www.unibo.it/sitoweb/moreno.marzolla)
% Ultimo aggiornamento: 2025-05-16

[![BFS Demo](bfs-demo.png "Demo visita BFS")](bfs-demo.html)

Realizziamo l'algoritmo di visita in ampiezza (_Breadth-First Search_,
BFS) di un grafo orientato $G=(V,E)$ con $n$ nodi e $m$
archi. L'algoritmo da implementare accetta un nodo sorgente $s$, e
deve visitare esclusivamente i nodi raggiungibili da $s$.  La visita
in ampiezza inizia da un nodo sorgente $s$ e procede "per livelli":
prima si visitano tutti i nodi adiacenti a $s$, poi tutti i nodi
adiacenti a quelli adiacenti, e così via.  Cliccando sull'immagine in
cima alla pagina è possibile vedere l'algoritmo BFS in azione
([fonte](https://bl.ocks.org/mbostock/11337835)).

Al termine della visita, l'algoritmo riempie due array `p[]` e `d[]`,
entrambi di $n$ elementi, con le seguenti informazioni:

- `p[v]` è il predecessore del nodo $v$ durante la visita (il
   predecessore del nodo sorgente è $-1$; è possibile usare il simbolo
   `NODE_UNDEF` il cui valore è $-1$ per evitare di fare ricorso a
   "costanti magiche").

- `d[v]` è la distanza del nodo $v$ dalla sorgente, dove per distanza
  si intende il numero di archi attraversati. Per ogni nodo
  raggiungibile dalla sorgente, l'algoritmo BFS determina il minimo
  numero di archi che è necessario attraversare per raggiungerlo. Se
  un nodo $v$ non è raggiungibile dalla sorgente poniamo `d[v] = -1`.

L'algoritmo BFS richiede l'uso di una coda FIFO in cui inserire i nodi
da visitare. In una coda FIFO il primo elemento inserito è anche il
primo ad essere estratto. A tale scopo si può usare la struttura dati
`List` già vista in una [precedente esercitazione](list.html), che
supporta inserimento e cancellazione da entrambi gli estremi in tempo
$O(1)$. Una coda FIFO può quindi essere simulata inserendo sempre da
una estremità, e rimuovendo sempre dall'altra.

![Figura 1: Esempio di esecuzione dell'algoritmo BFS su un grafo non orientato non connesso](bfs.svg)

La Figura 1 mostra un esempio di esecuzione dell'algoritmo BFS su un
grafo non orientato (l'algoritmo può essere applicato in modo identico
su un grafo orientato). Supponendo che i vicini di ciascun nodo
vengano esplorati in ordine crescente di identificatore, una visita
BFS che usa il nodo 0 come sorgente produrrà l'albero di visita
mostrato dalle frecce in grigio. Le frecce puntano verso il
predecessore di ogni nodo, per cui la relazione padre-figlio deve
essere immaginata invertendo la direzione delle frecce. L'array `d[]`
delle distanze e `p[]` dei predecessori sarà quello mostrato in
figura.

Poiché il grafo non è connesso, al termine si avrà che i nodi 4 e 5
non sono stati visitati, per cui la loro distanza sarà posta
convenzionalmente a -1 come pure i predecessori.

Nel caso in cui l'ordine di esplorazione dei vicini sia diverso, si
potrebbe ottenere un albero diverso ma ugualmente corretto.  Le
distanze invece devono rimanere le stesse.

Per compilare:

        gcc -std=c90 -Wall -Wpedantic list.c graph.c bfs.c -o bfs

Per eseguire in ambiente Linux/MacOSX:

        ./bfs 0 graph100.in

Per eseguire in ambiente Windows:

        ./bfs 0 graph100.in

dove al posto di 0 si può indicare l'indice di qualunque altro nodo da
usare come sorgente.

## Suggerimenti

L'algoritmo BFS utilizza una coda FIFO per memorizzare la frontiera
del grafo che viene esplorato. È possibile usare la struttura dati
`List` vista [in un precedente esercizio](list.html), di cui viene
fornita la soluzione in fondo a questa pagina. La struttura `List`
supporta inserimenti e cancellazioni da entrambe le estremità in tempo
$O(1)$.

- Per definire e creare una coda $Q$ si può usare l'istruzione:

  `List *Q = list_create();`

- Dato un intero $u$ che rappresenta l'id di un nodo, per inserire $u$
  nella coda si può usare l'istruzione:

  `list_add_first(Q, u);`

- Per estrarre un intero $v$ dall'altra estremità della lista,
  simulando quindi una coda FIFO, si può usare l'istruzione:

  `v = list_remove_last(Q);`

- Infine, per controllare se la coda è vuota, si può usare la funzione
  `list_is_empty(Q)`.

Un'altra operazione utilizzata dall'algoritmo BFS è l'iterazione su
tutti i nodi $v$ adiacenti ad un nodo dato $u$; questo serve per
esplorare i vicini di un nodo $u$. Per realizzarla, si può utilizzare
lo schema seguente:

```C
Edge *edge;

for (edge = graph_adj(g, u); edge != NULL; edge = edge-next) {
    const int v = edge->dst;
    \/\* eccetera \*\/
}
```

La funzione `graph_adj(g, u)` ritorna un puntatore al primo nodo della
lista di adiacenza di $u$; la lista di adiacenza consiste nell'elenco
degli archi che hanno $u$ come sorgente. Il nodo di destinazione è
l'attributo `dst` della struttura `Edge`. Si faccia riferimento al
file [graph.h](graph.h) per i dettagli.

## Curiosità

La visita in ampiezza può essere applicata all'analisi del grafo delle
mosse di un gioco da tavolo, per determinare il numero minimo di mosse
necessarie a vincere o se esiste una strategia vincente.  Un
risultato interessante è stato ottenuto nel 2007 quando un gruppo di
ricercatori ha [completato l'analisi del gioco della
dama](https://www.researchgate.net/publication/231216842_Checkers_Is_Solved),
che ha circa $5 \times 10^{20}$ configurazioni valide (che
corrispondono a nodi del grafo). È stato così dimostrato che, se
entrambi i giocatori giocano in modo "perfetto", il risultato è un
pareggio.  _"The Atlantic"_ ha un [articolo non
tecnico](https://www.theatlantic.com/technology/archive/2017/07/marion-tinsley-checkers/534111/) ([copia su Archive.org](https://web.archive.org/web/20240315184807/https://www.theatlantic.com/technology/archive/2017/07/marion-tinsley-checkers/534111/))
che discute questo risultato.

Usando la visita in ampiezza dell'albero delle mosse, è possibile
rispondere alle questioni sull'esercizio [shooting
stars](shooting-stars.html) che sono rimaste in sospeso: qual è il
minimo numero di mosse necessarie per vincere? qual è il minimo numero
di mosse necessarie per perdere? esistono configurazioni della griglia
di gioco che non possono essere ottenute da quella iniziale?

## File

- [bfs.c](bfs.c)
- [graph.c](graph.c)
- [graph.h](graph.h)
- [list.c](../solutions/list.c)
- [list.h](../solutions/list.h)
- [graph10.in](graph10.in). Risultato della visita in ampiezza usando [il nodo 0 come sorgente](graph10-bfs-0.out) oppure [il nodo 5 come sorgente](graph10-bfs-5.out). I cammini potrebbero risultare diversi in base all'ordine con cui si esplorano i vicini, ma le distanze devono essere le stesse.
- [graph100.in](graph100.in)
- [graph1000.in](graph1000.in)

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "graph.h"
#include "list.h"

/* Si può usare il simbolo NODE_UNDEF per indicare che il predecessore
   della lista dei padri non esiste. */
const int NODE_UNDEF = -1;

typedef enum { WHITE, GREY, BLACK } Color; /* colori dei nodi */

/* Visita il grafo `g` usando l'algoritmo di visita in ampiezza (BFS)
   usando `s` come nodo sorgente. Restituisce il numero di nodi
   raggiungibili da `s`, incluso `s`. */
int bfs( const Graph *g,
         int s,  /* Indice del nodo sorgente */
         int *d, /* Al termine dell'esecuzione, `d[i]` è la distanza
                    del nodo `i` dalla sorgente `s`, dove la distanza
                    è intesa come minimo numero di archi che collegano
                    la sorgente al nodo `i`. Se un nodo `i` non è
                    raggiungibile da `s`, si deve porre `d[i] =
                    -1`. Questo array deve essere allocato dal
                    chiamante e contenere `n` elementi (uno per ogni
                    nodo del grafo). */
         int *p  /* Al termine dell'esecuzione, `p[i]` è il
                    predecessore del nodo `i` lungo il cammino da `s`
                    a `i`. Nel caso in cui `i` non sia raggiungibile
                    dalla sorgente, `p[i] = -1`. Anche questo array
                    deve essere allocato dal chiamante e avere
                    lunghezza `n`. */
         )
{

    


    /* TODO */
    return 0;
}

/* Stampa il cammino che da `s` a `d` prodotto dalla visita in
   ampiezza; se `d` non è raggiungibile da `s`, stampa "Non
   raggiungibile". La stampa del cammino deve avere la forma:

   s->n1->n2->...->d

   dove n1, n2... sono gli identificatori (indici) dei nodi
   attraversati. */
void print_path(int s, int d, const int *p)
{
    if (s == d)
        printf("%d", s);
    else if (p[d] < 0)
        printf("Non raggiungibile");
    else {
        print_path(s, p[d], p);
        printf("->%d", d);
    }
}

/* Stampa le distanze dal nodo `src` di tutti gli altri nodi, e i
   cammini per raggiungerli. I cammini sono quelli prodotti dalla
   visita in ampiezza. L'array `p[]` indica l'array dei predecessori,
   cioè `p[i]` è il predecessore del nodo `i` nell'albero
   corrispondente alla visita BFS. Se un nodo non è raggiungibile da
   `src`, la sua distanza viene riportata come "-1" e il cammino viene
   sostituito dalla stringa "Non raggiungibile". */
void print_bfs( const Graph *g, int src, const int *d, const int *p )
{
    const int n = graph_n_nodes(g);
    int v;

    assert(p != NULL);
    assert(d != NULL);

    printf("  src | dest | distanza | path\n");
    printf("------+------+----------+-------------------------\n");
    for (v=0; v<n; v++) {
        printf(" %4d | %4d | %8d | ", src, v, d[v]);
        print_path(src, v, p);
        printf("\n");
    }
}

int main( int argc, char *argv[] )
{
    Graph *G;
    int nvisited; /* n. di nodi raggiungibili dalla sorgente */
    int *p, *d;
    FILE *filein = stdin;
    int src = 0, n;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s nodo_sorgente file_grafo\n", argv[0]);
        return EXIT_FAILURE;
    }

    src = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[2]);
            return EXIT_FAILURE;
        }
    }

    G = graph_read_from_file(filein);
    n = graph_n_nodes(G);
    assert((src >= 0) && (src < n));
    p = (int*)malloc( n * sizeof(*p) ); assert(p != NULL);
    d = (int*)malloc( n * sizeof(*d) ); assert(d != NULL);
    nvisited = bfs(G, src, d, p);
    print_bfs(G, src, d, p);
    printf("# %d nodi su %d raggiungibili dalla sorgente %d\n", nvisited, n, src);
    graph_destroy(G);
    free(p);
    free(d);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
