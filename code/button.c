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
  g2_pen(v->id, btn->color);
  g2_filled_rectangle(v->id, btn->x, btn->y, btn->x+btn->w, btn->y+btn->h);
  g2_pen(v->id, btn->fcolor);
  g2_set_font_size(v->id, btn->fsz);
  g2_string(v->id, btn->x + 20, btn->y + (btn->h - btn->fsz)/2.0, btn->text);
}

int btn_hover(button * btn, double x, double y) {
  return (btn->x <= x && btn->x + btn->w >= x
      &&  btn->y <= y && btn->y + btn->h >= y);
}
