FLAGS=-c -Wall
LNFLAGS=-Wall
LNLIBS=-lg2 -lm
CC = gcc -fdiagnostics-color=auto -pedantic -ansi
IDIR=include
ODIR=objects
CDIR=code
OBJECTS= main.o menu.o geometry.o spaceship.o view.o cockpit.o button.o grafico.o surface.o
OBJECTSPATH = $(patsubst %,$(ODIR)/%,$(OBJECTS))
.PHONY: all clean debug


all: eagle2014

drun: debug
	./eagle2014

run: release
	./eagle2014

release: clean
release: eagle2014

gdb: debug
	gdb ./eagle2014

debug: clean
debug: FLAGS += -D_DEBUG -g
debug: LNFLAGS += -D_DEBUG -g
debug: eagle2014

clean:
	rm -f objects/*.o eagle2014



eagle2014: $(OBJECTSPATH)
	$(CC) $(LNFLAGS) $(OBJECTSPATH) $(LNLIBS) -o eagle2014

$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) $< -o $@
