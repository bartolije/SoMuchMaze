
int * getLabyrintheInfo();

void printLabyrinthe(int ** labyrinthe, int height, int width);

void printLabyrinthe2(int * labyrinthe, int height, int width, int xdep, int ydep, int xarr, int yarr);

char getChar(int value);

int * getTabSharedMemory(int size, int id);

int * getLabyrinthe(int height, int width);

void randResolveMaze(int * adjmat, int height, int width, int depx, int depy, int arrx, int arry);

int canGo(int xcelldep, int ycelldep, int xcellarr, int ycellarr);

int ** allocateTab2(int height, int width);

void freeTab2(int ** labyrinthe, int height, int width);

int ** getcellswherehecango(int xcell, int ycell, int height, int width, int * nbcells, int * adjmat);

