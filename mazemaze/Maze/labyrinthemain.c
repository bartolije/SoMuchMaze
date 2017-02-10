#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinthe.h"


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
	printHeader();
	int height, width;
	printf("\tQuelle hauteur pour votre labyrinthe ? ");
	scanf("%d", &height);
	printf("\tQuelle largeur pour votre labyrinthe ? ");
	scanf("%d", &width);
	int xdep = -1;
	int ydep = -1;
	int xarr = -1;
	int yarr = -1;
	while(xdep < 0 || xdep > height - 1){
		printf("\tQuelle position en x pour le point de départ ? ");
		scanf("%d", &xdep);
	}
	while(ydep < 0 || ydep > width - 1){
		printf("\tQuelle position en y pour le point de départ ? ");
		scanf("%d", &ydep);
	}
	while(xarr < 0 || xarr > height - 1){
		printf("\tQuelle position en x pour le point d'arrivée ? ");
		scanf("%d", &xarr);
	}
	while(yarr < 0 || yarr > width - 1){
		printf("\tQuelle position en y pour le point d'arrivée ? ");
		scanf("%d", &yarr);
	}

	generateLabyrinthe(height, width, xdep, ydep, xarr, yarr);
	
	printf("\n\tLabyrinthe stocké dans la mémoire partagée... Entrer une touche pour quitter le programme ... ");

	
	scanf("%d", &xdep);

	int size = height * (width + (width - 1));

	detachSharedMemory(0, size);
	
	detachSharedMemory(1, 6);

    
    return 0;
}
