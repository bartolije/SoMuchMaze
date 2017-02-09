#include "bots.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define KEY 12345

///	labyrinthe.c :
///		Librairie permettant la génération d'un labyrinthe, sa sauvegarde dans un segment de mémoire partagé
///

typedef struct _Pos{
	int x;
	int y;
}Pos;


int * getLabyrintheInfo(){
	int * labInfo = getTabSharedMemory(6, 1);
	return labInfo;
}

int * getLabyrinthe(int height, int width){
	int size = height * (width + (width - 1));
	int * adjmatlab = getTabSharedMemory(size, 0);
	return adjmatlab;
}

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

char getChar(int value){
	if(value == 0){
		return '+';
	}else if (value == 1){
		return ' ';
	}else{
		return '+';
	}	
}

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






