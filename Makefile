all: eagle2014

eagle2014: objects/main.o objects/menu.o objects/consoleutil.o objects/spaceship.o objects/view.o objects/geometry.o
	gcc -Wall objects/main.o objects/menu.o objects/consoleutil.o objects/spaceship.o objects/view.o objects/geometry.o -lg2 -o eagle2014

objects/main.o:
	gcc -c main.c -o objects/main.o

objects/view.o:
	gcc -c code/view.c -o objects/view.o

objects/menu.o:
	gcc -c code/menu.c -o objects/menu.o

objects/geometry.o:
	gcc -c code/geometry.c -o objects/geometry.o

objects/consoleutil.o:
	gcc -c code/consoleutil.c -o objects/consoleutil.o

objects/spaceship.o:
	gcc -c code/spaceship.c -o objects/spaceship.o

clean:
	rm objects/*.o eagle2014
