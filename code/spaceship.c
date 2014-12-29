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
  s->mass_tara = N_TARA;
  s->mass_comb = 1200.0;
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
  spaceship * s;
  if (a==NULL) return NULL;
  s = (spaceship *)malloc(sizeof(spaceship));
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
  polygon * pol;
  double p[2]= {0}; /*isto inicializa a {0,0} */

  s->npart = 4;
  s->parts = malloc(sizeof(polygon *) * s->npart);
  s->fillpart = malloc(sizeof(int) * s->npart);
  s->colors = malloc(sizeof(int) * s->npart);
  TESTMEM(s->parts);
  TESTMEM(s->fillpart);
  TESTMEM(s->colors);
  /* Spacecraft Head (hexagon) */

  s->colors[0] = g2_ink(v->dev, 0.6, 0.4, 0.8); /*#9966CC */
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

  s->colors[1] = g2_ink(v->dev, 0, 0, 0); /*#00000 */
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

  s->colors[2] = g2_ink(v->dev, 0, 0, 0); /*#000000 */
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

  s->colors[3] = g2_ink(v->dev, (7*16+1)/255.0, (9*16+14)/255.0, (12*16+14)/255.0); /*#9193CE */
  s->fillpart[3] = 1;
  pol = poly();
  point(1.0/4.0*HEXRAD,                    -sqrt(3.0)*HEXRAD,                           p); poly_push(pol, p);
  point(-1.0/4.0*HEXRAD,                   -sqrt(3.0)*HEXRAD,                           p); poly_push(pol, p);
  point(-0.5*HEXRAD,                       (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  point(0.5*HEXRAD,                        (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,            p); poly_push(pol, p);
  s->parts[3] = pol;

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
  size_t i;
  if (s!=NULL) {
    sfc_destroy(s->moon);
    poly_destroy(s->colision_shape);
    if (s->colors!=NULL)
      free(s->colors);
    if (s->fillpart!=NULL)
      free(s->fillpart);
    if (s->parts!=NULL) {
      for (i=0; i<s->npart; i++)
        poly_destroy(s->parts[i]);
      free(s->parts);
    }
    if (s->hist!=NULL) {
      for (i=0; i<s->h_len; i++)
        free(s->hist[i]);
      free(s->hist);
    }
    free(s);
  }
}

/*
  Estamos a usar o metodo de integracao Velocity Verlet:
    http://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
  Temos um erro proporcional a O(dt^2) que e bastante baixo. Se quisessemos diminuir este erro (o que nao seria justificavel para um jogo),
  podiamos recorrer à integracao tendo por base mais termos anteriores, mas isso seria desnecessecário e custoso em termos de ciclos do processador.

  //TODO: isto tem de devolver o valor da atualizacao e fazer colision checking
*/
int spc_update_pos(spaceship * s, double dt) {
  /*TODO: fazer as colisoes aqui */
  /*printf("dt:%f, x: %f\n",dt, s->x); */
  double ax0, az0, aa0;
  double mass;
  if (s->mass_comb <= 0) {
    s->mass_comb = 0;
    s->fr = 0;
    s->ft = 0;
  }
  mass = s->mass_tara + s->mass_comb;
  /*
    Podiamos por aqui um for para fazer a integracao em intervalos mais pequenos do que a atualizacao grafica
    No entanto, nao o vamos fazer pois 1/60 de segundo e suficiente para a precisao utilizada
    Talvez na versao o final o facamos
  */
  /*1) Calcula a(t), I(t): */
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD; /*Deviamos usar uma constante k: (2/5)<k<(2/3) em vez de 2/5, */
  ax0 = -N_TAU_T*s->ft*sin(s->rot)/mass;
  az0 = N_TAU_T*s->ft*cos(s->rot)/mass-N_G;
  aa0 = N_TAU_R*s->fr*HEXRAD/s->I;
  /*pois o peso nao esta uniformemente distruibuida pela nave (que ja agora tambem nao e uma esfera) a massa centra-se nas bordas da nave */

  /*2) Calcula (x,y,rot)(t+dt): */
  s->rot = s->rot + s->va*dt + 0.5*aa0*dt*dt;
  s->x   = s->x   + s->vx*dt + 0.5*ax0*dt*dt;
  s->z   = s->z   + s->vz*dt + 0.5*az0*dt*dt;

  /*3) Calcula a(t+dt) e I(t+dt): serve so para calcular v(t+dt) e w(t+dt); */
  s->I = 2.0/5.0 * mass * HEXRAD * HEXRAD;
  s->mass_comb = s->mass_comb - (abs(N_BETA_R*N_TAU_R*s->fr) + N_BETA_T*N_TAU_T*s->ft)*dt;

  /*4) Calcula v(t+dt), w(t+dt): */
  s->va = s->va + (aa0 + N_TAU_R*s->fr*HEXRAD/s->I)/2.0*dt;
  s->vz = s->vz + (az0 + N_TAU_T*s->ft*cos(s->rot)/mass-N_G)/2.0*dt;
  s->vx  = s->vx + (ax0 +-N_TAU_T*s->ft*sin(s->rot)/mass)/2.0*dt;

  /*normaliza a rotacao: */
  /* s->rot = fmod(s->rot, 2*N_PI); Nao vamos usar porque e importante saber se o astronauta andou as voltas com a nave para aterrar */

  /*Adiciona os novos pontos a funcao que guarda na memoria a trajetoria da nave */
  spc_add_hist(s, dt);
/*
  printf("x:%f, z: %f, rot: %f, vx: %f, vz: %f\n", s->x, s->z, s->rot, s->vx, s->vz);
  printf("ft:%f, fr: %f, mass: %f, tau_R: %f, tau_t: %f\n", s->ft, s->fr, mass, N_TAU_R, N_TAU_T);
  printf("%f, %f, %f, %f\n", N_TAU_T, s->ft, cos(s->rot), mass);
  printf("%f || %f || %f\n", ax0, az0, aa0);
  */
  return 3;
}


void spc_draw(spaceship * s, camera2d * c, view * v) {
  size_t i;
  polygon * pol;
  double p[2] = {0};
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
  /*Pontos variaveis com o tempo (chamas): */
  /*Chama vertical*/
  poly_clear(pol);
  point(0.0,                       (-3.0/2.0*sqrt(3.0)+0.25-s->ft*2)*HEXRAD,      p); poly_push(pol, p);
  point(-0.25*HEXRAD*(1+s->ft),               (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,      p); poly_push(pol, p);
  point(0.25*HEXRAD*(1+s->ft),                (-3.0/2.0*sqrt(3.0)+0.25)*HEXRAD,      p); poly_push(pol, p);
  poly_rotate(pol, s->rot);
  poly_translate(pol, aux);
  poly_project(pol, c, pol);
  g2_pen(v->id, COLOR_COMB_T);
  g2_filled_polygon(v->id, pol->size, pol->pts);

  /* Chamas horizontais */
  poly_clear(pol);
  if (s->fr >= 0) {
    point(-2*HEXRAD,                         (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
    point(-2*HEXRAD,                         (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
    point(-(2+sin(s->fr*N_PI/2.0))*HEXRAD,   (-2*sqrt(3.0)+9.0/50.0+0.5)*HEXRAD,     p); poly_push(pol, p);
  } else {
    point(2*HEXRAD,                         (-2*sqrt(3.0)+9.0/25.0+0.5)*HEXRAD,   p); poly_push(pol, p);
    point(2*HEXRAD,                         (-2*sqrt(3.0)+0.5)*HEXRAD,            p); poly_push(pol, p);
    point((2+sin(-s->fr*N_PI/2.0))*HEXRAD,   (-2*sqrt(3.0)+9.0/50.0+0.5)*HEXRAD,     p); poly_push(pol, p);
  }
  poly_rotate(pol, s->rot);
  poly_translate(pol, aux);
  poly_project(pol, c, pol);
  g2_pen(v->id, COLOR_COMB_R);
  g2_filled_polygon(v->id, pol->size, pol->pts);

  poly_destroy(pol);
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


int spc_unsafe_landing(spaceship * s) {
  /*
    //TODO
  */
  if ((s->rot <= N_PI && s->rot > MAXROT) || (s->rot >= N_PI && s->rot < 2*N_PI - MAXROT) || s->vz < -LAND_MAXVZ || s->vx > LAND_MAXVX || s->vx < -LAND_MAXVX)
    return 1; /*pois nao cumpre as especificacoes */
/*  for (i=0; i<s->moon->l_size; i++) {
    if (s->moon->arr->pts[s->moon->l_points[i]*2] + 2*HEXRAD < s->x && s->moon->arr->pts[s->moon->l_points[i]*2+2] > s->x -2*HEXRAD) return 0;
  }
  */
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
  fprintf(fileout, "%f [kg]\n", s->mass_tara);
  fprintf(fileout, FILE_HEADLINE);
	for (i=0; i<s->h_len; i++) {
  	fprintf(fileout, "%9.3f", realtime += s->hist[i][0]);
  	fprintf(fileout, "%14.3f", s->hist[i][1]);
  	fprintf(fileout, "%14.3f", s->hist[i][2]);
  	fprintf(fileout, "%14.3f", s->hist[i][3]);
  	fprintf(fileout, "%14.3f", s->hist[i][4]);
  	fprintf(fileout, "%18.3f", s->hist[i][5]);
  	fprintf(fileout, "%14.3f\n", s->hist[i][6]);
	}
	fclose(fileout);
}

