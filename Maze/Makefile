
all : labyrinthe.exe bots.exe

1: labyrinthe.exe

2: bots.exe

labyrinthe.exe : labyrinthemain.o labyrinthe.o
	gcc -o $@ labyrinthemain.o labyrinthe.o

labyrinthemain.o : labyrinthemain.c labyrinthe.h
	gcc -o $@ -c labyrinthemain.c 

labyrinthe.o : labyrinthe.c
	gcc -o $@ -c labyrinthe.c

bots.exe : botsmain.o bots.o
	gcc -o $@ botsmain.o bots.o

botsmain.o : botsmain.c bots.h
	gcc -o $@ -c botsmain.c 

bots.o : bots.c
	gcc -o $@ -c bots.c

clean : 
	rm -f *.o core

mrproper :
	rm -f bots.exe
