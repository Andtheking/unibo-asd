/****************************************************************************
 *
 * hashtable.h -- Interfaccia hash table
 *
 * Copyright (C) 2021, 2023, 2025 Nicolas Farabegoli, Moreno Marzolla
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
#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **items;
    int size;
    int values_count;
} HashTable;

/* Questa funzione mappa un intero k arbitrario in una posizione
   dell'array *items[] dell'hash table. */
unsigned long hash_function(const HashTable *h, unsigned long k);

/* Trasforma una sequenza di caratteri in un intero senza segno. */
unsigned long encode(const char *key);

/* Crea e restituisce una nuova tabella hash con `size` slot. */
HashTable *ht_create(int size);

/* Svuota la tabella hash, cancellando tutti i nodi in essa contenuta.
   Non deve deallocare `h`, ma solo eliminare i nodi che contiene. */
void ht_clear(HashTable *h);

/* Libera tutta la memoria occupata dalla tabella hash, inclusa la
   struttura puntata da `h`. Dopo aver chiamato questa funzione, il
   puntatore `h` non deve essere dereferenziato perché la memoria
   puntata è stata liberata. */
void ht_destroy(HashTable *h);

/* Inserisce la coppia (key, value) nella tabella hash. Se la chiave è
   già presente, sostituisce il valore nel vecchio nodo con
   `value`. Se la chiave non è presente, deve essere creato un nuovo
   nodo; in tal caso, la funzione deve creare una copia di `key`, e
   salvarne il contenuto nella chiave nel nodo. Restituisce 1 se viene
   creato un nuovo nodo, 0 se viene aggiornato un nodo esistente. */
int ht_insert(HashTable *h, const char *key, int value);

/* Ritorna un puntatore al nodo contenente le informazioni associate
   alla chiave `key`; se la chiave non è presente, ritorna NULL. */
HashNode *ht_search(HashTable *h, const char *key);

/* Rimuove il nodo contenente `key` e il valore associato dalla
   tabella hash, liberandone la memoria; se la chiave non è presente,
   non fa nulla. Ritorna 1 se la chiave era presente ed è stata
   cancellata, 0 altrimenti. */
int ht_delete(HashTable *h, const char *key);

/* Ritorna il numero di coppie (chiave, valore) presenti nella tabella
   hash. */
int ht_count(const HashTable *h);

/* Stampa il contenuto della tabella hash; questa funzione può essere
   utile in fase di debug. */
void ht_print(const HashTable *h);

#endif
