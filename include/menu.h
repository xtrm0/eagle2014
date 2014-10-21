#ifndef MENU_H
#define MENU_H
#include <stdio.h>
/*
  Menu do programa - Serve para mostar o menu
*/



/*
  void clearbuffer(void)
  Limpa o buffer ate ao proximo '\n'
*/
void clearbuffer();


/*
  Mostra o menu
  returns:
    non-zero to end the program
    zero otherwise
*/
int menu(void);

#endif
