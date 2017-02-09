
all : labyrinthe.exe

labyrinthe.exe : labyrinthemain.o labyrinthe.o
	gcc -o $@ labyrinthemain.o labyrinthe.o

labyrinthemain.o : labyrinthemain.c labyrinthe.h
	gcc -o $@ -c labyrinthemain.c 

labyrinthe.o : labyrinthe.c
	gcc -o $@ -c labyrinthe.c

clean : 
	rm -f *.o core

mrproper :
	rm -f labyrinthe.exe
