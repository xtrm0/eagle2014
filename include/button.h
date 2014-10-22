#ifndef BUTTON_H
#define BUTTON_H
#include "../include/view.h"
typedef struct button {
  double x, y, w, h;
  int color, fcolor;
  char * text;
  double fsz;
} button;

button * btn_init(double,double,double,double,int,char *,double,int);

void btn_destroy();

void btn_draw(button *, view *);

int btn_hover(button*, double x, double y);





#endif
