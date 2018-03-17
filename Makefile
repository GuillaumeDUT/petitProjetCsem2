lexique: main.o struct.o
	gcc -o lexique main.o struct.o

main.o: main.c struct.h
	gcc -c main.c -o main.o -Wall

struct.o: struct.c struct.h
	gcc -c struct.c -o struct.o -Wall

clean:
		rm -f *.o

deljeu:
	  rm -f lexique
