#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "geometry.h"
#include "view.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
//METADE DO LADO DO HEXAGONO:
#define HEXRAD 15.0

/*
    Representa uma nave espacial
*/
typedef struct spaceship {
  double w, h;
  double x, z;
  double rot;
  double vx, vy;
  double fr, ft; //Isto e em percentagem em relacao as forcas maximas
  double mass_tara, mass_comb;

  size_t npart;
  polygon ** parts;
  int * colors;
  int * fillpart;
  //adicionar aqui um ponteiro para uma imagem?
} spaceship;



/*
  Aloca memoria para a spaceship e cria-a
*/
spaceship * spc_init(double,double,double, view *);
/*
  Carrega o modelo da nave espacial
  TODO: Carregar de um ficheiro?
*/
void spc_init_model(spaceship *, view *);

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
void spc_draw(spaceship * s, camera2d * c, view * v);






#endif
