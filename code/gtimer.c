#include "../include/gtimer.h"
void gtimer_destroy(gtimer *c) {
  if (c!=NULL)
    free(c);
}

#if _POSIX_C_SOURCE >= 199309L
gtimer * gtimer_init(double tfps, int pts, int modo) {
  gtimer * c;
  c = malloc(sizeof(gtimer));
  TESTMEM(c);
  c->target_fps = tfps;
  c->fps = tfps;
  c->cnt = 10;
  clock_gettime(CLOCK_MONOTONIC, &c->tend);
  return c;
}

double gtimer_begin(gtimer * c) {
  clock_gettime(CLOCK_MONOTONIC, &c->tstart);
  return (double) (((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec) - ((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec));
}


double gtimer_getdt(gtimer * c) {
  return (double) (((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec) - ((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec));
}

void gtimer_sleep(gtimer * c) {
  double slp;
  /*printf("FPS: %f\ncnt:%d\n", c->fps, c->cnt);*/
  clock_gettime(CLOCK_MONOTONIC, &c->tend);
  slp = 1.0/c->fps - (((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec) - ((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec));
  c->tend.tv_sec = c->tstart.tv_sec;
  c->tend.tv_nsec = c->tstart.tv_nsec;
  if (slp > 0) {
    c->cnt = min(c->cnt+1, 14);
    if (abs(c->fps-c->target_fps) > SIGMA && c->cnt == 14) {
      c->cnt=10;
      c->fps *= 2.0;
    }
    c->tsleep.tv_sec = (time_t) slp;
    c->tsleep.tv_nsec = (time_t) ((slp - c->tsleep.tv_sec)*10e8);
    nanosleep(&c->tsleep, &c->trem);
  } else {
    c->cnt = max(c->cnt-1, 6);
    if (c->fps > 2 && c->cnt == 6) {
      c->cnt=10;
      c->fps /= 2.0;
    }
  }
}
#else
#if defined(_ISOC11_SOURCE) && !defined(__STDC_NO_THREADS__)
/*
  Estas funcoes ja foram definidas na norma C11, mas ainda nao foram implementadas o glibc, pelo que ainda nao existe codigo
  Nos decidimos, com o intuito de adicionar um certo je ne sais quoi ao trabalho deixarmos aqui a nossa ideia de como ficariam nesta nova implementacao.
  Para isso consultamos a norma C11, disponivel em http://www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=57853 
*/
gtimer * gtimer_init(double tfps, int pts, int modo) {
  gtimer * c;
  c = malloc(sizeof(gtimer));
  TESTMEM(c);
  c->target_fps = tfps;
  c->fps = tfps;
  c->cnt = 10;
  timespec_get(&c->tend, TIME_UTC);
  return c;
}


double gtimer_begin(gtimer * c) {
  timespec_get(&c->tstart, TIME_UTC);
  return (double) (((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec) - ((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec));
}


double gtimer_getdt(gtimer * c) {
  return (double) (((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec) - ((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec));
}

void gtimer_sleep(gtimer * c) {
  double slp;
  timespec_get(&c->tend, TIME_UTC);
  slp = 1.0/c->fps - (((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec) - ((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec));
  c->tend.tv_sec = c->tstart.tv_sec;
  c->tend.tv_nsec = c->tstart.tv_nsec;
  if (slp > 0) {
    c->cnt = min(c->cnt+1, 14);
    if (abs(c->fps-c->target_fps) > SIGMA && c->cnt == 14) {
      c->cnt=10;
      c->fps *= 2.0;
    }
    c->tsleep.tv_sec = c->tend.tv_sec = (time_t) slp;
    c->tsleep.tv_nsec = c->tend.tv_nsec + (time_t) ((slp - ((size_t)(slp)))*10e8);
    thrd_sleep(&c->tsleep, &c->trem);
  } else {
    c->cnt = max(c->cnt-1, 6);
    if (c->fps > 2 && c->cnt == 6) {
      c->cnt=10;
      c->fps /= 2.0;
    }
  }
}
#else
gtimer * gtimer_init(double tfps, int pts, int modo) {
  unsigned long int ticks=0;
  time_t tmp;
  gtimer * c;
  c = malloc(sizeof(gtimer));
  TESTMEM(c);
  c->tlu=time(NULL);
  c->fps = tfps;
  tmp = time(NULL);
  while(tmp!=time(NULL));
  tmp = time(NULL);
  for (ticks=0; (tmp+5>time(NULL)); ticks++);
  c->steps = (unsigned long int) ticks / (tfps);
  return c;
}

/*
  Atualiza o numero de steps que dorme
*/
double gtimer_begin(gtimer * c) {
  if (c->tlu!=time(NULL)) {
    c->steps = c->steps * (c->times/c->fps);
    c->times = 0;
  }
  return gtimer_getdt(c);
}

double gtimer_getdt(gtimer * c) {
  return 1/c->fps;
}

/*Funcao privada, feita apenas para cumprir o prototipo pedido no enunciado*/
void mysleep(unsigned long ticks) {
  while(ticks--);
}

void gtimer_sleep(gtimer * c) {
  gtimer_begin(c);
  c->times++;
  mysleep(c->steps);
}

#endif
#endif
