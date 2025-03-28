/****************************************************************************
 *
 * list.c -- Liste doppiamente concatenate con sentinella
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
% LabASD - Liste doppiamente concatenate con sentinella
% [Moreno Marzolla](https://www.unibo.it/sitoweb/moreno.marzolla)
% Ultimo aggiornamento: 2025-03-25

(Crediti: prof. [Violetta Lonati](http://lonati.di.unimi.it/),
Università di Milano)

![Fonte: <https://www.youtube.com/watch?v=UqmnUe4pDdU>](treno.jpg)

Implementare la struttura dati "lista doppiamente concatenata con
sentinella", la cui interfaccia è specificata nel file
[list.h](list.h). Nel file [list.c](list.c) allegato sono già presenti
alcune funzioni; si chiede di completare quelle con il commento
`TODO`.

In una lista doppiamente concatenata, ogni nodo (che ha tipo
`ListNode`) contiene un attributo `val` di tipo `ListInfo` (che qui è
un intero), e due puntatori `succ` e `pred` al nodo successivo e
precedente, rispettivamente.

```C
typedef int ListInfo;

typedef struct ListNode {
    ListInfo val;
    struct ListNode *succ, *pred;
} ListNode;
```

La struttura `List` contiene un attributo `length` che indica la
lunghezza della lista (escluso il nodo sentinella), e un puntatore
`sentinel` al nodo sentinella.

```C
typedef struct {
    int length;
    ListNode *sentinel;
} List;
```

In questo tipo di lista è infatti presente un nodo speciale, detto
"sentinella", che non contiene alcuna informazione utile ma serve solo
per marcare l'inizio (o la fine) della lista; di fatto la presenza
della sentinella trasforma la lista in un anello. La sentinella
consente di accedere in tempo $O(1)$ al primo e ultimo nodo della
lista: il primo è il successore della sentinella, mentre l'ultimo è il
predecessore (Figura 1).

![Figura 1: Lista doppiamente concatenata con sentinella](list.svg)

Nel caso di lista vuota, è comunque presente il nodo sentinella, il
cui successore e predecessore è se stesso (Figura 2).

![Figura 2: Lista vuota con sentinella](empty-list.svg)

Oltre a consentire accesso in tempo costante agli estremi della lista,
la sentinella semplifica le operazioni di inserimento e cancellazione,
perché garantisce che ogni nodo abbia sempre un predecessore e un
successore. Non occorre quindi gestire in modo speciale la lista
vuota o le operazioni che coinvolgono il primo o l'ultimo elemento.

Nel file [list.h](list.h) vengono descritte le funzioni
dell'interfaccia del tipo `List`. L'unico punto di attenzione è
l'iterazione. Come esempio consideriamo la funzione `list_print(L)`
che stampa il contenuto di `L`. La funzione si può realizzare mediante
un ciclo `while`

```C
void list_print(List *L)
{
    ListNode *node = list_first(L);
    while (node != list_end(L)) {
        printf("%d ", node->val);
        node = list_succ(node);
    }
    printf("\n");
}
```

oppure `for`

```C
void list_print(List *L)
{
    ListNode *node;
    for (node = list_first(L); node != list_end(L); node = list_succ(node)) {
        printf("%d ", node->val);
    }
    printf("\n");
}
```

`list_first(L)` restituisce un puntatore al primo nodo di _L_, oppure
alla sentinella se la lista è vuota; `list_succ(node)` restituisce un
puntatore al successore di `node`, mentre `list_end()` restituisce un
puntatore alla sentinella. Questa interfaccia è conforme a strutture
dati analoghe di linguaggi come Java o C++;

Il file [list-main.c](list-main.c) contiene un programma, già completo
e funzionante, che esegue una sequenza di comandi da un file il cui
nome va specificato sulla riga di comando. L'elenco dei comandi con il
relativo significato è riportato nella Tabella 1.

: Tabella 1: Comandi nel file di input

-------------------------------------------------------------------------
Operazione    Significato
------------  -----------------------------------------------------------
`+` _k_       Inserisci un nuovo nodo contenente _k_ in testa alla lista.
              Sono ammessi valori duplicati.

`-` _k_       Cancella il primo nodo contenente _k_, se presente;
              altrimenti, non fa nulla.

`?` _k_       Cerca il valore _k_ nella lista, e stampa un opportuno
              messaggio per indicarne o meno la presenza.

`n` _idx_     Stampa il valore contenuto nel nodo in posizione _idx_;
              il primo nodo ha posizione _idx_ = 0,
              il secondo ha posizione _idx_ = 1, e così via.
              Se _idx_ è maggiore o uguale al numero di elementi
              della lista, stampa un opportuno messaggio.

`l`           Stampa la lunghezza della lista.

`p`           Stampa tutto il contenuto della lista.

`c`           Svuota la lista, cancellando tutti i nodi in essa
              contenuti.
-------------------------------------------------------------------------

È possibile inserire più volte lo stesso valore; in caso di
cancellazione di un valore ripetuto, è sufficiente cancellarne una
occorrenza qualsiasi.

Per compilare:

        gcc -std=c90 -Wall -Wpedantic list.c list-main.c -o list-main

Per eseguire in ambiente Linux/MaxOSX:

        ./list-main list.in

Per eseguire in ambiente Windows:

        .\list-main list.in

Come sempre, è possibile realizzare ulteriori funzioni di supporto.

## Suggerimento

Le funzioni `list_add_first()` e `list_add_last()` possono essere
realizzate sfruttando una funzione ausiliaria (da definire)

        static void list_insert_after(List *L, ListNode *n, ListInfo k)

che crea un nuovo nodo contenente il valore `k`, e lo inserisce
immediatamente dopo il nodo `n` della lista `L`. Il nodo `n` deve
essere già presente in `L`.

## File

- [list.c](list.c)
- [list.h](list.h)
- [list-main.c](list-main.c)
- [list.in](list.in) ([output atteso](list.out))
- [list1.in](list1.in)
- [list2.in](list2.in)
- [list3.in](list3.in)
- [list4.in](list4.in)

***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

/* Crea un nuovo nuovo oggetto nodo contenente valore `v`. I puntatori
   al successore e predecessore del nuovo nodo puntano a se stesso.
   Trattandosi di una funzione ad uso interno (non è elencata
   nell'interfaccia descritta nel file <list.h>), è dichiarata
   "static" in modo che non sia visibile esternamente a questo file
   sorgente. */
static ListNode *list_new_node(int v)
{
    ListNode *r = (ListNode *)malloc(sizeof(ListNode));
    assert(r != NULL); /* evitiamo un warning con VS */
    r->val = v;
    r->succ = r->pred = r;
    return r;
}

/* Restituisce l'indirizzo di memoria della sentinella di `L` */
ListNode *list_end(const List *L)
{
    assert(L != NULL);
    return L->sentinel;
}

List *list_create( void )
{
    List *L = (List*)malloc(sizeof(List));
    assert(L != NULL);

    L->length = 0;
    L->sentinel = list_new_node(0); /* il valore contenuto nel nodo sentinella è irrilevante */
    return L;
}

int list_length(const List *L)
{
    assert(L != NULL);

    return L->length;
}



void list_clear(List *L)
{
    /* TODO */
}

void list_destroy(List *L)
{
    list_clear(L);
    free(L->sentinel);
    free(L);
}

/* Nota: questa funzione assume che `ListInfo` sia il tipo "int" */
void list_print(const List *L)
{
    const ListNode *node;

    assert(L != NULL);

    printf("(");
    for (node = list_first(L); node != list_end(L); node = list_succ(node)) {
        printf("%d ", node->val);
    }
    printf(")\n");
}

int list_is_empty(const List *L)
{
    assert(L != NULL);

    return (list_first(L) == list_end(L));
}

ListNode *list_search(const List *L, ListInfo k)
{
    /* TODO */
    return NULL; /* Sostituire con il valore di ritorno corretto */
}

ListNode *list_first(const List *L)
{
    assert(L != NULL);

    return L->sentinel->succ;
}

ListNode *list_last(const List *L)
{
    assert(L != NULL);

    return L->sentinel->pred;
}


static void list_insert_after(List *L, ListNode *n, ListInfo k)
{
    /* Fatto dal prof in classe */

    ListNode *new_node, *succ_of_n;
    succ_of_n = n->succ;

    /* Creo il nodo */
    new_node = (ListNode*)malloc(sizeof(ListNode));
    assert(new_node != NULL);
    new_node->val = k;

    /* Ora devo sistmare i puntatori */
    new_node->pred = n;
    new_node->succ = succ_of_n;

    /* Andando avanti N deve farmi arrivare al nuovo nodo */    
    n->succ = new_node;

    /* Andando indietro il successivo del vecchio N deve farmi arrivare al nuovo nodo */
    succ_of_n->pred = new_node;

}

/* Inserisce un nuovo nodo contenente k all'inizio della lista */
void list_add_first(List *L, ListInfo k)
{
    assert(L != NULL);
    /* TODO */
}

/* Inserisce un nuovo nodo contenente k alla fine della lista */
void list_add_last(List *L, ListInfo k)
{
    assert(L != NULL);
    /* TODO */
}

/* Rimuove il nodo n dalla lista L */
void list_remove(List *L, ListNode *n)
{
    assert(L != NULL);
    assert(n != NULL);
    assert(n != list_end(L));
    /* TODO */
}

ListInfo list_remove_first(List *L)
{
    assert( !list_is_empty(L) );
    /* TODO */
    return -1; /* Sostituire con il valore di ritorno corretto */
}

ListInfo list_remove_last(List *L)
{
    assert( !list_is_empty(L) );
    /* TODO */
    return -1; /* Sostituire con il valore di ritorno corretto */
}

ListNode *list_succ(const ListNode *n)
{
    assert(n != NULL);

    return n->succ;
}

ListNode *list_pred(const ListNode *n)
{
    assert(n != NULL);

    return n->pred;
}

ListNode *list_nth_element(const List *L, int n)
{
    /* TODO */
    return NULL; /* Sostituire con il valore di ritorno corretto */
}

void list_concat(List *L1, List *L2)
{
    assert(L1 != NULL);
    assert(L2 != NULL);

    /* TODO */
}

int list_equal(const List *L1, const List *L2)
{
    assert(L1 != NULL);
    assert(L2 != NULL);

    /* TODO */
    return -1; /* Sostituire con il valore di ritorno corretto */
}
