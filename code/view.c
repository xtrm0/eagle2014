#include "../include/view.h"

view * view_init(int w, int h, char * name) {
  view * v = (view *)malloc(sizeof(view));
  if (v == NULL) {
    printf("(3x23) Erro detetado: Memory Access Error!");
    exit(ENOMEM);
  }
  memset(v,0,sizeof(view));
  v->W=w;
  v->H=h;
  v->name = name;
  v->dev = g2_open_X11X(w, h, 0, 0, name, name, "/dev/null", 0, 0);
  v->id = g2_open_vd();
  g2_attach(v->id, v->dev);
  g2_set_auto_flush(v->id, 0);
  g2_clear_palette(v->dev);
  //cores:
  g2_ink(v->dev, 0.0, 0.0, 0.0); //0
  g2_ink(v->dev, 1.0, 1.0, 1.0); //1
  g2_ink(v->dev, 1.0, 0.8, 0.6); //2
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
