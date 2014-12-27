#!/bin/sh
gcc -O2 -Wall code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/cockpit.c code/button.c code/grafico.c code/surface.c code/gtimer.c -lg2 -lm -lrt -o eagle2014
