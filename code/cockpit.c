#include "../include/cockpit.h"

void draw_gui(spaceship * s, camera2d * c, view * v, int res) {
  char str[20];
  g2_pen(v->id, COLOR_GUI);

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
    case 0:
    sprintf(str, "Em progresso...");
    break;
    case 1:
    sprintf(str, "Desastre");
    break;
    case 2:
    sprintf(str, "SUCESSO!!");
    break;
  }
  g2_string(v->id, COCKPIT_LEFT + COCKPIT_HSPACE + COCKPIT_PAD_HORZ, v->H - COCKPIT_TOP - 7*COCKPIT_PAD_VERT, str);
}

int modo_cockpit(spaceship * s) {
  void * tmp;
  view * v;
  camera2d * c;
  button * btn_more_t, * btn_less_t, * btn_more_r, * btn_less_r;
  button * btn_pause, * btn_play, * btn_exit;
  polygon * pol;
  gtimer * teemo;
  double aux[2] = {0};
  double deltatime;
  double * mouse_x, * mouse_y;
  double floor0[2]= {-10000.0, 0};
  double floor1[2]= {10000.0, 0};
  double tmpp[4]={-100,0,100,0};
  double floor0_p[2];
  double floor1_p[2];
  unsigned int * mouse_button;
  int runapp = 0;
  int resultado = 0;
  int mouse_last = 0, mouse_click=0;
  v = view_init(800, 300, "eagle2014 - Modo Cockpit");
  c = c2d_init(50, 50, 0, 0, 150, 150, 800-150, 300-150);
  g2_set_font_size(v->id, COCKPIT_FONT_SIZE);

  if(!(s->initialized)) {
    fprintf(stderr, "W: Dados inicias não definidos - usando valores predifinidos!\n");
    tmp = s;
    s = spc_init(0, 150, 0.0);
    free((spaceship *) tmp);
    sfc_add_point(s->moon, floor0);
    sfc_add_point(s->moon, tmpp);
    sfc_add_point(s->moon, tmpp+2);
    sfc_add_point(s->moon, floor1);
    sfc_add_lp(s->moon, 1);
  }
  spc_init_model(s, v);
  btn_more_r  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, ">", 20.0, COLOR_WHITE);
  btn_less_r  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 1.25*COCKPIT_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, "<", 20.0, COLOR_WHITE);
  btn_more_t  = btn_init(COCKPIT_SECOND_LEFT + 120, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 10, 10, COLOR_BLACK, "+", 20.0, COLOR_WHITE);
  btn_less_t  = btn_init(COCKPIT_SECOND_LEFT + 160, v->H - COCKPIT_TOP - 2.25*COCKPIT_PAD_VERT, 30, 30, 12, 10, COLOR_BLACK, "-", 20.0, COLOR_WHITE);
  btn_pause = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Pause", 20.0, COLOR_WHITE);
  btn_play = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Start", 20.0, COLOR_WHITE);
  btn_exit = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Sair", 20.0, COLOR_WHITE);

  mouse_x = malloc(sizeof(double));
  mouse_y = malloc(sizeof(double));
  mouse_button = malloc(sizeof(unsigned int));
  TESTMEM(mouse_x);
  TESTMEM(mouse_y);
  TESTMEM(mouse_button);
  pol = poly();

  teemo = gtimer_init(TARGET_FPS);
  while (1) {
    deltatime = gtimer_begin(teemo);
    /*printf("%f\n", deltatime); */

    /*Parte de input: */
      g2_query_pointer(v->dev, mouse_x, mouse_y, mouse_button);
      mouse_click = (mouse_last & ((*mouse_button) ^ mouse_last));

    /*Parte de logica: */
      /*atualiza a nave: */
      if (runapp && !resultado) {
        spc_update_pos(s,deltatime);

        /*colision detection: */
        /*TODO: implementar isto dentro do update_pos, pois queremos que se veja a posicao antes e depois e se faca uma colisao entre um prisma e um segmente de um plano que sao a versao extrudida da shape de colisao e da linha de chao, pelo tempo */
        point(s->x, s->z, aux);
        poly_copy(s->colision_shape, pol);
        poly_rotate(pol, s->rot);
        poly_translate(pol, aux);
        if(poly_colide_lineseg(pol, floor0, floor1) || s->z <= 13) { /*A segunda condição serve para evitar colision escape para velocidades muito rapidas*/
          switch (spc_unsafe_landing(s)) {
            case 0:
              resultado = 2;
              printf("A missão foi um sucesso.\n");
              break;
            case 1:
              resultado = 1;
              printf("Alunagem completa sem sucesso (pois nao respeita as regras de aterragem).\n");
              break;
            case 2:
              resultado = 1;
              printf("Alunagem completa sem sucesso (pois aterrou fora de um ponto de alunagem).\n");
              break;
          }
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

      if (!resultado) {
        if (mouse_click & Button1MotionMask) { /*Isto so acontece no loop em que se largou o botao direito do rato */
          if(btn_hover(btn_pause,*mouse_x,*mouse_y)) {
            runapp = !runapp;
          }
        }
      } else {
        if (mouse_click & Button1MotionMask) { /*Isto so acontece no loop em que se largou o botao direito do rato */
          if(btn_hover(btn_pause,*mouse_x,*mouse_y)) {
            break; /*sai do loop da simulacao */
          }
        }
      }

    /*Parte grafica: */
    /*garante que a camara esta solidaria com a nave: */
    c->pos[0] = s->x - c->dim[0]/2.0;
    c->pos[1] = s->z - c->dim[1]/2.0;
    view_begin(v); /*Garante que existe uma janela */

      /*Desenha o container da camara da nave */
      g2_pen(v->id, COLOR_BLACK);
      g2_filled_rectangle(v->id, c->vpos[0], c->vpos[1], c->vpos[0] + c->vdim[0], c->vpos[1] + c->vdim[1]);
      g2_pen(v->id, COLOR_WHITE);
      g2_filled_rectangle(v->id, c->vpos[0]+4, c->vpos[1]+4, c->vpos[0] + c->vdim[0]-3, c->vpos[1] + c->vdim[1]-4);
      /*TODO: Adicionar aqui algum efeito bonito */

      /*Desenha o chao: */
      sfc_draw(s->moon,c,v);
      /*Desenha a nave, rodada (neste modo o referencial da camara é solidário com o da nave): */
      g2_pen(v->id, COLOR_BLACK);
      g2_line(v->id,floor0_p[0],floor0_p[1],floor1_p[0],floor1_p[1]);
      spc_draw(s,c,v);

      draw_gui(s,c,v,resultado); /*Atualiza o text na gui */
      btn_draw(btn_more_r, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_less_r, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_more_t, v, *mouse_x,*mouse_y, *mouse_button);
      btn_draw(btn_less_t, v, *mouse_x,*mouse_y, *mouse_button);
      if (!resultado) {
        if (runapp) {
          btn_draw(btn_pause, v, *mouse_x,*mouse_y, *mouse_button);
        } else {
          btn_draw(btn_play, v, *mouse_x,*mouse_y, *mouse_button);
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
  poly_destroy(pol);
  spc_destroy(s);
  gtimer_destroy(teemo);
  return 0;
}
