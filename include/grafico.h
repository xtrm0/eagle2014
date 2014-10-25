#ifndef GRAFICO_H
#define GRAFICO_H
#include <stdio.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>
#include "../include/defines.h"
#include "../include/view.h"

/*
  Estrutura que representa um grafico
*/
typedef struct graph {
  polygon * data;
  camera2d * c;
  view * v;
  char * x_axis;
  char * y_axis;
  double max_x, max_y, min_x, min_y;
  int p_color, b_color, axisl_color, axisv_color, axisn_color;
} graph;

graph * graph_init(double W, double H, char * x_axis, char * y_axis, int b_color, int p_color, int axisl_color, int axisv_color, int axisn_color);

/*
  Esta funcao e o exemplo perfeito de um uso para a biblioteca g2, no entanto de modo a podermos utilizar a nossa camara, nao vamos usar
  o TODO:<nome da funcoa de referencial>
*/
int graph_load_points_from_file (char *, graph *);



#endif
