#ifndef MENU_H
#define MENU_H
#include "../include/spaceship.h"
#include <stdio.h>
#define COND_BIGGERTHAN0 (1<<0)
#define COND_SMALLRTHAN0 (1<<1)
#define COND_ANGLERAD (1<<2)

#
/*
  Menu do programa - Serve para mostar o menu
  Definimos aqui todas as funcoes relacionadas com input e output pela consola
*/

/*
  Mostra o menu
  returns:
    non-zero to end the program
    zero otherwise
*/
int menu(spaceship * s);

/*
  void clearbuffer(void)
  Limpa o buffer ate ao proximo '\n'
*/
void clearbuffer();


/*
 Le os dados do modulo e as condicoes iniciais de voo
*/
void read_data_spec();

/*
  Le um double do teclado
*/
void read_double(char *, double *, unsigned int);



#endif
