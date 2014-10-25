#ifndef MENU_H
#define MENU_H
#include "../include/spaceship.h"
#include "../include/button.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//5 graus:
#define MAXROT 0.0872664626

/*
  Estamos a usar muitos defines para facilitar fazer alteracoes no design
  Não tem problema as somas, porque o gcc substitui por um so valor inteiro ao compilar
  TODO: Utilizar mesmo isto
*/
#define COCK_FONT_SIZE 20
#define COCK_TOP  10
#define COCK_LEFT 50
#define COCK_PAD_VERT (COCK_FONT_SIZE + 20)
#define COCK_PAD_HORZ 20
#define COCK_HSPACE 180
#define COCK_SECOND_LEFT 400


#define COCK_VALUES_LEFT
/*
  Modo cockpit - Representa o modo cockpit do programa e todas as funcoes de simulacao deste
*/

/*
  Faz o loop do modo cockpit
  arguments:

  returns:
    zero se nao ocorreu nenhum erro critico
    non-zero para terminar o programa
*/
void draw_gui();

int cockipt_loop();


#endif
