#ifndef _SURFACE_PLANNER_H
#define _SURFACE_PLANNER_H
#include "../include/surface.h"
#include "../include/fuioutil.h"
#include <limits.h>
/*
	Redesenha a janela
*/
void s_p_update_window(surface * s, camera2d * c, view * v);
/*
	Le um moon_point
*/
void read_mp(moon_point * p, surface * s);
/*
	Todos os passos do menu
*/
int surface_planner_menu(surface * s);
/*
	Loop principial, e esta funcao que deve ser chamada pelo main
	Esta funcao tem o objetivo de definir a superficie lunar e/ou a sequencia de aterragem
	Quando esta funcao e chamada, ela carrega de um ficheiro todos os pontos de alunagem e, caso o ficheiro nao esteja vazio, apaga a sequencia de alunagem do ficheiro
*/
int surface_planner(surface * s);
#endif