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
  g2_clear_palette(v->dev);
  return v;
}

void view_destroy(view * v) {
  free(v);
}

void view_begin(view * v) {
  //atualmente isto nao faz nada :P
}
void view_end(view * v) {
  g2_flush(v->id);
}
