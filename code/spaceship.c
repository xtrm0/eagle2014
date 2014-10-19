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
  double g2p[8]; //estas variaveis sao automaticas e portanto a memoria e automaticamente libertada
  double p[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //um truque que inicializa todos os valores de p[4][4] com 0
  for (i=0; i<4; i++) {
    printf("%lf", p[i][0]);
    point2d(0,0,1,&p[0]);
  }

  //trasforma a array de pontos ortograficos em pontos reconhecidos pela g2
  for (i=0; i<4; i++) {
    normalize(p[i]);
    g2p[i*2] = p[i][1];
    g2p[i*2+1] = p[i][2];
  }

  g2_filled_rectangle(v->id, s->x, s->z, s->x+s->w, s->z+s->h);
  //g2_filled_polygon(v->id, 4, g2p);

  //TODO:# Desenha o poligono que representa a nave, ja transformado, dentro das bounding da camera:
  //camera_filled_polygon(c->id, v->id, 4, points);
}
