eagle2014
=========

A 2d lunar landing simulator made for our programming class.

=========
Projeto realizado por:

Numero:_________80816; Nome:Diogo_Gonçalves; Mestrado:_MEAer;

Numero:_________81861; Nome:__Afonso_Tinoco; Mestrado:_MEAer;

Como compilar o programa:
É possível compilar o programa de duas formas, consoante as configurações da máquina de teste:
+ Forma recomendada - usando o utilitário make:
```
  make clean
  make all
```

+ Forma tradicional - usando apenas o gcc:
```
  gcc -O2 -Wall -pedantic -ansi code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/cockpit.c code/button.c code/grafico.c code/surface.c -lg2 -lm -o eagle2014
```
