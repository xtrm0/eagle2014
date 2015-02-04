#!/bin/sh
gcc -O2 -Wall code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/button.c code/grafico.c code/surface.c code/gtimer.c code/game_engine.c  code/list.c code/surface_planner.c code/fuioutil.c -lg2 -lm -lrt -lX11 -o eagle2014
