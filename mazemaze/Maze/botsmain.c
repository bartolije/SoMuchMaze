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

	int * adjmatlab = getLabyrinthe(tabInfo[0], tabInfo[1]);
	printLabyrinthe2(adjmatlab, tabInfo[0], tabInfo[1]);

    
    return 0;
}
