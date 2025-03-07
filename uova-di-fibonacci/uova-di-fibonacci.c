/* Andrea Maria Castronovo */

#include <stdio.h>

/*

Un grosso cesto contiene delle uova. Il numero di uova gode delle seguenti proprietà: 
se si contano le uova due a due, oppure tre a tre, oppure quattro a quattro, oppure cinque a cinque, oppure sei a sei
allora alla fine del conteggio ne resta una. 
Se invece si contano le uova sette a sette, alla fine del conteggio non ne rimane nessuna.

Scrivere un programma che calcoli e stampi il minimo valore intero 
che goda delle proprietà precedenti. 
(Suggerimento: realizzare un algoritmo che proceda per tentativi; si tenga presente che in questo problema semplice ).

*/

int main()
{
    int i;
    char trovato = 0;
    for (i = 1; !trovato; i++)
    {

        if (i % 2 == 1 && /* A due a due ne rimane 1 */ 
            i % 3 == 1 && /* A tre a tre ne rimane 1 */
            i % 4 == 1 && /* A quatro a quatro ne rimane 1 */
            i % 5 == 1 && /* A cinque a cinque ne rimane 1 */
            i % 6 == 1 && /* A sei a sei ne rimane 1 */
            i % 7 == 0    /* A sette a sette non ne restano */ 
        ) 
        {
            trovato = 1;
        }
    }

    printf("%d", i - 1);
    
    return 0;
}
