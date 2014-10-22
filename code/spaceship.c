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

  s->npart = 5; //TODO: edit this to add more parts
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

  /* Spacecraft Left Leg */

  s->colors[1] = g2_ink(v->dev, 1.0, 0.5, 1.0);
  s->fillpart[1] = 1;
  pol = poly();
  point(-1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-3.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-(0.85+3.0*sqrt(3.0)/16)*HEXRAD,   (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,  p); poly_push(pol, p);
  point(-2*HEXRAD,                      (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,  p); poly_push(pol, p);
  point(-2*HEXRAD,                      (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  point(-HEXRAD,                        (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  s->parts[1] = pol;

  /* Spacecraft Right Leg */

  s->colors[2] = g2_ink(v->dev, 1.0, 0.5, 1.0);
  s->fillpart[2] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(3.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point((0.85+3.0*sqrt(3.0)/16)*HEXRAD,   (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,  p); poly_push(pol, p);
  point(2*HEXRAD,                      (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,  p); poly_push(pol, p);
  point(2*HEXRAD,                      (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  point(HEXRAD,                        (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  s->parts[2] = pol;


  /* Spacecraft Combustion Centre */

  s->colors[3] = g2_ink(v->dev, 1.0, 0.5, 1.0);
  s->fillpart[3] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  s->parts[3] = pol;

  /* Combustion */

  s->colors[4] = g2_ink(v->dev, 1.0, 0.5, 1.0);
  s->fillpart[4] = 1;
  pol = poly();
  point(0.0,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(1.0/12.0*(sqrt(3.0)*HEXRAD-0.5)*FT,           (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD+1.0/4.0*(sqrt(3.0)*HEXRAD-0.5)*FT,      p); poly_push(pol, p);
  s->parts[4] = pol;

}

void spc_destroy(spaceship * s) {
  free(s);
}

void spc_update_pos(spaceship * s, double dt) { //TODO: adicionar uma estrutura aos argumentos para verificar colisoes com os vertices no movimento
  printf("dt:%lf, x: %lf\n",dt, s->x);
  s->x += 100*dt;
}


void spc_draw(spaceship * s, camera2d * c, view * v) {
  //ja vamos a rotacoes. Inicialmente vamos so mapear a posicao
  int i;
  polygon * pol;
  double aux[2] = {0};
  point(s->x, s->z, aux);
  pol = poly();

  for (i=0; i<s->npart; i++) {
    poly_copy(s->parts[i], pol);
    poly_rotate(pol, s->rot);
    poly_translate(pol, aux);
    //TODO: Podemos deixar de usar camaras, e passar a definir o referncial do virtual device, diretamente para o g2 (E uma questao de altera a linha a seguir: )
    poly_project(pol, c, pol);
    g2_pen(v->id, s->colors[i]);
    if (s->fillpart[i]) {
      g2_filled_polygon(v->id, pol->size, pol->pts);
    } else {
      g2_polygon(v->id, pol->size, pol->pts);
    }
  }

}
