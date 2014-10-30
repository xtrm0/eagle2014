#ifndef BUTTON_H
#define BUTTON_H
#include "../include/view.h"
/*
  Representa um botão que é desenhável para o ecrã
 */

typedef struct button {
  double x, y, w, h;
  double left, bottom;
  int color, fcolor;
  char * text;
  double fsz;
} button;

button * btn_init(double,double,double,double,double,double,int,char *,double,int);

void btn_destroy();

void btn_draw(button *, view *, double, double, unsigned int);

/*
  Indica se o rato se encontra sob o botão:
  returns:
    1 caso o ponteiro se encontre sobre o botão (mesmo que o botão se encontra invisível)
    0 caso contrário
 */
int btn_hover(button*, double x, double y);





#endif
