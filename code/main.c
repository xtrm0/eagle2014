#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(void) {
  spaceship * s;
//  pl_no * m = NULL;
  s = spc_init(0,0,0);
  print_banner();

  while(!menu(s));

  spc_destroy(s);
  return 0;
}

#else
/*CODIGO MAIN PARA DEBUG :P */

int main(void) {
  spaceship * s;
  s = spc_init(0,0,0);
  //surface_planner(s->moon);
  //read_data_spec(s);
  game_engine(s, MODE_GRAPHIC);
  modo_graph("vooLunarCorrente.txt", 0,1);
  printf("Press a key to continue");
  getchar();

  return 0;
}

#endif
