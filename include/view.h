#ifndef VIEW_H
#define VIEW_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include "geometry.h"
#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define COLOR_GUI   2

/*
  Estrutura que representa uma janela que esta a ser mostrada ao utilizador
  Esta janela implementa double buffering atravez dos metodos begin e end
  (W,H): Dimensoes da janela
  id: Id da janela a desenhar, alocada no init pela libg2
*/
typedef struct view {
  int W, H;
  int id, dev;
  char * name;
} view;


view * view_init(int,int,char *);
void view_destroy(view *);
void view_begin(view * v);
void view_end(view * v);
//TODO: void map2d(view * c, camera * p, double p[4], double r[4]);


#endif
