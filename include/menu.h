#ifndef MENU_H
#define MENU_H
#include "../include/spaceship.h"
#include "../include/cockpit.h"
#include "../include/grafico.h"
#include <stdio.h>
#include <ctype.h>


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
  Imprime o cabecalho que se ve quando se abre o programa
*/
void print_banner();

/*
  Le um double do teclado

  Nao desiste enquando nao tiver um double na forma valida
  O ultimo argumento e recebi como bitmask
*/
#define COND_BIGGERTHAN0 (1<<0)
#define COND_SMALLRTHAN0 (1<<1)
#define COND_ANGLERAD (1<<2)
#define COND_ALTITUDE (1<<3)
#define COND_BIGGERTHAN100 (1<<4)
void read_double(char *, double *, unsigned int);

/*
  Le um inteiro do teclado

  Nao desiste enquando nao tiver um inteiro na forma valida
*/
void read_int(char * prompt, int * target, int mini, int maxi);


#endif
