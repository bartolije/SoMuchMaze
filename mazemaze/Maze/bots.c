#include "bots.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define DEBUG 0

int moves;

///	bots.c :
///		Librairie permettant la résolution d'un labyrinthe stocké dans la mémoire partagée
///

typedef struct _Pos{
	int x;
	int y;
}Pos;

//Récupère les informations du labyrinthe sous forme de tableau à 1 dimension (index 0 = height, 1 = width, 2 = x depart, 3 = y depart, 4 = x arrivee, 5 = y arrivee) dans la mémoire partagée
int * getLabyrintheInfo(){
	//Récupére le tableau ayant l'id 1 dans la mémoire partagée
	int * labInfo = getTabSharedMemory(6, 1);
	return labInfo;
}

//Récupère la matrice d'adjacence dans la mémoire partagée sous forme de tableau à 1 dimension (2 dimensions impossible en mémoire partagée)
int * getLabyrinthe(int height, int width){
	int size = height * (width + (width - 1));
	int * adjmatlab = getTabSharedMemory(size, 0);
	return adjmatlab;
}

//Affiche le labyrinthe dans la console
void printLabyrinthe(int ** labyrinthe, int height, int width){
	printf("\t\tLog : Starting printing labyrinthe...\n");
	printf("\t+");
	for(int k = 0; k < width; k++){
		printf("++");
	}
	printf("\n");
	for(int i = 0; i < height; i++){
		printf("\t+");
		for (int j = 1; j < (width * 2) - 2; j=j+2){
			printf(" %c", getChar(labyrinthe[i][j]));
			
		}
		if(i != height -1){
			printf(" +\n\t+");
			for (int k = 0; k < (width * 2) - 1; k=k+2){
				printf("%c+", getChar(labyrinthe[i][k]));
			}
		}else{
			
			printf(" +");
		}	
		printf("\n");
	}
	printf("\t");
	for(int l = 0; l < width; l++){
		printf("++");
	}
	printf("+\n");
	printf("\t\tLog : Print succeeded.\n");
}

//Affiche le labyrinthe dans la console
void printLabyrinthe2(int * labyrinthe, int height, int width, int xdep, int ydep, int xarr, int yarr){
	if(DEBUG == 1)printf("\t\tLog : Starting printing labyrinthe...\n");
	printf("\t+");
	for(int k = 0; k < width; k++){
		printf("++");
	}
	printf("\n");
	for(int i = 0; i < height; i++){
		printf("\t+");
		for (int j = 1; j < (width * 2) - 2; j=j+2){	
			if(i == xdep && div(j, 2).quot == ydep){
				printf("D");
			}else if(i == xarr && div(j, 2).quot == yarr){
				printf("A");
			}else {
				printf(" ");
			}
			printf("%c", getChar(labyrinthe[i * (width*2 - 1) + j]));
			
		}
		if(i != height -1){
			printf(" +\n\t+");
			for (int k = 0; k < (width * 2) - 1; k=k+2){
				printf("%c+", getChar(labyrinthe[i * (width*2 - 1) + k]));
			}
		}else{
			if(i == xdep && width - 1 == ydep){
				printf("D");
			}else if(i == xarr && width - 1 == yarr){
				printf("A");
			}else {
				printf(" ");
			}
			printf("+");
		}	
		printf("\n");
	}
	printf("\t");
	for(int l = 0; l < width; l++){
		printf("++");
	}
	printf("+\n");
	if(DEBUG == 1)printf("\t\tLog : Print succeeded.\n");
}

//Récupère le caractère à afficher à l'écran en fonction de la valeur dans la matrice d'adacence
char getChar(int value){
	if(value == 0){
		return '+';
	}else if (value == 1){
		return ' ';
	}else{
		return '+';
	}	
}

//Récupère le tableau de taille size et d'identifiant unique id dan sla mémoire partagée
int * getTabSharedMemory(int size, int id){
	int shm;
	int * sharedmem;
	key_t key;

	key = ftok("./key", id);
	
	int size2 = sizeof(int) * size;

	shm = shmget(key, size2, 0666 | IPC_CREAT);
	if (shm == -1) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	sharedmem = shmat(shm, NULL, 0);

	return sharedmem;
	
}

//Bot de résolution aléatoire
void randResolveMaze(int * adjmat, int height, int width, int depx, int depy, int arrx, int arry){
	
	int currx = depx;
	int curry = depy;
	moves = 0;
	int ** cellshecango;
	int nbCells;
	int randNum;
	while(currx != arrx && curry != arry){
		cellshecango = getcellswherehecango(currx, curry, height, width, &nbCells, adjmat);
		randNum = div(rand(), nbCells).rem;
		currx = cellshecango[randNum][0];
		curry = cellshecango[randNum][1];
		moves++;
	}
	printf("Le bot de résolution aléatoire a trouvé un chemin en %d mouvements.\n", moves);
	
	
	return;
}

//Retourne 0 s'il y a un mur, 1 s'il y a un chemin (entre deux cases adjacentes)
int canGo(int xcelldep, int ycelldep, int xcellarr, int ycellarr){
	return 0;
}

int ** getcellswherehecango(int xcell, int ycell, int height, int width, int * nbcells, int * adjmat){
	if(DEBUG == 1) printf("\t\tLog : Looking for neighbours cells...\n");
	int ** adjcells = allocateTab2(4, 2);
	*nbcells = 0;
	if(DEBUG == 1) printf("\t\tLog : NbCells. %d\n", *nbcells);
	if(xcell > 0){
		if(adjmat[(xcell-1)*((width*2)-1) + (ycell * 2)] == 1){
			adjcells[*nbcells][0] = xcell - 1;
			adjcells[*nbcells][1] = ycell;
			*nbcells = *nbcells + 1;
			if(DEBUG == 1) printf("\t\tLog : Found a match. %d\n", *nbcells);
		}
	}
	if(ycell > 0){
		if(adjmat[xcell*((width*2)-1) + ((ycell * 2)-1)] == 1){
			adjcells[*nbcells][0] = xcell;
			adjcells[*nbcells][1] = ycell - 1;
			*nbcells = *nbcells + 1;
			if(DEBUG == 1) printf("\t\tLog : Found a match. %d\n", *nbcells);
		}
	}
	if(xcell < height - 1){
		if(adjmat[xcell*((width*2)-1) + (ycell * 2)] == 1){
			adjcells[*nbcells][0] = xcell + 1;
			adjcells[*nbcells][1] = ycell;
			*nbcells = *nbcells + 1;
			if(DEBUG == 1) printf("\t\tLog : Found a match. %d\n", *nbcells);

		}
	}if(ycell < width - 1){
		if(adjmat[xcell*((width*2)-1) + ((ycell * 2)+1)] == 1){
			adjcells[*nbcells][0] = xcell;
			adjcells[*nbcells][1] = ycell + 1;
			*nbcells = *nbcells + 1;
			if(DEBUG == 1) printf("\t\tLog : Found a match. %d\n", *nbcells);
		}
	}
	if(DEBUG == 1) printf("\t\tLog : Found %d matches.\n", *nbcells);
	return adjcells;
}


int ** allocateTab2(int height, int width){
	int ** labyrinthe;
	
	if(DEBUG == 1)printf("\t\tLog : Starting memory allocation...\n");
	
	//Allocation de la première dimension du tableau
	labyrinthe = malloc(height * sizeof(*labyrinthe));

	//Vérification que l'allocation a fonctionnée, quitte le programme en cas d'echec
	if(labyrinthe == NULL){
		if(DEBUG == 1)printf("\t\tLog : First allocation failed, exiting.\n");
		exit(EXIT_FAILURE);
	}
	
	//Allocation de la deuxième dimension du tableau, calloc permet d'initialiser les valeurs à 0
	for(int i = 0; i < height - 1; i++){
		labyrinthe[i] = calloc(width, sizeof(*(labyrinthe[i])));

		if(labyrinthe[i] == NULL){
			if(DEBUG == 1)printf("\t\tLog : Second allocation failed on %d iteration, exiting.\n", i);
			freeTab2(labyrinthe, height, width);
			exit(EXIT_FAILURE);
		}
	}

	if(DEBUG == 1)printf("\t\tLog : Allocation succeeded.\n");	
	
	return labyrinthe;
}

void freeTab2(int ** labyrinthe, int height, int width){

	if(DEBUG == 1)printf("\t\tLog : Starting memory clean...\n");

	for(int i = 0; i < height - 1; i++){
		free(labyrinthe[i]);
	}
	free(labyrinthe);
	labyrinthe = NULL;

	if(DEBUG == 1)printf("\t\tLog : Clean succeeded.\n");
}





