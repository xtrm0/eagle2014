#ifndef _SURFACE_PLANNER_H
#define _SURFACE_PLANNER_H
#include "../include/surface.h"
#include "../include/fuioutil.h"
#include <limits.h>
void s_p_update_window(surface * s, camera2d * c, view * v);

void read_mp(moon_point * p, surface * s);

int surface_planner_menu(surface * s);

int surface_planner(surface * s);
#endif