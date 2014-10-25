#include "../include/cockpit.h"

void gui_init(view * v) {
  //limpa o ecra:
  g2_clear(v->id);

  //desenha um retangulo:
  //TODO: editar isto para desenhar a seguir a camara ser desenhada o.o, de modo a tapar tudo o que for escrito fora da camara
  g2_pen(v->id, COLOR_GUI);
  g2_filled_rectangle(v->id, 0, 0, v->W, v->H);

  g2_pen(v->id, COLOR_BLACK);
  g2_set_font_size(v->id, COCK_FONT_SIZE);
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 1*COCK_PAD_VERT, "Atitude:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 2*COCK_PAD_VERT, "Altitude:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 3*COCK_PAD_VERT, "Distancia Horizontal:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 4*COCK_PAD_VERT, "Velocidade x:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 5*COCK_PAD_VERT, "Velocidade z:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 6*COCK_PAD_VERT, "Combustivel:");

  g2_set_font_size(v->id, COCK_FONT_SIZE);
  g2_string(v->id, COCK_SECOND_LEFT, v->H - COCK_TOP - 1*COCK_PAD_VERT, "F :");
  g2_string(v->id, COCK_SECOND_LEFT, v->H - COCK_TOP - 2*COCK_PAD_VERT, "F :");
  g2_set_font_size(v->id, COCK_FONT_SIZE/1.4);
  g2_string(v->id, COCK_SECOND_LEFT + 8, v->H - COCK_TOP - 1*COCK_PAD_VERT - 8, "r");
  g2_string(v->id, COCK_SECOND_LEFT + 8, v->H - COCK_TOP - 2*COCK_PAD_VERT - 8, "m");
  g2_set_font_size(v->id, COCK_FONT_SIZE);
}

void draw_gui(spaceship * s, camera2d * c, view * v) {
  char str[20];
  g2_pen(v->id, COLOR_GUI);




  g2_pen(v->id, COLOR_GUI);
  g2_filled_rectangle(v->id, 0, 0, c->vpos[0]-1, v->H-1);
  g2_filled_rectangle(v->id, c->vpos[0], 0, v->W, c->vpos[1]-1);
  g2_pen(v->id, COLOR_BLACK);
  g2_set_font_size(v->id, COCK_FONT_SIZE);
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 1*COCK_PAD_VERT, "Atitude:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 2*COCK_PAD_VERT, "Altitude:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 3*COCK_PAD_VERT, "Distancia Horizontal:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 4*COCK_PAD_VERT, "Velocidade x:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 5*COCK_PAD_VERT, "Velocidade z:");
  g2_string(v->id, COCK_LEFT, v->H - COCK_TOP - 6*COCK_PAD_VERT, "Combustivel:");



  g2_set_font_size(v->id, COCK_FONT_SIZE);
  g2_string(v->id, COCK_SECOND_LEFT, v->H - COCK_TOP - 1*COCK_PAD_VERT, "F :");
  g2_string(v->id, COCK_SECOND_LEFT, v->H - COCK_TOP - 2*COCK_PAD_VERT, "F :");
  g2_set_font_size(v->id, COCK_FONT_SIZE/1.4);
  g2_string(v->id, COCK_SECOND_LEFT + 8, v->H - COCK_TOP - 1*COCK_PAD_VERT - 8, "r");
  g2_string(v->id, COCK_SECOND_LEFT + 8, v->H - COCK_TOP - 2*COCK_PAD_VERT - 8, "m");
  g2_set_font_size(v->id, COCK_FONT_SIZE);

  g2_pen(v->id, COLOR_BLACK);
  g2_set_font_size(v->id, COCK_FONT_SIZE);

  //Lado direito das labels:
  sprintf(str, "%5.2lf" " \xb0", s->rot*180.0/(N_PI)); //Aqui tivemos de usar o valor em hexadecimal, porque o nosso editor de texto estava a guardar o caracter latino º
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 1*COCK_PAD_VERT, str);
  sprintf(str, "%5.2lf" " m", s->z);
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 2*COCK_PAD_VERT, str);
  sprintf(str, "%5.2lf" " m", s->x);
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 3*COCK_PAD_VERT, str);
  sprintf(str, "%5.2lf" " m/s", s->vx);
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 4*COCK_PAD_VERT, str);
  sprintf(str, "%5.2lf" " m/s", s->vz);
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 5*COCK_PAD_VERT, str);
  sprintf(str, "%5.2lf" " kg", s->mass_comb);
  g2_string(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 6*COCK_PAD_VERT, str);
  sprintf(str, "%3.2lf" " %%", s->fr * 100);
  g2_string(v->id, COCK_SECOND_LEFT + 30, v->H - COCK_TOP - 1*COCK_PAD_VERT, str);
  sprintf(str, "%3.2lf" " %%", s->ft * 100);
  g2_string(v->id, COCK_SECOND_LEFT + 30, v->H - COCK_TOP - 2*COCK_PAD_VERT, str);

}

int cockpit_loop() {
  struct timespec tstart, tend, tsleep, trem;
  view * v;
  spaceship * s;
  camera2d * c;
  button * btn_more_t, * btn_less_t, * btn_more_r, * btn_less_r;
  button * btn_pause, * btn_play, * btn_exit;
  polygon * pol;
  double aux[2] = {0};
  double deltatime, sleeptime;
  double fps = 60.0;
  double revfps = 1.0/fps;
  double * mouse_x, * mouse_y;
  double floor0[2]= {-1000.0, 0};
  double floor1[2]= {1000.0, 0};
  double floor0_p[2];
  double floor1_p[2];
  int * mouse_button;
  int runapp = 0;
  int resultado = 0;
  int mouse_last = 0, mouse_click=0;

  v = view_init(800, 300, "eagle2014 - Modo Cockpit");
  c = c2d_init(150, 150, 0, 0, 150, 150, 800-150, 300-150);
  s = spc_init(100, 15000, 0.0, v);
  btn_more_r  = btn_init(COCK_SECOND_LEFT + 160, v->H - COCK_TOP - 1.25*COCK_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, ">", 20.0, COLOR_WHITE);
  btn_less_r  = btn_init(COCK_SECOND_LEFT + 120, v->H - COCK_TOP - 1.25*COCK_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, "<", 20.0, COLOR_WHITE);
  btn_more_t  = btn_init(COCK_SECOND_LEFT + 120, v->H - COCK_TOP - 2.25*COCK_PAD_VERT, 30, 30, 10, 10, COLOR_BLACK, "+", 20.0, COLOR_WHITE);
  btn_less_t  = btn_init(COCK_SECOND_LEFT + 160, v->H - COCK_TOP - 2.25*COCK_PAD_VERT, 30, 30, 12, 10, COLOR_BLACK, "-", 20.0, COLOR_WHITE);
  btn_pause = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Pause", 20.0, COLOR_WHITE);
  btn_play = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Start", 20.0, COLOR_WHITE);
  btn_exit = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Sair", 20.0, COLOR_WHITE);
  mouse_x = malloc(sizeof(double));
  mouse_y = malloc(sizeof(double));
  mouse_button = malloc(sizeof(int));
  pol = poly();
  gui_init(v);

  clock_gettime(CLOCK_MONOTONIC, &tend);
  while (1) {
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    deltatime = (((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec) - ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec));
    //printf("%lf\n", deltatime);

    //Parte de input:
      g2_query_pointer(v->dev, mouse_x, mouse_y, mouse_button);
      mouse_click = (mouse_last & ((*mouse_button) ^ mouse_last));

    //Parte de logica:
      //atualiza a nave:
      if (runapp && !resultado) {
        spc_update_pos(s,deltatime);

        //colision detection:
        //TODO: implementar isto dentro do update_pos, pois queremos que se veja a posicao antes e depois e se faca uma colisao entre um prisma e um segmente de um plano que sao a versao extrudida da shape de colisao e da linha de chao, pelo tempo
        point(s->x, s->z, aux);
        poly_copy(s->colision_shape, pol);
        poly_rotate(pol, s->rot);
        poly_translate(pol, aux);
        if(poly_colide_lineseg(pol, floor0, floor1)) {
          if (s->rot > MAXROT || s->rot < 2*N_PI - MAXROT || s->vz > 0.01 || s->vx > 0.005 || s->vx < -0.005) {
            resultado = 1;
            printf("Alunagem completa sem sucesso.\n");
          } else {
            resultado = 2;
            printf("A missão foi um sucesso.\n");
          }
        }

        //atualiza a forca:
        if ((*mouse_button) & Button1MotionMask) {
          if(btn_hover(btn_more_t,*mouse_x,*mouse_y)) {
            s->ft+=0.25*deltatime;
          }
          if(btn_hover(btn_less_t,*mouse_x,*mouse_y)) {
            s->ft-=0.25*deltatime;
          }
          if(btn_hover(btn_more_r,*mouse_x,*mouse_y)) {
            s->fr+=0.25*deltatime;
          }
          if(btn_hover(btn_less_r,*mouse_x,*mouse_y)) {
            s->fr-=0.25*deltatime;
          }
        }

        //garante que a forca esta dentro do intervalo 0,1;
        if (s->fr<-1) s->fr=-1;
        if (s->fr>1) s->fr=1;
        if (s->ft<0) s->ft=0;
        if (s->ft>1) s->ft=1;
      }

      if (!resultado) {
        if (mouse_click & Button1MotionMask) { //Isto so acontece no loop em que se largou o botao direito do rato
          if(btn_hover(btn_pause,*mouse_x,*mouse_y)) {
            runapp = !runapp;
          }
        }
      } else {
        if (mouse_click & Button1MotionMask) { //Isto so acontece no loop em que se largou o botao direito do rato
          if(btn_hover(btn_pause,*mouse_x,*mouse_y)) {
            break; //sai do loop da simulacao
          }
        }
      }

    //Parte grafica:
    //garante que a camara esta solidaria com a nave:
    c->pos[0] = s->x - c->dim[0]/2.0;
    c->pos[1] = s->z - c->dim[1]/2.0;
    view_begin(v); //Garante que existe uma janela

      //Desenha o container da camara da nave
      g2_pen(v->id, COLOR_BLACK);
      g2_filled_rectangle(v->id, c->vpos[0], c->vpos[1], c->vpos[0] + c->vdim[0], c->vpos[1] + c->vdim[1]);
      g2_pen(v->id, COLOR_WHITE);
      g2_filled_rectangle(v->id, c->vpos[0]+1, c->vpos[1]+1, c->vpos[0] + c->vdim[0]-2, c->vpos[1] + c->vdim[1]-2);
      //TODO: Adicionar aqui algum efeito bonito

      //Desenha a nave, rodada (neste modo o referencial da camara é solidário com o da nave):
      project(floor0, c, floor0_p);
      project(floor1, c, floor1_p);
      g2_pen(v->id, COLOR_BLACK);
      g2_line(v->id,floor0_p[0],floor0_p[1],floor1_p[0],floor1_p[1]);
      spc_draw(s,c,v);

      draw_gui(s,c,v); //Atualiza o text na gui
      btn_draw(btn_more_r, v);
      btn_draw(btn_less_r, v);
      btn_draw(btn_more_t, v);
      btn_draw(btn_less_t, v);
      if (!resultado) {
        if (runapp) {
          btn_draw(btn_pause, v);
        } else {
          btn_draw(btn_play, v);
        }
      } else {
        btn_draw(btn_exit,v);
      }

    view_end(v); //Envia o buffer grafico escondido para o X11 desenhar na janela


    mouse_last = *mouse_button;
    clock_gettime(CLOCK_MONOTONIC, &tend);
    sleeptime = revfps - (((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    tend.tv_sec = tstart.tv_sec;
    tend.tv_nsec = tstart.tv_nsec;
    if (sleeptime > 0) {
       tsleep.tv_sec = (time_t) sleeptime;
       tsleep.tv_nsec = (time_t) ((sleeptime-tsleep.tv_sec)*10e8); //TODO: ISTO DEVIA SER 10e9, mas por algum motivo so da bem quando ponho 10e8. Temos de investigar
       nanosleep(&tsleep, &trem);
    }
  }
  view_destroy(v);
  printf("Saving simulation data to file...");
  spc_save_to_file(s);
  printf(" Done!\n");

  //TODO: Desalocar a memoria que falta desalocar:

  return 0;
}
