#TODO: Tirar o g para modo release
FLAGS=-c
LNFLAGS=-Wall
LNLIBS=-lg2 -lm
IDIR=include
ODIR=objects
CDIR=code
OBJECTS: main.o menu.o consoleutil.o spaceship.o view.o geometry.o

all: eagle2014

debug: 
	rm -f objects/*.o eagle2014
debug: FLAGS += -DDEBUG -g
debug: LNGLAGS += -DDEBUG -g
debug: eagle2014
	clear
	gdb ./eagle2014

eagle2014: $(OBJECTS)
	gcc $(LNFLAGS) $(OBJECTS) $(LNLIBS) -o eagle2014

$(ODIR)/%.o: $(CDIR)/%.c
	gcc $(FLAGS) $< -o $(ODIR)/$@ 

clean:
	rm objects/*.o eagle2014
