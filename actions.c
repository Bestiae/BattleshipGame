#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <windows.h>

// Mriezka s rozmiestnenymi lodami je dodana v subore "deployment_grid.c".
extern int deployment_grid[GRID_SIZE][GRID_SIZE];

// Popis:
// Hracie pole (budeme ho nazyvat "attack_grid") obsahuje informacie o strelach hracov.
// Znacenie suradnic hracieho pola:
//		0		- na danu z suradnicu doposial ani jeden hracov nestrielal ("unknown")
//		1/-1	- hrac 1 strielal na danu suradnicu a trafil lod/vodu
//		2/-2	- hrac 2 strielal na danu suradnicu a trafil lod/vodu
int attack_grid[GRID_SIZE][GRID_SIZE] = {{0}};

// Funkcia na vykreslenie aktualnej situacie v hernom poli ("attack_grid").
// Pri vypise cisla v "attack_grid" nahradte vhodnymi symbolmi.
// Napriklad zasah do vody znazornite symbolom '~'.
char voda = 248, out = 126;

void drawAttackGrid() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0, j = 0, counter = 1;
	printf("\t\t    ");
    for(i=0; i < GRID_SIZE; i++){
        printf("%*d", 3, counter);
        counter++;
        }
    printf("\n\n");
    counter = 1;

	for(i = 0; i < GRID_SIZE; i++){
        printf("\t\t%*d: ", 2, counter);
        for(j = 0; j < GRID_SIZE; j++){
            if(attack_grid[i][j]==0){
                SetConsoleTextAttribute(hConsole, 9);
                printf("%*c", 3, voda);
                SetConsoleTextAttribute(hConsole, 7);
            }else if(attack_grid[i][j]== -1 || attack_grid[i][j]== -2){
                printf("%*c", 3, out);
            } else {
                SetConsoleTextAttribute(hConsole, 4);
                printf("%*d", 3, attack_grid[i][j]);
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
        counter++;
        printf("\n");
	}
}

// Funkcia, ktora zisti, ci doslo k zasahu lode na zadanych suradniciach (row,col) hracom s cislom playerID.
int checkHit(int row, int col, int playerID) {
    // Skontrolujte, ci niekto uz predtym nezasiahol dane policko:
	//		* ak ano, tak teraz nedoslo k zasahu (funkcia vrati 0)
	//		* ak nie, zaznacte aktualny pokus do "attack_grid" a vratte, ci doslo k zasahu (0/1)
    // TODO ...

    if(deployment_grid[row][col] == 1 && attack_grid[row][col] == 0){
	    if(playerID == 1){
                attack_grid[row][col] = 1;
            }else {attack_grid[row][col] = 2;}
        return 1;

	} else if(deployment_grid[row][col] == 0){ //&& attack_grid[row][col] == 0){
        if(playerID == 1){
                attack_grid[row][col] = -1;
            }else {attack_grid[row][col] = -2;}
        return 0;

	} else if((attack_grid[row][col] == -1 || attack_grid[row][col] == -2) || attack_grid[row][col] == 1 || attack_grid[row][col] == 2) {
        return -1;
	}

}

//Funkcia pre zmenu hraca, ktora vrati hraca
int swapPlayerID(int playerID){
    if(playerID == 1){
        playerID = 2;
    } else playerID =1;

    return playerID;
}

// funkcia ktora overi cisla ktore zadava pouzivatel

int overCijeCislo(){
    int cislo;
    while(scanf("%d", &cislo) != 1){
        printf("\t\t\tZadaj cislo a nie pismenko: ");
        scanf("%d", &cislo);
        getchar();
    }
    return cislo;
}

int Winner2[7][47] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,0,0,0,1,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0},
    {1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0},
    {1,1,0,0,1,1,0,1,0,1,0,0,0,1,1,0,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1},
};

int Winner1[7][47] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0},
    {1,0,0,0,0,1,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0},
    {1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
    {1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0},
    {1,1,0,0,1,1,0,1,0,1,0,0,0,1,1,0,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0},
};

void vypisWinner1(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    for(i = 0; i < 7; i++){
            printf("\t   ");
        for(j = 0; j < 47; j++){
            if(Winner1[i][j] == 0){
                printf(" ");
            } else if(Winner1[i][j] == 1){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("#");
                    SetConsoleTextAttribute(hConsole, 7);
            }
        }
        printf("\n");
    }
}

void vypisWinner2(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    for(i = 0; i < 7; i++){
            printf("\t   ");
        for(j = 0; j < 47; j++){
            if(Winner2[i][j] == 0){
                printf(" ");
            } else if(Winner2[i][j] == 1){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("#");
                    SetConsoleTextAttribute(hConsole, 7);
            }
        }
        printf("\n");
    }
}
