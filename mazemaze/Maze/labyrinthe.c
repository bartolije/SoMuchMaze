#include "labyrinthe.h"
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

///	generateLabyrinthe : 
///		Génère un labyrinthe sous la forme d'un tableau à deux dimensions (pointeur sur tableau de pointeur) contenant des entiers
///'
int * generateLabyrinthe(int height, int width, int xdep, int ydep, int xarr, int yarr){
	
	printf("\t\tLog : Starting labyrinthe generation...\n");
	
	int * sharedtabadjmat;
	
	int * sharedtabinfo;	

	int size = height * (width + (width - 1));
	
	int shmid1 = 0;
	int shmid2 = 1;

	sharedtabadjmat = createTabSharedMemory(size, 0);
	sharedtabinfo = createTabSharedMemory(6, 1);
	sharedtabinfo[0] = height;
	sharedtabinfo[1] = width;
	sharedtabinfo[2] = xdep;
	sharedtabinfo[3] = ydep;
	sharedtabinfo[4] = xarr;
	sharedtabinfo[5] = yarr;
	

	int totalCells = height * width;
	int indexCell = 0;
	//Stocke les cases visitées, premiere case visitée : x = visitedcells[0][0], y = visitedcells[0][1]
	int * visitedCells = allocateTab2(totalCells, 2);

	int visitedcellscount = 1;
		
	


	printf("\t\tLog : Generation succeeded.\n");

	
	scanf("%d", &width);

	detachSharedMemory(0, size);
	
	detachSharedMemory(1, 6);

	return sharedtabadjmat;
}

///	allocateTab2 : 
///		Initialise le pointeur sur tableau de pointeur qui contiendra le labyrinthe
///
///		Paramètres :
///			int height : entier représentant la hauteur du labyrinthe
///			int width : entier représentant la largeur du labyrinthe
///		Retourne :
///			int ** : pointeur sur tableau de pointeur (tableau à deux dimensions) d'entiers
///
int ** allocateTab2(int height, int width){
	int ** labyrinthe;
	
	printf("\t\tLog : Starting memory allocation...\n");
	
	//Allocation de la première dimension du tableau
	labyrinthe = malloc(height * sizeof(*labyrinthe));

	//Vérification que l'allocation a fonctionnée, quitte le programme en cas d'echec
	if(labyrinthe == NULL){
		printf("\t\tLog : First allocation failed, exiting.\n");
		exit(EXIT_FAILURE);
	}
	
	//Allocation de la deuxième dimension du tableau, calloc permet d'initialiser les valeurs à 0
	for(int i = 0; i < height - 1; i++){
		labyrinthe[i] = calloc(width, sizeof(*(labyrinthe[i])));

		if(labyrinthe[i] == NULL){
			printf("\t\tLog : Second allocation failed on %d iteration, exiting.\n", i);
			freeTab2(labyrinthe, height, width);
			exit(EXIT_FAILURE);
		}
	}

	printf("\t\tLog : Allocation succeeded.\n");	
	
	return labyrinthe;
}

///	freeTab2 :
///		Libère la mémoire occupée par le tableau à deux dimensions
///
void freeTab2(int ** labyrinthe, int height, int width){

	printf("\t\tLog : Starting memory clean...\n");

	for(int i = 0; i < height - 1; i++){
		free(labyrinthe[i]);
	}
	free(labyrinthe);
	labyrinthe = NULL;

	printf("\t\tLog : Clean succeeded.\n");
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

int hasEveryCellsBeenVisited(int ** Cells, int height, int width){
	int result = 1;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(Cells[i][j] == 0){
				result = 0;
				break;
			}
		}
		if(result == 0){
			break;
		}
	}
	return result;
}

int isValidCell(int indice1, int indice2, int height, int width){
	int result = 1;
	if(!((indice1 >= 0) && (indice1 <= height - 1))){
		result = 0;
	}
	if(!((indice2 >= 0) && (indice2 <= width - 1))){
		result = 0;
	}
	return result;
}

void getNextCell(int * x, int * y, int direction){
	switch(direction){
		case 0:
			*x = *x-1;
			break;
		case 1:
			*y = *y-1;
			break;
		case 2:
			*x = *x+1;
			break;
		case 3:	
			*y = *y+1;
			break;
		default:
			return;
			break;
	}
}

int areAllAdjCellsBeenVisited(int ** visitedCells, int x, int y, int height, int width){
	if(x - 1 >= 0){
		if(visitedCells[x-1][y] == 0){
			return 0;
		}
	}
	if(x + 1 < height){
		if(visitedCells[x+1][y] == 0){
			return 0;
		}
	}
	if(y - 1 >= 0){
		if(visitedCells[x][y-1] == 0){
			return 0;
		}
	}
	if(y + 1 < height){
		if(visitedCells[x][y+1] == 0){
			return 0;
		}
	}
	return 1;
}

int * createTabSharedMemory(int size, int id){
	printf("\t\tLog:Creating shared memory segment...\n");
	int shm;
	int * sharedmem;
	key_t key;

	key = ftok("./key", id);	
	
	int sizemem = sizeof(int) * size;

	shm = shmget(key, sizemem, 0666 | IPC_CREAT);
	if (shm == -1) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	sharedmem = shmat(shm, NULL, 0);
	printf("\t\tLog:Creation succeeded.\n");

	return sharedmem;
	
}


void detachSharedMemory(int id, int size){
	key_t key = ftok("./key", id);
	id = shmget(key, size*sizeof(int), 0666 | IPC_CREAT);
	shmctl(id, IPC_RMID, NULL);
}





