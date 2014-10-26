#include "../include/surface.h"

surface * sfc_init() {
  surface * s = malloc(sizeof(surface));
  TESTMEM(s);
  s->arr = poly();
  s->l_size = 0;
  s->l_max_size = 1;
  s->l_points = malloc(sizeof(size_t));
  TESTMEM(s->l_points);
  return s;
}

void sfc_destroy(surface * s) {
  poly_destroy(s->arr);
  free(s->l_points);
  free(s);
}

void sfc_add_point(surface * s, double * p) {
  poly_push(s->arr, p);
}

void sfc_add_lp(surface * s, size_t index) {
  size_t * g;
  if (s->l_max_size==s->l_size) {
    s->l_max_size = s->l_max_size * 2;
    g = malloc(sizeof(size_t) * s->l_max_size);
    TESTMEM(g);
    memcpy(g, s->l_points, sizeof(size_t) * s->l_size);
    free(s->l_points);
    s->l_points = g;
  }
  s->l_points[s->l_size] = index;
  s->l_size++;
}

void sfc_draw(surface * s, camera2d * c, view * v) {
  size_t i;
  polygon * pol;
  pol = poly();
  g2_pen(v->id, COLOR_MOON);
  g2_set_line_width(v->id, 4);
  poly_copy(s->arr, pol);
  poly_project(pol, c, pol);
  g2_poly_line(v->id, pol->size, pol->pts);
  for (i=0; i<s->l_size; i++) {
    g2_pen(v->id, COLOR_RED);
    g2_line(v->id, pol->pts[2*s->l_points[i]], pol->pts[2*s->l_points[i]+1], pol->pts[2*s->l_points[i]+2], pol->pts[2*s->l_points[i]+3]);
  }
}
