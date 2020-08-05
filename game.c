#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <windows.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int row, col; //то буде так, що 3 ряд, 5 колонка;
	int playerID = 1;
	int shipsHit = 0, p1 = 0, p2 = 0;

	while(shipsHit < shipsTotal){//3
        CLEAR_SCREEN();

        SetConsoleTextAttribute(hConsole, 2);
        printf("\n\t\t\t\t\t\tHrac 1: %d\n", p1);
        printf("\tHra Namorna Bitka\t\t\tHrac 2: %d\n\n", p2);
        SetConsoleTextAttribute(hConsole, 7);

        drawAttackGrid();

        printf("\n\tHra hrac %d\n", playerID);

        while(1 == 1){
            printf("\t\t\tZadaj suradnicu row: ");
             row = overCijeCislo();
            if(row <= 10 && row >= 1){
                break;
            }
        }

        while(1 == 1){
            printf("\t\t\tZadaj suradnicu col: ");
            col = overCijeCislo();
            if(col <= 10 && col >= 1){
                break;
            }
        }

        row -= 1;
        col -= 1;

        printf("\n");

        if (checkHit(row, col, playerID) == 1){
            if(playerID == 1){
                p1++;
                printf("\tHrac %d trafil %d krat", playerID, p1);
            } else{
                p2++;
                printf("\tHrac %d trafil %d krat", playerID, p2);
            }
            shipsHit++;

        } else if(checkHit(row, col, playerID) == 0){
            printf("\tHrac %d zasiahol vodu", playerID);
            playerID = swapPlayerID(playerID);

        } else if(checkHit(row, col, playerID) == -1){
            printf("\tHrac %d zasiahol uz obsadenu poziciu.\n\tDavaj pozor na to co vyberas.", playerID);
            playerID = swapPlayerID(playerID);
        }
        getch();
	}
	CLEAR_SCREEN();

	SetConsoleTextAttribute(hConsole, 2);
    printf("\n\t\t\t\t\t\tHrac 1: %d\n", p1);
    printf("\tHra Namorna Bitka\t\t\tHrac 2: %d\n\n", p2);
    SetConsoleTextAttribute(hConsole, 7);

	if(p1 > p2){
        drawAttackGrid();
        vypisWinner1();
	} else {
        drawAttackGrid();
        vypisWinner2();
	}

	return 0;
}
