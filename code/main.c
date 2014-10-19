#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(void) {
  while(!menu());

  return 0;
}

#else
//CODIGO MAIN PARA DEBUG :P

int main(void) {
  view * v;
  spaceship * s;
  camera2d * c;
  v = view_init(800, 600);
  c = c2d_init(800, 600, 100,-100, 400, 300, 100, 100);
  s = spc_init(100, 200);
  spc_draw(s,c,v);
  view_flush(v);
  printf("%lf %lf\n", s->x, s->z);

  printf("Press a key to continue");
  getchar();
  return 0;
}



#endif
