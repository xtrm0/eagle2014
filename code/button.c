#include "../include/button.h"
button * btn_init(double x,double y,double w, double h, double left, double bottom, int color,char * text, double fsz, int fcolor){
  button * btn = malloc(sizeof(button));
  TESTMEM(btn);
  btn->text = malloc(1+strlen(text));
  TESTMEM(btn->text);
  strcpy(btn->text, text);
  btn->x = x;
  btn->y = y;
  btn->w = w;
  btn->h = h;
  btn->left = left;
  btn->bottom = bottom;
  btn->color = color;
  btn->fsz = fsz;
  btn->fcolor = fcolor;
  return btn;
}

void btn_destroy(button * btn) {
  if (btn!=NULL) {
    if (btn->text!=NULL)
      free(btn->text);
    free(btn);
  }
}

void btn_draw(button * btn, view * v, double x, double y, unsigned int mouse_button) {
  /*TODO: Desenha um botao na posicao assinalada */
  if (btn_hover(btn, x, y)) {
    if (mouse_button & Button1MotionMask)
      g2_pen(v->id, COLOR_CLICK);
    else
      g2_pen(v->id, COLOR_COMB_R);
  } else {
    g2_pen(v->id, btn->color);
  }
  g2_filled_rectangle(v->id, btn->x+3, btn->y, btn->x+btn->w-3, btn->y+btn->h);
  g2_filled_rectangle(v->id, btn->x, btn->y+3, btn->x+3, btn->y+btn->h-3);
  g2_filled_rectangle(v->id, btn->x+btn->w-3, btn->y+3, btn->x+btn->w, btn->y+btn->h-3);
  g2_filled_circle(v->id, btn->x+3, btn->y+3, 3);
  g2_filled_circle(v->id, btn->x+btn->w-3, btn->y+3, 3);
  g2_filled_circle(v->id, btn->x+3, btn->y+btn->h-3, 3);
  g2_filled_circle(v->id, btn->x+btn->w-3, btn->y+btn->h-3, 3);
  g2_pen(v->id, btn->fcolor);
  g2_set_font_size(v->id, btn->fsz);
  g2_string(v->id, btn->x + btn->left, btn->y + btn->bottom, btn->text);
}

int btn_hover(button * btn, double x, double y) {
  /*
    @Warning: O g2 nao permite saber se o rato se encontra diretamente sobre a janela ou se encontra uma janela entre o rato e a janela do g2.
  */
  return (btn->x <= x && btn->x + btn->w >= x
      &&  btn->y <= y && btn->y + btn->h >= y);
}
