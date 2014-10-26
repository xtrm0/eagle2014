#ifndef SURFACE_H
#define SURFACE_H
#include "../include/geometry.h"
#include "../include/view.h"
/*
  Representa a superficie lunar
  arr-> vertices da superficies
  l_points -> array dinamica que indica as arestas que sao locais de aterragem
  l_size -> numero de pontos de aterragem
*/

typedef struct surface {
  polygon * arr;
  size_t l_size;
  size_t l_max_size;
  size_t * l_points;
} surface;

surface * sfc_init();

void sfc_add_point(surface * s, double * p);

void sfc_add_lp(surface * s, size_t index);

void sfc_draw(surface * s, camera2d * c, view * v);

#endif
