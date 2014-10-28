#include "../include/gtimer.h"
void gtimer_destroy(gtimer *c ) {
  if (c!=NULL)
    free(c);
}

#if _POSIX_C_VERSION >= 199309L
gtimer * gtimer_init() {
  gtimer * c;
  c = malloc(sizeof(gtimer));
  TESTMEM(c);
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

void gtimer_sleep(gtimer * c, double sleeptime) {
  double slp;
  clock_gettime(CLOCK_MONOTONIC, &c->tend);
  slp = sleeptime - (((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec) - ((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec));
  c->tend.tv_sec = c->tstart.tv_sec;
  c->tend.tv_nsec = c->tstart.tv_nsec;
  if (slp > 0) {
     c->tsleep.tv_sec = (time_t) slp;
     c->tsleep.tv_nsec = (time_t) ((slp - c->tsleep.tv_sec)*10e8);
     nanosleep(&c->tsleep, &c->trem);
  }
}
#else
#ifdef _ISOC11_SOURCE
/*
  TODO: Aqui vamos usar:
    1) Mede o tempo usando timespec_get
    2) Utiliza a funcao thrd_sleep() para dormir
*/
gtimer * gtimer_init() {
  gtimer * c;
  c = malloc(sizeof(gtimer));
  TESTMEM(c);
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

void gtimer_sleep(gtimer * c, double sleeptime) {
  double slp;
  timespec_get(&c->tend, TIME_UTC);
  slp = sleeptime - (((double)c->tend.tv_sec + 1.0e-9*c->tend.tv_nsec) - ((double)c->tstart.tv_sec + 1.0e-9*c->tstart.tv_nsec));
  c->tend.tv_sec = c->tstart.tv_sec;
  c->tend.tv_nsec = c->tstart.tv_nsec;
  if (slp > 0) {
     c->tsleep.tv_sec = c->tend.tv_sec = (time_t) slp;
     c->tsleep.tv_nsec = c->tend.tv_nsec + (time_t) ((slp - ((size_t)(slp)))*10e8);
     thrd_sleep(&c->tsleep, &c->trem);
  }
}
#else
/*
  TODO: Utilizar relogios externos.
*/
#endif
#endif
