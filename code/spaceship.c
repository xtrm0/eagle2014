#include "../include/spaceship.h"

spaceship * spc_init(double x, double z, double rot) {
  spaceship * s = (spaceship *)malloc(sizeof(spaceship));
  TESTMEM(s);
  memset(s,0,sizeof(spaceship));
  s->initialized = 0;
  s->moon = sfc_init();
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
  TESTMEM(s->hist);
  s->hist[0] = malloc(sizeof(double)*7);
  TESTMEM(s->hist[0]);
  return s;
}

spaceship * _spc_copy(spaceship * a) {
  size_t i;
  if (a==NULL) return NULL;
  spaceship * s = (spaceship *)malloc(sizeof(spaceship));
  TESTMEM(s);
  memset(s,0,sizeof(spaceship));
  memcpy(s, a, sizeof(spaceship));
  if (a->colors!=NULL) {
    s->colors = malloc(sizeof(int)*s->npart);
    TESTMEM(s->colors);
    memcpy(s->colors,a->colors,sizeof(int)*s->npart);
  }
  if (a->fillpart!=NULL) {
    s->fillpart = malloc(sizeof(int)*s->npart);
    TESTMEM(s->fillpart);
    memcpy(s->fillpart,a->fillpart,sizeof(int)*s->npart);
  }
  if (a->moon!=NULL)
    s->moon = _sfc_copy(a->moon);
  if (a->colision_shape!=NULL)
    s->colision_shape = _poly_copy(a->colision_shape);
  if (a->parts!=NULL) {
    s->parts = malloc(sizeof(polygon *)*s->npart);
    TESTMEM(s->parts);
    for (i=0; i<a->npart; i++) {
      s->parts[i] = _poly_copy(a->parts[i]);
    }
  }
  s->hist = malloc(sizeof(double *) * a->h_max);
  TESTMEM(s->hist);
  for (i=0; i<a->h_len; i++) {
    s->hist[i] = malloc(sizeof(double)*7);
    TESTMEM(s->hist[i]);
    memcpy(s->hist[i],a->hist[i],sizeof(double)*7);
  }
  return s;
}

void spc_init_model(spaceship * s, view *v) {
  //TODO: passar a ler a nave de um ficheiro, em vez de ser daqui
  polygon * pol;
  double p[2]= {0}; //isto inicializa a {0,0}

  s->npart = 5;
  s->parts = malloc(sizeof(polygon *) * s->npart);
  s->fillpart = malloc(sizeof(int) * s->npart);
  s->colors = malloc(sizeof(int) * s->npart);
  TESTMEM(s->parts);
  TESTMEM(s->fillpart);
  TESTMEM(s->colors);
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
  point(-1.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD+0.01,               p); poly_push(pol, p);
  point(-3.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD,                    p); poly_push(pol, p);
  point(-(0.85+3.0*sqrt(3.0)/16)*HEXRAD,   (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
  point(-2*HEXRAD,                         (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
  point(-2*HEXRAD,                         (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  point(-HEXRAD,                           (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  s->parts[1] = pol;

  /* Spacecraft Right Leg */

  s->colors[2] = g2_ink(v->dev, 0, 0, 0); //#000000
  s->fillpart[2] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD,                    p); poly_push(pol, p);
  point(3.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD,                    p); poly_push(pol, p);
  point((0.85+3.0*sqrt(3.0)/16)*HEXRAD,   (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
  point(2*HEXRAD,                         (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
  point(2*HEXRAD,                         (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  point(HEXRAD,                           (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
  s->parts[2] = pol;


  /* Spacecraft Combustion Centre */

  s->colors[3] = g2_ink(v->dev, (7*16+1)/255.0, (9*16+14)/255.0, (12*16+14)/255.0); //#9193CE
  s->fillpart[3] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                    -sqrt(3.0)*HEXRAD,                           p); poly_push(pol, p);
  point(-1.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD,                           p); poly_push(pol, p);
  point(-0.5*HEXRAD,                       (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  s->parts[3] = pol;

  /* Combustion */

  s->colors[4] = g2_ink(v->dev, 1.0, 0.4, 0.2); //#FF6633
  s->fillpart[4] = 1;
  pol = poly();
  point(0.0,                                          (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,                                        p); poly_push(pol, p);
  point(1.0/12.0*(sqrt(3.0)*HEXRAD-0.5)*FT,           (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD+1.0/4.0*(sqrt(3.0)*HEXRAD-0.5)*FT,      p); poly_push(pol, p);
  s->parts[4] = pol;


  /*
   * Colision detection shape
   */

  s->colision_shape = poly();
  point(-2*HEXRAD,                     (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(s->colision_shape, p);
  point(2*HEXRAD,                      (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(s->colision_shape, p);
  point( HEXRAD*2, 0.0,                p); poly_push(s->colision_shape, p);
  point( HEXRAD,   +sqrt(3.0)*HEXRAD,  p); poly_push(s->colision_shape, p);
  point(-HEXRAD,   +sqrt(3.0)*HEXRAD,  p); poly_push(s->colision_shape, p);
  point(-HEXRAD*2, 0.0,                p); poly_push(s->colision_shape, p);

}

void spc_destroy(spaceship * s) {
  //TODO: completar isto
  size_t i;
  for (i=0; i<s->h_len; i++)
    free(s->hist[i]);
  free(s->hist);
  sfc_destroy(s->moon);
  free(s);
}

/*
  Estamos a usar o metodo de integracao Velocity Verlet:
    http://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
  Temos um erro proporcional a O(dt^2) que e bastante baixo. Se quisessemos diminuir este erro (o que nao seria justificavel para um jogo),
  podiamos recorrer � integracao tendo por base mais termos anteriores, mas isso seria desnecess�rio e custoso em termos de cpu.
*/
/*
  De modo a evitar mensagens como "Houston, we have a problem" decidimos impedir que os astronautas treinassem a aterragem com modelos fisico incorretos, efetuando a seguinte corrre��o ao pdf:
    Da equa��o da conserva��o extraimos d/dt (L) = F_r * R <=> d/dt (I*w) = F_r * R
*/
void spc_update_pos(spaceship * s, double dt) {
  //TODO: fazer as colisoes aqui
  //printf("dt:%lf, x: %lf\n",dt, s->x);
  double ax0, az0, aa0;
  double mass = s->mass_tara + s->mass_comb;
  /*
    Podiamos por aqui um for para fazer a integracao em intervalos mais pequenos do que a atualizacao grafica
    No entanto, nao o vamos fazer pois 1/60 de segundo e suficiente para a precisao utilizada
    Talvez na versao o final o facamos
  */
  //1) Calcula a(t), I(t):
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD; //Deviamos usar uma constante k: (2/5)<k<(2/3) em vez de 2/5,
  ax0 = -N_TAU_T*s->ft*sin(s->rot)/mass;
  az0 = N_TAU_T*s->ft*cos(s->rot)/mass-N_G;
  aa0 = N_TAU_R*s->fr*HEXRAD/s->I;
  //pois o peso nao esta uniformemente distruibuida pela nave (que ja agora tambem nao e uma esfera) a massa centra-se nas bordas da nave

  //2) Calcula (x,y,rot)(t+dt):
  s->rot = s->rot + s->va*dt + 0.5*aa0*dt*dt;
  s->x   = s->x   + s->vx*dt + 0.5*ax0*dt*dt;
  s->z   = s->z   + s->vz*dt + 0.5*az0*dt*dt;

  //3) Calcula a(t+dt) e I(t+dt): serve so para calcular v(t+dt) e w(t+dt);
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD;

  //4) Calcula v(t+dt), w(t+dt):
  s->va = s->va + (aa0 + N_TAU_R*s->fr*HEXRAD/s->I)/2.0*dt;
  s->vz = s->vz + (az0 + N_TAU_T*s->ft*cos(s->rot)/mass-N_G)/2.0*dt;
  s->vx  = s->vx + (ax0 +-N_TAU_T*s->ft*sin(s->rot)/mass)/2.0*dt;

  //normaliza a rotacao:
  s->rot = fmod(s->rot, 2*N_PI); //Nao vamos usar porque e importante saber se o astronauta andou as voltas com a nave para aterrar
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
  int i;
  polygon * pol;
  double aux[2] = {0};
  point(s->x, s->z, aux);
  pol = poly();
/*
  Desenha a colision_shape:
  poly_copy(s->colision_shape, pol);
  poly_rotate(pol, s->rot);
  poly_translate(pol, aux);
  poly_project(pol, c, pol);
  g2_pen(v->id, COLOR_RED);
  g2_polygon(v->id, pol->size, pol->pts);
*/
  for (i=0; i<s->npart; i++) {
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



void spc_add_hist(spaceship * s, double dt) {
  size_t i;
  double ** d;
  if (s->h_max==s->h_len) {
    s->h_max = s->h_max * 2;
    d = malloc(sizeof(double *) * s->h_max);
    TESTMEM(d);
    for (i=0; i<s->h_len; i++)
      d[i] = s->hist[i];
    free(s->hist);
    s->hist = d;
  }

  s->hist[s->h_len] = malloc(sizeof(double)*7);
  TESTMEM(s->hist[s->h_len]);
  s->hist[s->h_len][0] = dt;
  s->hist[s->h_len][1] = s->x;
  s->hist[s->h_len][2] = s->z;
  s->hist[s->h_len][3] = s->vx;
  s->hist[s->h_len][4] = s->vz;
  s->hist[s->h_len][5] = s->rot * 180.0 / (N_PI);
  s->hist[s->h_len][6] = s->mass_comb;
  s->h_len++;
}

/*
  Isto funciona apenas para o modo 2, e tem complexidade O(n_pontos_alunagem), o que aceitavel visto que so e executada 1 vez no fim das simulacoes
  Para o modo 5, temos de melhorar a surface: Vamos fazer esta funcao ser O(log(n_pontos_alunagem), usando algum estrutura que o permita (iex: kd-tree));
*/
int spc_unsafe_landing(spaceship * s) {
  size_t i;
  if ((s->rot <= N_PI && s->rot > MAXROT) || (s->rot >= N_PI && s->rot < 2*N_PI - MAXROT) || s->vz < -LAND_MAXVZ || s->vx > LAND_MAXVX || s->vx < -LAND_MAXVX)
    return 1; //pois nao cumpre as especificacoes
  for (i=0; i<s->moon->l_size; i++) {
    if (s->moon->arr->pts[s->moon->l_points[i]*2] + 2*HEXRAD < s->x && s->moon->arr->pts[s->moon->l_points[i]*2+2] > s->x -2*HEXRAD) return 0;
  }
  return 2;
}

void spc_save_to_file(spaceship * s) {
	size_t i;
	FILE *fileout;
  double realtime=0;
	if ((fileout = fopen ("vooLunarCorrente.txt", "w")) == NULL) {
    fprintf(stderr, "E: Não foi possível abrir o ficheiro 'vooLunarCorrente.txt'\n");
    return;
  }
  fprintf(fileout, "%lf [kg]\n", s->mass_tara);
  fprintf(fileout, FILE_HEADLINE);
	for (i=0; i<s->h_len; i++) {
  	fprintf(fileout, "%9.3lf", realtime += s->hist[i][0]);
  	fprintf(fileout, "%14.3lf", s->hist[i][1]);
  	fprintf(fileout, "%14.3lf", s->hist[i][2]);
  	fprintf(fileout, "%14.3lf", s->hist[i][3]);
  	fprintf(fileout, "%14.3lf", s->hist[i][4]);
  	fprintf(fileout, "%18.3lf", s->hist[i][5]);
  	fprintf(fileout, "%14.3lf\n", s->hist[i][6]);
	}
	fclose(fileout);
}
