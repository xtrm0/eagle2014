#include "../include/spaceship.h"

spaceship * spc_init(double x, double z, double rot, view * v) {
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
  s->rot = rot;
  spc_init_model(s, v);
  return s;
}

void spc_init_model(spaceship * s, view *v) {
  //TODO: passar a ler a nave de um ficheiro, em vez de ser daqui
  int i;
  polygon * pol;
  double p[2]= {0}; //isto inicializa a {0,0}

  s->npart = 1; //TODO: edit this to add more parts
  s->parts = malloc(sizeof(polygon *) * s->npart);
  s->fillpart = malloc(sizeof(int) * s->npart);
  s->colors = malloc(sizeof(int) * s->npart);
  /* Spacecraft Head (hexagon) */

  s->colors[0] = g2_ink(v->dev, 1.0, 0.5, 1.0);
  s->fillpart[0] = 1;
  pol = poly();
  point(-HEXRAD,   -sqrt(3.0)*HEXRAD,  p); poly_push(pol, p);
  point(-HEXRAD*2, 0.0,                p); poly_push(pol, p);
  point(-HEXRAD,   +sqrt(3.0)*HEXRAD,  p); poly_push(pol, p);
  point(+HEXRAD,   +sqrt(3.0)*HEXRAD,  p); poly_push(pol, p);
  point(+HEXRAD*2, 0.0,                p); poly_push(pol, p);
  point(+HEXRAD,   -sqrt(3.0)*HEXRAD,  p); poly_push(pol, p);
  s->parts[0] = pol;
}

void spc_destroy(spaceship * s) {
  free(s);
}


void spc_update_pos(spaceship * s, double dt) { //TODO: adicionar uma estrutura aos argumentos para verificar colisoes com os vertices no movimento
  s->x += 1;
}


void spc_draw(spaceship * s, camera2d * c, view * v) {
  //ja vamos a rotacoes. Inicialmente vamos so mapear a posicao
  int i;
  polygon * pol;
  double aux[2] = {0};
  point(s->x, s->z, aux);
  pol = poly();

  for (i=0; i<s->npart; i++) {
//    printf("%d\n", s->colors[i]);
    poly_copy(s->parts[i], pol);
    poly_rotate(pol, s->rot);
    poly_translate(pol, aux);
    poly_project(pol, c, pol);
    g2_pen(v->id, s->colors[i]);
    if (s->fillpart[i]) {
      g2_filled_polygon(v->id, pol->size, pol->pts);
    } else {
      g2_polygon(v->id, pol->size, pol->pts);
    }
  }

}
