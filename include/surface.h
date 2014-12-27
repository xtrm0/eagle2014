#ifndef SURFACE_H
#define SURFACE_H
#include "../include/geometry.h"
#include "../include/view.h"
#include "../include/list.h"
#define MAX_POINT_NAME 30
/*
  Representa a superficie lunar
  arr-> vertices da superficies
  l_points -> array dinamica que indica as arestas que sao locais de aterragem
  l_size -> numero de pontos de aterragem
*/
typedef struct MOON_POINT {
  char name[MAX_POINT_NAME];
  double c[2];
} moon_point;

typedef struct surface {
  list_no * arr;
  size_t arr_size;
  list_no * lp;
  size_t lp_size;
  list_no * arr_back;
  list_no * lp_back;
  list_no * curr_lp;
} surface;

surface * sfc_init();

void sfc_destroy(surface *);

/*
  Devolve um ponteiro para uma copia da superificie
 */
surface * _sfc_copy(surface * a);

/*
  Adiciona um ponto à superificie
 */
void sfc_add_point(surface * s, moon_point p);
/*
  Adiciona um ponto a seguir ao ultimo ponto da superficie
*/
void sfc_add_point_back(surface * s, moon_point * p);

/*
  Torna a aresta que se inicia no ponto com indice assinalado um local de aterragem seguro
 */
void sfc_add_lp(surface * s, char name[MAX_POINT_NAME]);

void sfc_draw(surface * s, camera2d * c, view * v);

void sfc_draw_labels(surface * s, camera2d * c, view * v);

void sfc_remove_arr(surface * s, list_no * tmp);

void sfc_clear_lp (surface * s);

/*
Funcoes auxiliares para as pesquisas:
*/
int arr_find_byname(void *a, void *b);
#endif
