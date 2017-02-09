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
	int height, width;
	printf("\tQuelle hauteur pour votre labyrinthe ? ");
	scanf("%d", &height);
	printf("\tQuelle largeur pour votre labyrinthe ? ");
	scanf("%d", &width);
	 
	generateLabyrinthe(height, width, 0, 0, height-1, width-1);
	

	//printLabyrinthe2(labyrinthe, height, width);
	//freeTab2(labyrinthe, height, width);
	/*
	State state = INIT;


	//Boucle d'exécution du programme
	while(state != DONE){
		switch(state){
			case INIT:
				
				break;
			case RUNNING:

				break;
			case DONE:

				break;
		}
	}*/

	//printHeader();

    
    return 0;
}
