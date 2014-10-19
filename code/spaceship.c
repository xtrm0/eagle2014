#include "../include/spaceship.h"

spaceship * spc_init(double x, double z) {
  spaceship * s = (spaceship *)malloc(sizeof(spaceship));
  if (s == NULL) {
    printf("(3x23) Erro detetado: Memory Access Error!");
    exit(ENOMEM);
  }

  memset(s,0,sizeof(spaceship));
  s->x = x;
  s->z = z;
  s->w = 20.0;
  s->h = 20.0;
  return s;
}

void spc_destroy(spaceship * s) {
  free(s);
}


void spc_update_pos(spaceship * s, double dt) { //TODO: adicionar uma estrutura aos argumentos para verificar colisoes com os vertices no movimento

}


void spc_draw(spaceship * s, camera2d * c, view * v) {
  //ja vamos a rotacoes. Inicialmente vamos so mapear a posicao
  int i;
  double * g2p;
  polygon * pol;
  double p[4][4] = {{0}};
  double aux[4] = {0};

  point2d(s->x, s->z, 1.0, aux);
  point2d(0.0,0.0,  1.0, p[0]);
  point2d(0.0,s->h, 1.0, p[1]);
  point2d(s->w,s->h,1.0, p[2]);
  point2d(s->w,0.0, 1.0, p[3]);

  pol = poly(2);
  for (i=0; i<4; i++)
    poly_push(pol, p[i]);

  poly_rotate2d(pol, s->rot);
  //Agora e preciso desenha-la no referencial da camara e de seguida no da view

  poly_translate(pol, aux);

  g2p = poly_to_g2poly(pol);
  g2_filled_polygon(v->id, pol->size, g2p);
  //TODO:# Desenha o poligono que representa a nave, ja transformado, dentro das bounding da camera:
  //camera_filled_polygon(c->id, v->id, 4, points);
}
