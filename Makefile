all: eagle2014

eagle2014: objects/main.o objects/menu.o objects/consoleutil.o
	gcc -Wall objects/main.o objects/menu.o objects/consoleutil.o -lg2 -o eagle2014

objects/main.o:
	gcc -c main.c -o objects/main.o

objects/menu.o:
	gcc -c code/menu.c -o objects/menu.o

objects/consoleutil.o:
	gcc -c code/consoleutil.c -o objects/consoleutil.o

clean:
	rm objects/*.o eagle2014
