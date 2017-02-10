#include "bots.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>



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
void printLabyrinthe2(int * labyrinthe, int height, int width){
	printf("\t\tLog : Starting printing labyrinthe...\n");
	printf("\t+");
	for(int k = 0; k < width; k++){
		printf("++");
	}
	printf("\n");
	for(int i = 0; i < height; i++){
		printf("\t+");
		for (int j = 1; j < (width * 2) - 2; j=j+2){
			printf(" %c", getChar(labyrinthe[i*j]));
			
		}
		if(i != height -1){
			printf(" +\n\t+");
			for (int k = 0; k < (width * 2) - 1; k=k+2){
				printf("%c+", getChar(labyrinthe[i*k]));
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

void resolveMaze(int * adjmat, int height, int width, int depx, int depy, int arrx, int arry{
	return;
}

//Retourne 0 s'il y a un mur, 1 s'il y a un chemin (entre deux cases adjacentes)
int canGo(int xcelldep, int ycelldep, int xcellarr, int ycellarr){
	return 0;
}





