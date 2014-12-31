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
/*METADE DO LADO DO HEXAGONO: */
#define HEXRAD 4.5

/*Constantes fisicas: */
/* Obtidos a partir da pagina da wikipedia http://en.wikipedia.org/wiki/Apollo_Lunar_Module*/
#define N_TAU_R 441
#define N_TAU_T 44400
/*Os valores de Beta estao apenas na ordem de grandeza certa, no entanto dependem das caracteristicas do combustivel, pelo que nada sabemos sobre elas*/
#define N_BETA_R 0.01
#define N_BETA_T 0.0001
#define N_G 1.622
#define N_PI 3.1415926535
#define N_TARA 14696



/*
    Representa o tudo o que esteja relacionado com a nave espacial
    Estamos a guardar a superificie lunar aqui, porque todas as funcoes que utilizam a superificie lunar tambem utilizam a nave espacial
*/
/*
  Estamos a guardar o historico para memoria por questoes de performance (nao mantemos o ficheiro aberto durante 10 minutos :P):
    Tamanho da array:
      7*FPS*TIME*8 bytes
    Se fps = 60 e TIME = 600 (10 minutos)
    Entao ocupamos aprox. 1.922 megabytes de memoria, o que e muito aceitavel (2016000 bytes)
*/
typedef struct spaceship {
  /*Parte em relacao a inicializacao: */
  int initialized;
  /*Parte para desenhar para o ecra: */
  double w, h;
  double x, z;
  double rot;
  double vx, vz, va;
  double fr, ft; /*Isto e em percentagem em relacao as forcas maximas */
  double mass_tara, mass_comb;
  double I;
  double fps;
  polygon * colision_shape;
  surface * moon;
  /*Parte do historico para guardar para ficheiro: */
  size_t h_len;
  size_t h_max;
  double ** hist;

  /*Parte grafica */
  size_t npart;
  polygon ** parts;
  int * colors;
  int * fillpart;
  /* Nao estamos a usar um png porque a imagem da spaceship e tao simples que nao faz sentido */
} spaceship;



/*
  Aloca memoria para a spaceship e cria-a
*/
spaceship * spc_init(double,double,double,double);
/*
  Carrega o modelo da nave espacial
*/
void spc_init_model(spaceship *, view *);

spaceship * _spc_copy(spaceship * a);

/*
  Desaloca a memoria da spaceship
*/
void spc_destroy(spaceship * s);

/*
  Atualiza a posicao da nave, apos terem passado dt segundos
*/
int spc_update_pos(spaceship * s, double dt);

/*
  Desenha a nave, para a janela v, usando a camara para fazer projecoes;
*/
void spc_draw(spaceship * s, camera2d * c, view * v);

/*
  Desenha a colision shape da nave, para a janela v, usando a camara para fazer projecoes;
*/
void spc_draw_cs(spaceship * s, camera2d * c, view * v);

/*
  Guarda os pontos atuais da posição da nave em memória
  O(1+)
 */
void spc_add_hist(spaceship * s, double dt);

/*
  Grava os pontos de posição da nave que se encontram em memória no ficheiro vooLunarCorrente.txt
   O(1+)
 */
void spc_save_to_file(spaceship *);

/*
  indica se a posicao atual da spaceship s e um local de aterragem seguro, e se encontra consoante as especificacoes do pdf
  devolve:
    0 em aterragem segura dentro de uma zona segura
    1 em aterragem perigosa
    2 em aterragem segura fora de pontos de alunagem

  Notas: Ver spaceship.c para notas sobre complexidade
*/
int spc_safe_landing(spaceship * s, double * p1, double * p2);


#endif
