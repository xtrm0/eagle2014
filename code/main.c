#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(void) {
  while(!menu());

  return 0;
}

#else

#include <time.h>
#include <unistd.h>

//CODIGO MAIN PARA DEBUG :P

void cockpit() {
  struct timespec tstart, tend, tsleep, trem;
  view * v;
  spaceship * s;
  camera2d * c;
  double deltatime, sleeptime;
  double fps = 60.0;
  double revfps = 1.0/fps;
  int runapp;


  v = view_init(480, 320);
  c = c2d_init(480, 320, 0,0, 480, 320, 0, 0);
  s = spc_init(100, 200, 0.0, v);
  runapp = 1;
  tstart.tv_sec = 0; tstart.tv_nsec = 0;
  tend.tv_sec   = 0; tend.tv_nsec   = 0;

  while (runapp) {
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    deltatime = (((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec) - ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec));
    printf("%lf\n", deltatime);

    //Parte de logica:
    spc_update_pos(s,deltatime);


    //Parte grafica
    view_begin(v);
    g2_clear(v->id);
    spc_draw(s,c,v);
    view_end(v); //End means send the data to g2 physical device



    clock_gettime(CLOCK_MONOTONIC, &tend);
    sleeptime = revfps - (((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    tend.tv_sec = tstart.tv_sec;
    tend.tv_nsec = tstart.tv_nsec;
    if (sleeptime > 0) {
       tsleep.tv_sec = (time_t) sleeptime;
       tsleep.tv_nsec = (time_t) ((sleeptime-tsleep.tv_sec)*10e8); //TODO: ISTO DEVIA SER 10e9, mas por algum motivo so da bem quando ponho 10e8. Temos de investigar
       nanosleep(&tsleep, &trem);
    }

  }
}

int main(void) {
  cockpit();
  printf("Press a key to continue");
  getchar();
  return 0;
}



#endif
