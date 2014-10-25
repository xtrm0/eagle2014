#include "../include/menu.h"
#include "../include/spaceship.h"

#ifndef _DEBUG

int main(void) {
  while(!menu());

  return 0;
}

#else
//CODIGO MAIN PARA DEBUG :P

int main(void) {
  cockpit_loop();
  modo_graph ("vooLunarCorrente.txt");
  printf("Press a key to continue");
  getchar();
  return 0;
}



#endif
