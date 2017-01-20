#include "main.h"

int main(void)
{
	char maze[MAZESIZE][MAZESIZE];
	int i, j;

	mazeGenerator(maze);
	printf("Enter to solve...\n");
	getchar();

	mazeTraverse(maze, 0, 0);

	for (i = 0; i < MAZESIZE; i++)
	{
		for (j = 0; j < MAZESIZE; j++)
			putchar(maze[i][j]);
		putchar('\n');
	}

	getchar();
	return 0;
}

void mazeGenerator(char maze[][MAZESIZE])
{
	int i, j;

	for (i = 0; i < MAZESIZE; i++)
	{
		for (j = 0; j < MAZESIZE; j++)
		{
			if (i % 2 == 1)
				maze[i][j] = WALL;
			else if (j % 2 == 1)
				maze[i][j] = WALL;
			else
				maze[i][j] = UNVISITED;
		}
	}

	maze[MAZESIZE - 1][MAZESIZE - 2] = ROAD;
	maze[MAZESIZE - 1][MAZESIZE - 1] = EXIT;  


	srand((unsigned)time(NULL)); 
	digWall(maze, 0, 0);

	maze[0][0] = ENTRANCE;


	for (i = 0; i < MAZESIZE; i++)
	{
		for (j = 0; j < MAZESIZE; j++)
			putchar(maze[i][j]);
		putchar('\n');
	}
}

void mazeTraverse(char maze[][MAZESIZE], int posx, int posy)
{
	int i = 0, j = 0;

	static int wasHere[MAZESIZE][MAZESIZE];
	if (posx == MAZESIZE - 1 && posy == MAZESIZE - 1)
	{
		maze[posx][posy] = GOODWAY;
		return;
	}
	if (maze[posx][posy] == WALL || wasHere[posx][posy])
		return;    
	wasHere[posx][posy] = 1;
	if (posx != 0) 
	{
		mazeTraverse(maze, posx - 1, posy); 
		if (maze[posx - 1][posy] == GOODWAY) 
		{
			maze[posx][posy] = GOODWAY;   
			return;
		}
	}
	if (posx != MAZESIZE - 1) 
	{
		mazeTraverse(maze, posx + 1, posy);  
		if (maze[posx + 1][posy] == GOODWAY)
		{
			maze[posx][posy] = GOODWAY;
			return;
		}
	}
	if (posy != 0) 
	{
		mazeTraverse(maze, posx, posy - 1);
		if (maze[posx][posy - 1] == GOODWAY)
		{
			maze[posx][posy] = GOODWAY;
			return;
		}
	}
	if (posy != MAZESIZE - 1) 
	{
		mazeTraverse(maze, posx, posy + 1);  
		if (maze[posx][posy + 1] == GOODWAY)
		{
			maze[posx][posy] = GOODWAY;
			return;
		}
	}

}

void digWall(char maze[][MAZESIZE], int posx, int posy)
{

	maze[posx][posy] = ROAD;
	int tried[4] = { 0,0,0,0 };

	if (posx == 0)   
		tried[0] = 1;  
	if (posx == MAZESIZE - 2)
		tried[1] = 1;
	if (posy == 0)    
		tried[2] = 1;
	if (posy == MAZESIZE - 2)
		tried[3] = 1;
	int direction; 
	while (tried[0] * tried[1] * tried[2] * tried[3] == 0)
	{
		direction = rand() % 4;       
		if (tried[direction] == 1) 
			continue;
		tried[direction] = 1;   
		switch (direction)   
		{
		case 0: UP;      
		case 1: DOWN;  
		case 2: LEFT; 
		case 3: RIGHT; 
		}
	}
}