#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(int argc, char** argv) {
  spaceship * s;
  double tmp=0;
  if (argc<=1) {
    printf("Warning: tempo de sleep nao definido, usando valor default 8ms. (chame o programa como ./eagle2014 <sleeptime in ms>\n");
  } else if (argc==2) {
    tmp=strtod(argv[1],NULL);
  } else {
    printf("Demasiados argumentos enviados para o programa, saindo!\n");
    exit(0);
  }
  if (tmp<1 || tmp > 200) {
    tmp = TARGET_FPS;
    printf("W: sleep alterado para " PRETOSTRING(TARGET_FPS) " frames por segundo\n");
  } else {
    tmp = 1000.0/tmp;
  }
  s = spc_init(0,0,0,tmp);
  print_banner();

  while(!menu(s));

  spc_destroy(s);
  return 0;
}

#else
/*CODIGO MAIN PARA DEBUG :P */

int main(int argc, char** argv) {
  spaceship * s;
  s = spc_init(0,0,0,TARGET_FPS);
  /*surface_planner(s->moon);*/
  /*read_data_spec(s);*/
  game_engine(s, MODE_GRAPHIC);
  modo_graph("vooLunarCorrente.txt", 0,0);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,1);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,2);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,3);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,4);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,5);
  printf("Press a key to continue");
  modo_graph("vooLunarCorrente.txt", 0,6);
  printf("Press a key to continue");
  getchar();

  return 0;
}

#endif
