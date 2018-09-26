main: main.o	arquivo.o 	
	gcc main.o	arquivo.o	-lpthread	-o  exe
	rm *.o
main.o:	main.c
	gcc -c main.c
arquivo.o:	arquivo.h arquivo.c
	gcc -c arquivo.c