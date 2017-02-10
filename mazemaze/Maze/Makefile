
all : labyrinthe.sh bots.sh

1: labyrinthe.sh

2: bots.sh

labyrinthe.sh : labyrinthemain.o labyrinthe.o
	gcc -o $@ labyrinthemain.o labyrinthe.o

labyrinthemain.o : labyrinthemain.c labyrinthe.h
	gcc -o $@ -c labyrinthemain.c 

labyrinthe.o : labyrinthe.c
	gcc -o $@ -c labyrinthe.c

bots.sh : botsmain.o bots.o
	gcc -o $@ botsmain.o bots.o

botsmain.o : botsmain.c bots.h
	gcc -o $@ -c botsmain.c 

bots.o : bots.c
	gcc -o $@ -c bots.c

clean : 
	rm -f *.o core

mrproper :
	rm -f *.sh core
