#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

/*
    Representa uma nave espacial
*/
typedef struct spaceship {
  double x, y;
  double vx, vy;
  double fx, fy;
  //adicionar aqui um ponteiro para uma imagem?
};



/*
  Aloca memoria para a spaceship e cria-a
*/
void spc_init(spaceship * s);

/*
  Desaloca a memoria da spaceship
*/
void spc_destroy(spaceship * s);


/*
  Atualiza a posicao da nave, apos terem passado dt segundos
*/
void spc_update_pos(spaceship * s, double dt); //TODO: adicionar uma estrutura aos argumentos para verificar colisoes com os vertices no movimento

/*
  Desenha a nave no ecra id;
*/
void spc_draw(spaceship * s, int id);






#endif
