all: compila

compila:	
	gcc -c lista.c
	gcc -c ura.c
	gcc -o ura ura.o lista.o 
	rm -rf *.o 
