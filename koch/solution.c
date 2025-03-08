
#include "solution.h"
#include "lib/libpsgraph.h"

/* Disegna la curva di Koch di ordine `n` e lunghezza `x`. */
void koch(double x, int n)
{
    if (n == 0)
    {
        draw(x);
        return;
    }

    koch(x/3, n-1);
    turn(-45);
    koch(x/3, n-1);
    turn(90);
    koch(x/3, n-1);
    turn(-45);
    koch(x/3, n-1);
    

}

void fiocco_di_loch(double x, int n)
{

    koch(x,n);

    turn(30+90);
    koch(x,n);

    turn(30+90);
    koch(x,n);
}