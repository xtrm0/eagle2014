#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "../include/defines.h"
#include "../include/geometry.h"
#include "../include/view.h"
#include "../include/surface.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
//METADE DO LADO DO HEXAGONO:
#define HEXRAD 15.0

#define N_TAU_R 10000.0
#define N_TAU_T 100000.0
#define N_BETA_R 1.0
#define N_BETA_T 1.0
#define N_G 1.622
#define N_PI 3.1415926535
#define FT 10.0

/*
    Representa uma nave espacial
*/
/*
  Estamos a guardar o historico para memoria por questoes de performance (nao mantemos o ficheiro aberto durante 10 minutos :P):
    Tamanho da array:
      7*FPS*TIME*8 bytes
    Se fps = 60 e TIME = 600 (10 minutos)
    Entao ocupamos aprox. 1.922 megabytes de memoria, o que e muito aceitavel (2016000 bytes)
*/
typedef struct spaceship {
  //Parte em relacao a inicializacao:
  int initialized;
  //Parte para desenhar para o ecra:
  double w, h;
  double x, z;
  double rot;
  double vx, vz, va; //w significa velocidade angular
  double fr, ft; //Isto e em percentagem em relacao as forcas maximas
  double mass_tara, mass_comb;
  double I;
  polygon * colision_shape;
  surface * moon;
  //Parte do historico para guardar para ficheiro:
  size_t h_len;
  size_t h_max;
  double ** hist;

  //Parte grafica
  size_t npart;
  polygon ** parts;
  int * colors;
  int * fillpart;
  //Por aqui um ponteiro para uma imagem
} spaceship;



/*
  Aloca memoria para a spaceship e cria-a
*/
spaceship * spc_init(double,double,double);
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

void spc_add_hist(spaceship * s, double dt);

void spc_save_to_file(spaceship *);


#endif
