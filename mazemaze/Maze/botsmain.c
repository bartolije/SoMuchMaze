#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bots.h"

///
///	Programme permettant la génération du labyrinthe
///


///
///	Type représentant l'état du programme (EN COURS D'EXECUTION, INITIALISATION, FIN)
///
typedef enum State {RUNNING, INIT, END};

///
///	Imprime le header du programme dans la console
///
void printHeader(){
	printf("\t---------------------------------------------------------\n");
	printf("\t----------------WELCOME-TO-THE-LABYRINTHE----------------\n");
	printf("\t---------------------------------------------------------\n");
}

int main()
{	
	int * tabInfo = getLabyrintheInfo();
	printf("Height : %d\n", tabInfo[0]);
	printf("Width : %d\n", tabInfo[1]);
	printf("Position de départ en x : %d\n", tabInfo[2]);
	printf("Position de départ en y : %d\n", tabInfo[3]);
	printf("Position d'arrivée en x : %d\n", tabInfo[4]);
	printf("Position d'arrivée en y : %d\n", tabInfo[5]);

	int * adjmatlab = getLabyrinthe(tabInfo[0], tabInfo[1]);
	printLabyrinthe2(adjmatlab, tabInfo[0], tabInfo[1], tabInfo[2], tabInfo[3], tabInfo[4], tabInfo[5]);
	randResolveMaze(adjmatlab, tabInfo[0], tabInfo[1], tabInfo[2], tabInfo[3], tabInfo[4], tabInfo[5]);

    
    return 0;
}
