#ifndef VIEW_H
#define VIEW_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include "geometry.h"

/*
  Estrutura que representa uma janela que esta a ser mostrada ao utilizador
  (W,H): Dimensoes da janela
  id: Id da janela a desenhar, alocada no init pela libg2
*/
typedef struct view {
  int W, H;
  int id, dev;
} view;


view * view_init(int,int);
void view_destroy(view *);
void view_flush(view * v);
//TODO: void map2d(view * c, camera * p, double p[4], double r[4]);


#endif
