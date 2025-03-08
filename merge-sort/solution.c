#include "solution.h"

/* Andrea Maria Castronovo */


/* Fonde i sottovettori ordinati `v[p..q]` e `v[q+1..r]`. Usa
   `buffer[]` come array temporaneo. `buffer[]` ha la stessa lunghezza
   dell'intero array `v[]`. */
void merge(int *v, int p, int q, int r, int *buffer)
{
    /* Dichiarazioni tutte all'inizio per evitare WARNING */
    int iSx = p;
    int iDx = q + 1;
    int iBuffer = p;
    int i = p;

    while (iBuffer <= r)
    {
        /* Se l'indice destro è andato oltre la lunghezza del sotto-array */
        /* Oppure l'elemento dell'array a sinistra è minore dell'elemento a destra */
        /* E l'indice di sinistra è sotto la metà, quindi non sfora il sotto-array di sinistra */
        if ((iDx > r || v[iSx] < v[iDx]) && iSx <= q)
        {
            buffer[iBuffer++] = v[iSx++];
        }
        else
        {
            buffer[iBuffer++] = v[iDx++];
        }
    }

    /* Copio l'array temporaneo in quello effettivo */
    for (i = p; i <= r; i++)
    {
        v[i] = buffer[i];
    }
}

/* Ordina il sottovettore buffer[p..r] (estremi inclusi) usando
   l'algoritmo Merge-Sort ricorsivo. L'array `buffer` ha lunghezzza n
   (pari all'intera lunghezza di `v[]`) ed è allocato dal chiamante;
   può essere utilizzato come buffer temporaneo per le operazioni
   `merge()`, senza necessità di allocare un nuovo buffer ad ogni
   chiamata. */
void merge_sort(int *v, int p, int r, int *buffer)
{
    int half = (p + r) / 2;

    if (p >= r)
        return; /* Vettore lungo 1 già ordinato */

    merge_sort(v, p, half, buffer);
    merge_sort(v, half + 1, r, buffer);

    merge(v, p, half, r, buffer);
}