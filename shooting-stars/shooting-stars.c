#include <stdio.h>
#include <stdlib.h>

#define GRID_X 3
#define GRID_Y 3





int checkWin(char grid[GRID_X][GRID_Y])
{
    int i;
    for (i = 0; i < GRID_X*GRID_Y; i++)
    {
        if (((char*)grid)[i] == '.' && i != 4)
            return 0;
    }
    return 1;
}

int checkLoss(char grid[GRID_X][GRID_Y])
{
    int i;
    for (i = 0; i < GRID_X*GRID_Y; i++)
    {
        if (((char*)grid)[i] != '.')
            return 0;
    }
    return 1;
}

void changeCellState(char grid[GRID_X][GRID_Y], int x)
{
    if (((char*)grid)[x] == '.')
    {
        ((char*)grid)[x] = x + 48;
    }
    else 
    {
        ((char*)grid)[x] = '.';
    }
}


void explodeLogic(char grid[GRID_X][GRID_Y], int *change)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (change[i] != -1)
            changeCellState(grid, change[i]);
    }
    
}

void stampaCampoGioco(char grid[GRID_X][GRID_Y])
{
    int i;
    for (i = 0; i < GRID_X; i++)
    {
        int j;
        for (j = 0; j < GRID_Y; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    
}

int main()
{
    char campoGioco[3][3] = {
        {'.', '.', '.'}, 
        {'.', '*', '.'}, 
        {'.', '.', '.'}
    };

    int posizioni[9][5] = 
    {
        {0, 1, 3, 4},
        {0, 1, 2, -1, -1},
        {1, 2, 4, 5, -1},
        {0, 3, 6, -1, -1},
        {1, 3, 4, 5, 7},
        {2, 5, 8, -1, -1},
        {3, 4, 6, 7, -1},
        {6, 7, 8, -1, -1},
        {4, 5, 7, 8, -1}
    };

    
    int going = 1;

    while (going)
    {
        char input = fgetc(stdin);

        if (input < 48 || input > 56)
        {
            puts("Input non valido. Inserisci un numero da 0 a 8");
        }
        else
        {
            int scelta = input-48;
            explodeLogic(campoGioco, posizioni[scelta]);
        }

        stampaCampoGioco(campoGioco);

        
    }

    return 0;
}