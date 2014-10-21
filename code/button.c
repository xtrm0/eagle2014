#include "../include/button.h"
button * btn_init(double x,double y,double w, double h,int color,char * text, double fsz, int fcolor){
  button * btn = malloc(sizeof(button));
  btn->x = x;
  btn->y = y;
  btn->w = w;
  btn->h = h;
  btn->color = color;
  btn->text = text;
  btn->fsz = fsz;
  btn->fcolor = fcolor;
  return btn;
}

void btn_destroy(button * btn) {
  free(btn->text);
  free(btn);
}

void btn_draw(button * btn, view * v) {
  //TODO: Desenha um botao na posicao assinalada
}

int mouse_hover(button * btn, double x, double y) {
  return (btn->x <= x && btn->x + btn->w >= x
      &&  btn->y <= y && btn->y + btn->h >= y);
}
