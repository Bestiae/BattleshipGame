#ifndef HELPERS_H
#define HELPERS_H

// funkcia pre zmenu hraca
int swapPlayerID(int playerID);

// konstanta definujuca rozmer mriezky s lodami
#define GRID_SIZE 10

 // pomocna premenna reprezentujuca celkovy pocet policok v mriezke obsadenych lodami
extern int shipsTotal;

// funkcia na vykreslenie aktualneho stavu herneho pola
void drawAttackGrid();

// funkcia ktora overi cisla ktore zadava pouzivatel
int overCijeCislo();

// funkcia, ktora zaznamena strelu hraca do herneho pola a vrati, ci doslo k zasahu (0 - "miss", 1 - "hit")
int checkHit(int row, int col, int playerID);

// Podmieneny preklad: verzia pre WINDOWS sa lisi od LINUX verzie
// makro na vycistenie obsahu konzoly
#ifdef _WIN32
	#define CLEAR_SCREEN()	system("cls")
#else
	#define CLEAR_SCREEN()	printf("\x1b[2J");
#endif

// TODO: deklaracie vasich vlastnych funkcii resp. premennych

#endif /* HELPERS_H */
