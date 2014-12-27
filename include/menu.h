#ifndef MENU_H
#define MENU_H
#include "../include/spaceship.h"
#include "../include/cockpit.h"
#include "../include/grafico.h"
#include "../include/fuioutil.h"
#include "../include/surface_planner.h"
#include <stdio.h>
#include <ctype.h>


/*
  Menu do programa - Serve para mostar o menu
*/

/*
  Mostra o menu
  returns:
    non-zero to end the program
    zero otherwise
*/
int menu(spaceship * s);

/*
 Le os dados do modulo e as condicoes iniciais de voo
*/
void read_data_spec();

/*
  Imprime o cabecalho que se ve quando se abre o programa
*/
void print_banner();



#endif
