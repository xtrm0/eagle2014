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
  s->mass_tara = 1000.0;
  s->mass_comb = 100.0;
  s->h_len=0;
  s->h_max=1;
  s->hist = malloc(sizeof(double *)*1);
  s->hist[0] = malloc(sizeof(double)*7);
  spc_init_model(s, v);
  return s;
}

void spc_init_model(spaceship * s, view *v) {
  //TODO: passar a ler a nave de um ficheiro, em vez de ser daqui
  int i;
  polygon * pol;
  double p[2]= {0}; //isto inicializa a {0,0}

  s->npart = 5;
  s->parts = malloc(sizeof(polygon *) * s->npart);
  s->fillpart = malloc(sizeof(int) * s->npart);
  s->colors = malloc(sizeof(int) * s->npart); //Usámos o programa gpick para tirar as cores a partir do pdf

  /* Spacecraft Head (hexagon) */

  s->colors[0] = g2_ink(v->dev, 0.6, 0.4, 0.8); //#9966CC
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

  s->colors[1] = g2_ink(v->dev, 0, 0, 0); //#00000
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

  s->colors[2] = g2_ink(v->dev, 0, 0, 0); //#000000
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

  s->colors[3] = g2_ink(v->dev, (7*16+1)/255.0, (9*16+14)/255.0, (12*16+14)/255.0); //#9193CE
  s->fillpart[3] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-1.0/4.0*HEXRAD,                -sqrt(3.0)*HEXRAD,              p); poly_push(pol, p);
  point(-0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  s->parts[3] = pol;

  /* Combustion */

  s->colors[4] = g2_ink(v->dev, 1.0, 0.4, 0.2); //#FF6633
  s->fillpart[4] = 1;
  pol = poly();
  point(0.0,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(1.0/12.0*(sqrt(3.0)*HEXRAD-0.5)*FT,           (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD+1.0/4.0*(sqrt(3.0)*HEXRAD-0.5)*FT,      p); poly_push(pol, p);
  s->parts[4] = pol;
}

void spc_destroy(spaceship * s) {
  free(s);
}

/*
  Estamos a usar o metodo de integracao Velocity Verlet:
    http://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
  Temos um erro proporcional a O(dt^2) que e bastante baixo. Se quisessemos diminuir este erro (o que nao seria justificavel para um jogo),
  podiamos recorrer à integracao tendo por base mais termos anteriores, mas isso seria desnecessário e custoso em termos de cpu.
*/
/*
  De modo a evitar mensagens como "Houston, we have a problem" decidimos impedir que os astronautas treinassem a aterragem com modelos fisico incorretos, efetuando a seguinte corrreção ao pdf:
    Da equação da conservação extraimos d/dt (L) = F_r * R <=> d/dt (I*w) = F_r * R
*/
void spc_update_pos(spaceship * s, double dt) { //TODO: adicionar uma estrutura aos argumentos para verificar colisoes com os vertices no movimento
  printf("dt:%lf, x: %lf\n",dt, s->x);
  double ax0, az0, aa0;
  double fx, fz;
  double mass = s->mass_tara + s->mass_comb;
  //1) Calcula a(t), I(t):
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD; //Deviamos usar uma constante k: (2/5)<k<(2/3) em vez de 2/5,
  ax0 = -N_TAU_T*s->ft*sin(s->rot)/mass;
  az0 = N_TAU_T*s->ft*cos(s->rot)/mass-N_G;
  aa0 = N_TAU_R*s->fr*HEXRAD/s->I;
  //pois o peso nao esta uniformemente distruibuida pela nave (que ja agora tambem nao e uma esfera) a massa centra-se nas bordas da nave

  //2) Caclcula (x,y,rot)(t+dt):
  s->rot = s->rot + s->va*dt + 0.5*aa0*dt*dt;
  s->x   = s->x   + s->vx*dt + 0.5*ax0*dt*dt;
  s->z   = s->z   + s->vz*dt + 0.5*az0*dt*dt;

  //3) Calcula a(t+dt) e I(t+dt): serve so para calcular v(t+dt) e w(t+dt);
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD;

  //4) Calcula v(t+dt), w(t+dt):
  s->va = s->va + (aa0 + N_TAU_R*s->fr*HEXRAD/s->I)/2.0*dt;
  s->vz = s->vz + (az0 + N_TAU_T*s->ft*cos(s->rot)/mass-N_G)/2.0*dt;
  s->vx  = s->vx + (ax0 +-N_TAU_T*s->ft*sin(s->rot)/mass)/2.0*dt;

  //Adiciona os novos pontos a funcao que guarda na memoria a trajetoria da nave
  spc_add_hist(s, dt);
/*
  printf("x:%lf, z: %lf, rot: %lf, vx: %lf, vz: %lf\n", s->x, s->z, s->rot, s->vx, s->vz);
  printf("ft:%lf, fr: %lf, mass: %lf, tau_R: %lf, tau_t: %lf\n", s->ft, s->fr, mass, N_TAU_R, N_TAU_T);
  printf("%lf, %lf, %lf, %lf\n", N_TAU_T, s->ft, cos(s->rot), mass);
  printf("%lf || %lf || %lf\n", ax0, az0, aa0);
  */
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



void spc_add_hist(spaceship * s, double dt) {
  size_t i;
  double ** d;
  if (s->h_max==s->h_len) {
    s->h_max = s->h_max * 2;
    d = malloc(sizeof(double *) * s->h_max); //Podiamos evitar o malloc usando uma array de pontos, mas a complexidade mantinha-se O(1+),
    //, a unica diferenca e que diminuiamos a constante
    for (i=0; i<s->h_len; i++)
      d[i] = s->hist[i];
    free(s->hist);
    s->hist = d;
  }

  s->hist[s->h_len] = malloc(sizeof(double)*7);
  s->hist[s->h_len][0] = dt;
  s->hist[s->h_len][1] = s->x;
  s->hist[s->h_len][2] = s->z;
  s->hist[s->h_len][3] = s->vx;
  s->hist[s->h_len][4] = s->vz;
  s->hist[s->h_len][5] = s->rot * 90.0 / 2*N_PI;
  s->hist[s->h_len][6] = s->mass_comb;
  s->h_len++;
}

void spc_save_to_file(spaceship * s) {
  //TODO:@ALCapas
  size_t i;

  for (i=0; i<s->h_len; i++) {
    //pass
  }
}
