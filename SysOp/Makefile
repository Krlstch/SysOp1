EXECUTABLE=output

output: lib1.o main.o
	gcc -Wall main.o lib1.o -o output

main.o: lib1.o main.c
	gcc -Wall -c main.c

lib1.o: lib1.c lib1.h
	gcc -Wall -c lib1.c

clean:
	rm *.o output
