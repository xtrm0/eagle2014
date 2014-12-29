#ifndef COCKPIT_H
#define COCKPIT_H
#include "../include/spaceship.h"
#include "../include/button.h"
#include "../include/gtimer.h"
#include <stdio.h>
#include <time.h>

#define TARGET_FPS 60.0

/*
  Defines para design:
  Estamos a usar muitos defines para facilitar fazer alteracoes no design
  Não tem problema as somas, porque o gcc substitui por um so valor inteiro ao compilar
*/
#define COCKPIT_FONT_SIZE 20
#define COCKPIT_TOP  0
#define COCKPIT_LEFT 50
#define COCKPIT_PAD_VERT (COCKPIT_FONT_SIZE + 20)
#define COCKPIT_PAD_HORZ 20
#define COCKPIT_HSPACE 180
#define COCKPIT_SECOND_LEFT 400

#define GRAPHIC_FONT_SIZE 12
#define GRAPHIC_TOP  15
#define GRAPHIC_LEFT 20
#define GRAPHIC_PAD_VERT (GRAPHIC_FONT_SIZE + 5)
#define GRAPHIC_PAD_VERT_2 30
#define GRAPHIC_PAD_HORZ 20
#define GRAPHIC_HSPACE 120
#define GRAPHIC_SECOND_LEFT 400

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
int game_engine(spaceship * s, unsigned int mode);



/*desenha o texto e o background da interface grafica, no modo 2*/
void draw_gui(spaceship * s, camera2d * c, view * v, int res);
/*desenha o texto e o background da interface grafica, no modo 5*/
void draw_gui_graphic(spaceship * s, camera2d * c, view * v, int res);

/* 
Explicacao do resize_camera_pts()
	Tem de ter pelo menos 40 de width
	Tem aspect ratio constante
	A nave tem de estar a uma distancia f(height) do topo da camara (diminui com a altura) e estar centrada horizontalmente
	Tem de conter todos os pedacos de aresta que estao dentro da secao de plano definia pelas retas verticais a 20 da nave:  ______
		  |  ::  |
		  |   _  |
		  | _/ \_|
		  |/_____|
	Depois disso, faz-se um zoomout de 5%
	Algoritmo:
			1) Desenhar as 2 retas e interceptar com o chao
			2) Calcular o minimo das coordendas y dos pontos entre as intercepcoes e os pontos nelas. Temos ymin
			3) heigth = max(30, nave.y - ymin)
			4) width  = heigth
			5) xmin   = nave.x - width/2
			6) zoomout(5%);
	Temos o retangulo da camara definido
*/
void resize_camera_pts(spaceship * s, camera2d * c);
#endif
