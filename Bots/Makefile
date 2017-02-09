
all : bots.exe

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
