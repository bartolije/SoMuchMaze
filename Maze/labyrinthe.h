

int * generateLabyrinthe(int height, int width, int xdep, int ydep, int xarr, int yarr);

int ** allocateTab2(int height, int width);

void freeTab2(int ** labyrinthe, int height, int width);

void printLabyrinthe(int ** labyrinthe, int height, int width);

void printLabyrinthe2(int * labyrinthe, int height, int width);

char getChar(int value);

int hasEveryCellsBeenVisited(int ** Cells, int height, int width);

int isValidCell(int indice1, int indice2, int height, int width);

void getNextCell(int * x, int * y, int direction);

int areAllAdjCellsBeenVisited(int ** visitedCells, int x, int y, int height, int width);

int * createTabSharedMemory(int size, int id);

void detachSharedMemory(int id, int size);
