#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(void) {
  spaceship * s = NULL;
  while(!menu());

  return 0;
}

#else
//CODIGO MAIN PARA DEBUG :P

int main(void) {
  spaceship * s;
  surface * moon;
  s = spc_init(0,0,0);
  //read_data_spec(s);
  modo_cockpit(s);
  modo_graph ("vooLunarCorrente.txt");
  printf("Press a key to continue");
  getchar();
  return 0;
}



#endif
