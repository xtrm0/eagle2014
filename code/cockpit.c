#include "../include/cockpit.h"

void draw_gui(spaceship * s, camera2d * c, view * v, int res) {
  char str[60];

  g2_pen(v->id, COLOR_GUI);
  g2_filled_rectangle(v->id, 0, 0, c->vpos[0]-1, v->H-1);
  g2_filled_rectangle(v->id, c->vpos[0], 0, v->W, c->vpos[1]-1);
  g2_pen(v->id, COLOR_BLACK);
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 1*COCKPIT_PAD_VERT, "Atitude:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 2*COCKPIT_PAD_VERT, "Altitude:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 3*COCKPIT_PAD_VERT, "Distancia Horizontal:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 4*COCKPIT_PAD_VERT, "Velocidade x:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 5*COCKPIT_PAD_VERT, "Velocidade z:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 6*COCKPIT_PAD_VERT, "Combustivel:");
  g2_string(v->id, COCKPIT_LEFT, v->H - COCKPIT_TOP - 7*COCKPIT_PAD_VERT, "Aterragem:");

  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/
  g2_string(v->id, COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 1*COCKPIT_PAD_VERT, "F :");
  g2_string(v->id, COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 2*COCKPIT_PAD_VERT, "F :");
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE/1.4);*/
  g2_string(v->id, COCKPIT_SECOND_LEFT + 8, v->H - COCKPIT_TOP - 1*COCKPIT_PAD_VERT - 8, "r");
  g2_string(v->id, COCKPIT_SECOND_LEFT + 8, v->H - COCKPIT_TOP - 2*COCKPIT_PAD_VERT - 8, "m");
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/

  g2_pen(v->id, COLOR_BLACK);
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/

  /*Lado direito das labels: */
  sprintf(str, "%5.2f" " \xb0", s->rot*180.0/(N_PI)); /*Aqui tivemos de usar o valor em hexadecimal, porque o nosso editor de texto estava a guardar o caracter latino º */
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 1*COCKPIT_PAD_VERT, str);
  sprintf(str, "%5.2f" " m", s->z);
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 2*COCKPIT_PAD_VERT, str);
  sprintf(str, "%5.2f" " m", s->x);
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 3*COCKPIT_PAD_VERT, str);
  sprintf(str, "%5.2f" " m/s", s->vx);
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 4*COCKPIT_PAD_VERT, str);
  sprintf(str, "%5.2f" " m/s", s->vz);
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 5*COCKPIT_PAD_VERT, str);
  sprintf(str, "%5.2f" " kg", s->mass_comb);
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 6*COCKPIT_PAD_VERT, str);
  sprintf(str, "%3.2f" " %%", s->fr * 100);
  g2_string(v->id, COCKPIT_SECOND_LEFT + 30, v->H - COCKPIT_TOP - 1*COCKPIT_PAD_VERT, str);
  sprintf(str, "%3.2f" " %%", s->ft * 100);
  g2_string(v->id, COCKPIT_SECOND_LEFT + 30, v->H - COCKPIT_TOP - 2*COCKPIT_PAD_VERT, str);

  switch(res) {
    case -1:
      sprintf(str, "Desastre");
      break;
    case 0:
      sprintf(str, "SUCESSO!!");
      break;
    default:
      sprintf(str, "Em progresso... (%d/%ld)", res-1, (unsigned long int)s->moon->lp_size);
      break;
  }
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 7*COCKPIT_PAD_VERT, str);
}

void draw_gui_graphic(spaceship * s, camera2d * c, view * v, int res) {
  char str[60];

  g2_pen(v->id, COLOR_BLACK);
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 1*GRAPHIC_PAD_VERT, "Atitude:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 2*GRAPHIC_PAD_VERT, "Altitude:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 3*GRAPHIC_PAD_VERT, "Distancia Horizontal:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 4*GRAPHIC_PAD_VERT, "Velocidade x:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 5*GRAPHIC_PAD_VERT, "Velocidade z:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 6*GRAPHIC_PAD_VERT, "Combustivel:");
  g2_string(v->id, GRAPHIC_LEFT, v->H - GRAPHIC_TOP - 7*GRAPHIC_PAD_VERT, "Aterragem:");

  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/
  g2_string(v->id, GRAPHIC_SECOND_LEFT, v->H - GRAPHIC_TOP - 1*GRAPHIC_PAD_VERT_2, "F :");
  g2_string(v->id, GRAPHIC_SECOND_LEFT, v->H - GRAPHIC_TOP - 2*GRAPHIC_PAD_VERT_2, "F :");
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE/1.4);*/
  g2_string(v->id, GRAPHIC_SECOND_LEFT + 8, v->H - GRAPHIC_TOP - 1*GRAPHIC_PAD_VERT_2 - 8, "r");
  g2_string(v->id, GRAPHIC_SECOND_LEFT + 8, v->H - GRAPHIC_TOP - 2*GRAPHIC_PAD_VERT_2 - 8, "m");
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/

  g2_pen(v->id, COLOR_BLACK);
  /*g2_set_font_size(v->id, COCKPIT_FONT_SIZE);*/

  /*Lado direito das labels: */
  sprintf(str, "%5.2f" " \xb0", s->rot*180.0/(N_PI)); /*Aqui tivemos de usar o valor em hexadecimal, porque o nosso editor de texto estava a guardar o caracter latino º */
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 1*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%5.2f" " m", s->z);
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 2*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%5.2f" " m", s->x);
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 3*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%5.2f" " m/s", s->vx);
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 4*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%5.2f" " m/s", s->vz);
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 5*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%5.2f" " kg", s->mass_comb);
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 6*GRAPHIC_PAD_VERT, str);
  sprintf(str, "%3.2f" " %%", s->fr * 100);
  g2_string(v->id, GRAPHIC_SECOND_LEFT + 30, v->H - GRAPHIC_TOP - 1*GRAPHIC_PAD_VERT_2, str);
  sprintf(str, "%3.2f" " %%", s->ft * 100);
  g2_string(v->id, GRAPHIC_SECOND_LEFT + 30, v->H - GRAPHIC_TOP - 2*GRAPHIC_PAD_VERT_2, str);

  switch(res) {
    case -1:
      sprintf(str, "Desastre");
      break;
    case 0:
      sprintf(str, "SUCESSO!!");
      break;
    default:
      sprintf(str, "Em progresso... (%d/%ld)", res-1, (unsigned long int)s->moon->lp_size);
      break;
  }
  g2_string(v->id, GRAPHIC_LEFT + GRAPHIC_HSPACE + GRAPHIC_PAD_HORZ, v->H - GRAPHIC_TOP - 7*GRAPHIC_PAD_VERT, str);
}

int game_engine(spaceship * s, unsigned int mode) {
  void * tmp;
  view * v;
  camera2d * c;
  button * btn_more_t, * btn_less_t, * btn_more_r, * btn_less_r;
  button * btn_pause, * btn_play, * btn_exit;
  gtimer * teemo;
  double deltatime;
  double * mouse_x, * mouse_y;
  moon_point floorp;
  unsigned int * mouse_button;
  int runapp = 0;
  int resultado = 1;
  int mouse_last = 0, mouse_click=0;
  int gameflag=1;
  if (mode & MODE_COCKPIT) {
    v = view_init(800, 300, "eagle2014 - Modo Cockpit");
    c = c2d_init(50, 50, 0, 0, 150, 150, 800-150, 300-150);
    g2_set_font_size(v->id, COCKPIT_FONT_SIZE);
  } else if (mode & MODE_GRAPHIC) {
    v = view_init(640, 600, "eagle2014 - Modo Grafico");
    c = c2d_init(640, 600, 0, 0, 640, 600, 0, 0);
    g2_set_font_size(v->id, GRAPHIC_FONT_SIZE);
  }

  if(((s->initialized) & INIT_SPACESHIP)==0) {
    fprintf(stderr, "W: Dados inicias da nave não definidos - usando valores predifinidos!\n");
    tmp = s;
    s = spc_init(0, 150, 0.0);
    free((spaceship *) tmp);
  }
  //TODO: caso nao esteja definido o plano de aterragem isto deve funcionar de outra forma
  if ((s->initialized & (INIT_SURFACE))==0) {
    fprintf(stderr, "W: Dados inicias da superficie lunar não definidos - usando plano horizontal!\n");
    sfc_destroy(s->moon);
    s->moon = sfc_init();
    floorp.c[0]=-100;
    floorp.c[1]=0;
    sprintf(floorp.name, "p1");
    sfc_add_point_back(s->moon, &floorp);
    floorp.c[0]=100;
    floorp.c[1]=0;
    sprintf(floorp.name, "p2");
    sfc_add_point_back(s->moon, &floorp);
    floorp.c[0]=200;
    floorp.c[1]=0;
    sprintf(floorp.name, "p3");
    sfc_add_point_back(s->moon, &floorp);
    sprintf(floorp.name, "p1");
    sfc_add_lp(s->moon, floorp.name);
  }
  s->moon->curr_lp = s->moon->lp->next;
  spc_init_model(s, v);

  if (mode & MODE_GRAPHIC) {
    btn_more_r  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, ">", 20.0, COLOR_WHITE);
    btn_less_r  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, "<", 20.0, COLOR_WHITE);
    btn_more_t  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 10, 10, COLOR_BLACK, "+", 20.0, COLOR_WHITE);
    btn_less_t  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 12, 10, COLOR_BLACK, "-", 20.0, COLOR_WHITE);
    btn_pause   = btn_init(COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Pause", 20.0, COLOR_WHITE);
    btn_play    = btn_init(COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Start", 20.0, COLOR_WHITE);
    btn_exit    = btn_init(COCKPIT_SECOND_LEFT + 100, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Sair" , 20.0, COLOR_WHITE);
  } else if (mode & MODE_COCKPIT) {
    btn_more_r  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, ">", 20.0, COLOR_WHITE);
    btn_less_r  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, "<", 20.0, COLOR_WHITE);
    btn_more_t  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 10, 10, COLOR_BLACK, "+", 20.0, COLOR_WHITE);
    btn_less_t  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 12, 10, COLOR_BLACK, "-", 20.0, COLOR_WHITE);
    btn_pause   = btn_init(COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Pause", 20.0, COLOR_WHITE);
    btn_play    = btn_init(COCKPIT_SECOND_LEFT, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Start", 20.0, COLOR_WHITE);
    btn_exit    = btn_init(COCKPIT_SECOND_LEFT + 100, v->H - COCKPIT_TOP - 3.5*COCKPIT_PAD_VERT, 90, 30, 20, 8, COLOR_BLACK, "Sair" , 20.0, COLOR_WHITE);
  }

  mouse_x = malloc(sizeof(double));
  mouse_y = malloc(sizeof(double));
  mouse_button = malloc(sizeof(unsigned int));
  TESTMEM(mouse_x);
  TESTMEM(mouse_y);
  TESTMEM(mouse_button);

  teemo = gtimer_init(TARGET_FPS, s->moon->arr_size, mode);
  while (gameflag) {
    deltatime = gtimer_begin(teemo);
//  printf("%f\n", deltatime);

    /*Parte de input: */
      g2_query_pointer(v->dev, mouse_x, mouse_y, mouse_button);
      mouse_click = (mouse_last & ((*mouse_button) ^ mouse_last));
//    printf("%d", *mouse_button);
    /*Parte de logica: */
      /*atualiza a nave: */
      if (runapp && resultado>0) {
        switch (spc_update_pos(s,deltatime)) {
          case 0:
            resultado = 0;
            printf("A missão foi um sucesso.\n");
            break;
          case 1:
            resultado = -1;
            printf("Alunagem completa sem sucesso (pois nao respeita as regras de alunagem).\n");
            break;
          case 2:
            resultado = -1;
            printf("Alunagem completa sem sucesso (pois aterrou fora de um ponto de alunagem).\n");
            break;
          default:
            break;
        }
        /*atualiza a forca: */
        if ((*mouse_button) & Button1MotionMask) {
          if(btn_hover(btn_more_t,*mouse_x,*mouse_y)) {
            s->ft+=0.20*deltatime;
          }
          if(btn_hover(btn_less_t,*mouse_x,*mouse_y)) {
            s->ft-=0.20*deltatime;
          }
          if(btn_hover(btn_more_r,*mouse_x,*mouse_y)) {
            s->fr+=0.20*deltatime;
          }
          if(btn_hover(btn_less_r,*mouse_x,*mouse_y)) {
            s->fr-=0.20*deltatime;
          }
        }

        /*garante que a forca esta dentro do intervalo 0,1; */
        if (s->fr<-1) s->fr=-1;
        if (s->fr>1) s->fr=1;
        if (s->ft<0) s->ft=0;
        if (s->ft>1) s->ft=1;
      }
      if (resultado>0) {
        if (mouse_click & Button1MotionMask) { /*Isto so acontece no loop em que se largou o botao direito do rato */
          if(!runapp && btn_hover(btn_exit,*mouse_x,*mouse_y)) {
            break;
          }
          if(btn_hover(btn_pause,*mouse_x,*mouse_y)) {
            runapp = !runapp;
          }
        }

      } else {
        if (mouse_click & Button1MotionMask) { /*Isto so acontece no loop em que se largou o botao direito do rato */
          if(btn_hover(btn_exit,*mouse_x,*mouse_y)) {
            break; /*sai do loop da simulacao */
          }
        }
      }
      if (mouse_click & KeyReleaseMask) {
        printf("Saindo do modo verboose!\n");
      }


    /*Parte grafica: */
    /*garante que a camara esta solidaria com a nave: */
    if (mode & MODE_COCKPIT) {
      c->pos[0] = s->x - c->dim[0]/2.0;
      c->pos[1] = s->z - c->dim[1]/2.0;
    } else {
      resize_camera_pts(s,c);
    }
    view_begin(v); /*Garante que existe uma janela */
      if (mode & MODE_COCKPIT) {
        g2_pen(v->id, COLOR_BLACK);
        g2_filled_rectangle(v->id, c->vpos[0], c->vpos[1], c->vpos[0] + c->vdim[0], c->vpos[1] + c->vdim[1]);
        g2_pen(v->id, COLOR_WHITE);
        g2_filled_rectangle(v->id, c->vpos[0]+4, c->vpos[1]+4, c->vpos[0] + c->vdim[0]-3, c->vpos[1] + c->vdim[1]-4);
      } else if (mode & MODE_GRAPHIC) {
        g2_pen(v->id, COLOR_WHITE);
        g2_filled_rectangle(v->id, c->vpos[0], c->vpos[1], c->vpos[0] + c->vdim[0], c->vpos[1] + c->vdim[1]);
        sfc_draw(s->moon,c,v);
        if (*mouse_button & KeyReleaseMask) { //Ver o que corresponde ao capslocks
          sfc_draw_labels(s->moon,c,v);
        }
      }
      /*Desenha a nave, rodada (neste modo o referencial da camara é solidário com o da nave): */
      spc_draw(s,c,v);
      if (mode & MODE_COCKPIT)
        draw_gui(s,c,v,resultado); /*Atualiza o text na gui */
      else if (mode & MODE_GRAPHIC)
        draw_gui_graphic(s,c,v,resultado); /*Atualiza o text na gui */
      btn_draw(btn_more_r, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_less_r, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_more_t, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_less_t, v, *mouse_x,*mouse_y, *mouse_button);


      if (resultado>0) {
        if (runapp) {
          btn_draw(btn_pause, v, *mouse_x,*mouse_y, *mouse_button);
        } else {
          btn_draw(btn_play, v, *mouse_x,*mouse_y, *mouse_button);
          btn_draw(btn_exit, v, *mouse_x,*mouse_y, *mouse_button);
        }
      } else {
        btn_draw(btn_exit, v, *mouse_x,*mouse_y, *mouse_button);
      }

    view_end(v); /*Envia o buffer grafico escondido para o X11 desenhar na janela */


    mouse_last = *mouse_button;
    gtimer_sleep(teemo);
  }
  view_destroy(v);
  printf("Saving simulation data to file...");
  spc_save_to_file(s);
  printf(" Done!\n");

  btn_destroy(btn_more_r);
  btn_destroy(btn_less_r);
  btn_destroy(btn_more_t);
  btn_destroy(btn_less_t);
  btn_destroy(btn_pause);
  btn_destroy(btn_play);
  btn_destroy(btn_exit);
  free(mouse_x);
  free(mouse_y);
  free(mouse_button);
  c2d_destroy(c);
  spc_destroy(s);
  gtimer_destroy(teemo);
  return 0;
}


void resize_camera_pts(spaceship * s, camera2d * c) {
  list_no * aux;
  moon_point * p;
  double p1[2] = {0};
  double p2[2] = {0};
  double tmp;
  double minz=MAX_COORD;
  aux = s->moon->arr;
  if (aux->next==NULL) {
    /*nao ha pontos, representa a linha y=0*/
    c2d_centerfit(c, s->x, (s->z)/2.0, 40, s->z);
    c2d_zoom(c, 1.10);
    return;
  }

  p = aux->next->val;
  p1[0] = p->c[0];
  p1[1] = p->c[1];

  /* eSTA QAUIQ UM ERRO QUE ACONTECE QUANDO ANDAMOS PARA A esquerda do 1 ponto (nao acontece com a direita do ultimo)
  */
  if (s->x <= p1[0] || aux->next==NULL) {
    minz = min(minz, p1[1]);
  }

  aux = aux->next;
  while (aux->next!=NULL) {
    p = aux->next->val;
    p1[0] = p->c[0];
    p1[1] = p->c[1];

    if (fabs(s->x - p1[0]) <= AUX_LINES_ZOOM) {
      minz = min(minz, p1[1]);
    }
    if (p1[0]-p2[0]>0.5) { //este 0.5 e para evitar division by 0
      if (p2[0] < s->x-AUX_LINES_ZOOM && p1[0] > s->x-AUX_LINES_ZOOM) {
        tmp = (p2[1]*(s->x-AUX_LINES_ZOOM-p2[0]) + p1[1]*(p1[0]-(s->x-AUX_LINES_ZOOM)))/(p1[0]-p2[0]);
        minz = min(minz, tmp);
      }
      if (p2[0] < s->x+AUX_LINES_ZOOM && p1[0] > s->x+AUX_LINES_ZOOM) {
        tmp = (p2[1]*(s->x+AUX_LINES_ZOOM-p2[0]) + p1[1]*(p1[0]-(s->x+AUX_LINES_ZOOM)))/(p1[0]-p2[0]);
        minz = min(minz, tmp);
      }
    }
    p2[0] = p1[0];
    p2[1] = p1[1];
    aux = aux->next;
  }

   if (s->x >= p1[0] || fabs(s->x - p1[0]) <= AUX_LINES_ZOOM) {
    minz = min(minz, p1[1]);
  }

  c2d_centerfit(c, s->x, (s->z+2*HEXRAD + minz)/2.0, 2*AUX_LINES_ZOOM, s->z - minz);
  c2d_zoom(c, 1.20);
  printf("%f %f %f %f %f\n",minz, c->pos[0], c->pos[1], c->dim[0], c->dim[1]);
}