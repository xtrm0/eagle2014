#include "../include/view.h"

view * view_init(int w, int h) {
  view * v = (view *)malloc(sizeof(view));
  if (v == NULL) {
    printf("(3x23) Erro detetado: Memory Access Error!");
    exit(ENOMEM);
  }
  memset(v,0,sizeof(view));
  v->W=w;
  v->H=h;
  v->dev = g2_open_X11(w, h);
  v->id = g2_open_vd();
  g2_attach(v->id, v->dev);
  g2_set_auto_flush(v->id, 0);
  return v;
}

void view_destroy(view * v) {
  free(v);
}


camera2d * c2d_init(double w, double h, double x, double y) {
  camera2d * c = (camera2d *)malloc(sizeof(camera2d));
  if (c == NULL) {
    printf("(3x23) Erro detetado: Memory Access Error!");
    exit(ENOMEM);
  }
  memset(c,0,sizeof(camera2d));
  c->W=w;
  c->H=h;
  c->X=x;
  c->Y=y;
  return c;
}
void c2d_destroy(camera2d * c) {
  free(c);
}

void view_flush(view * v) {
  g2_flush(v->id);
}
