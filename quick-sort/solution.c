#include "solution.h"
#include <string.h>

/* Andrea Maria Castronovo */

void swap(int *v, int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int partition(int *v, int p, int r)
{
    int pivot = v[r];
    int i = p;
    int j;

    for (j = p; j < r; j++)
    {
        if (v[j] <= pivot)
        {
            swap(v, i, j);  
            i++;
        }
    }
      
    swap(v,i,r);
    return i;
}


void quick_sort(int *v, int p, int r)
{
    int q;
    if (p >= r)
        return; /* Array lungo 1 */
    

    q = partition(v, p, r); /* Faccio la partizione con il pivot */

    quick_sort(v, p, q - 1);
    quick_sort(v, q + 1, r);
    
    
}