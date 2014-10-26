#ifndef COCKPIT_H
#define COCKPIT_H
#include "../include/spaceship.h"
#include "../include/button.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>


/*
  Estamos a usar muitos defines para facilitar fazer alteracoes no design
  Não tem problema as somas, porque o gcc substitui por um so valor inteiro ao compilar
  TODO: Mudar os nomes das variaveis
*/
#define COCKPIT_FONT_SIZE 20
#define COCKPIT_TOP  0
#define COCKPIT_LEFT 50
#define COCKPIT_PAD_VERT (COCKPIT_FONT_SIZE + 20)
#define COCKPIT_PAD_HORZ 20
#define COCKPIT_HSPACE 180
#define COCKPIT_SECOND_LEFT 400


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
int modo_cockpit(spaceship * s);



//desenha o texto e o background da interface grafica
void draw_gui(spaceship * s, camera2d * c, view * v, int res);


#endif
