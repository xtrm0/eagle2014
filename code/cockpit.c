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

void draw_gui(spaceship * s, view * v) {
  char str[20];
  g2_pen(v->id, COLOR_GUI);
  g2_filled_rectangle(v->id, COCK_LEFT + COCK_HSPACE + COCK_PAD_HORZ, v->H - COCK_TOP - 7*COCK_PAD_VERT, COCK_SECOND_LEFT-1, v->H);
  g2_filled_rectangle(v->id, COCK_SECOND_LEFT + 30, v->H - COCK_TOP - 7*COCK_PAD_VERT, v->W, v->H);


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
  button * btn_pause;
  double deltatime, sleeptime;
  double fps = 60.0;
  double revfps = 1.0/fps;
  double * mouse_x, * mouse_y;
  int * mouse_button;
  int runapp;


  v = view_init(800, 300, "eagle2014 - Modo Cockpit");
  c = c2d_init(150, 150, 0, 0, 150, 150, 800-150, 300-150);
  s = spc_init(100, 200, 0.0, v);
  btn_more_r  = btn_init(COCK_SECOND_LEFT + 160, v->H - COCK_TOP - 1.25*COCK_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, ">", 20.0, COLOR_WHITE);
  btn_less_r  = btn_init(COCK_SECOND_LEFT + 120, v->H - COCK_TOP - 1.25*COCK_PAD_VERT, 30, 30, 8, 10, COLOR_BLACK, "<", 20.0, COLOR_WHITE);
  btn_more_t  = btn_init(COCK_SECOND_LEFT + 120, v->H - COCK_TOP - 2.25*COCK_PAD_VERT, 30, 30, 10, 10, COLOR_BLACK, "+", 20.0, COLOR_WHITE);
  btn_less_t  = btn_init(COCK_SECOND_LEFT + 160, v->H - COCK_TOP - 2.25*COCK_PAD_VERT, 30, 30, 12, 10, COLOR_BLACK, "-", 20.0, COLOR_WHITE);
  btn_pause = btn_init(400, 110, 90, 30, 20, 8, COLOR_BLACK, "Pause", 20.0, COLOR_WHITE);

  mouse_x = malloc(sizeof(double));
  mouse_y = malloc(sizeof(double));
  mouse_button = malloc(sizeof(int));
  gui_init(v);
  runapp = 1;

  clock_gettime(CLOCK_MONOTONIC, &tend);
  while (runapp) {
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    deltatime = (((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec) - ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec));
    //printf("%lf\n", deltatime);

    //Parte de input:
      g2_query_pointer(v->dev, mouse_x, mouse_y, mouse_button);
      printf("mouse_button: 0x%04x = %08o (oct)\n", *mouse_button, *mouse_button);
    //Parte de logica:
      //atualiza a nave:
      spc_update_pos(s,deltatime);

      //atualiza a forca:
      if (((*mouse_button)/256)%2 == 1) { //INFO: O rato esta clicado quando o 9bit for 1
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

      //garante que a camara esta solidaria com a nave:
      c->pos[0] = s->x - c->dim[0]/2.0;
      c->pos[1] = s->z - c->dim[1]/2.0;

    //Parte grafica
    view_begin(v); //Garante que existe uma janela
      draw_gui(s,v); //Atualiza o text na gui
      btn_draw(btn_more_r, v);
      btn_draw(btn_less_r, v);
      btn_draw(btn_more_t, v);
      btn_draw(btn_less_t, v);
      btn_draw(btn_pause, v);
      //Desenha o container da camara da nave
      g2_pen(v->id, COLOR_BLACK);
      g2_filled_rectangle(v->id, c->vpos[0], c->vpos[1], c->vpos[0] + c->vdim[0], c->vpos[1] + c->vdim[1]);
      g2_pen(v->id, COLOR_WHITE);
      g2_filled_rectangle(v->id, c->vpos[0]+1, c->vpos[1]+1, c->vpos[0] + c->vdim[0]-2, c->vpos[1] + c->vdim[1]-2);
      //TODO: Adicionar aqui algum efeito bonito

      //Desenha a nave, rodada (neste modo o referencial da camara é solidário ao da nave):
      spc_draw(s,c,v);
    view_end(v); //Envia o buffer grafico escondido para o X11 desenhar na janela



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
  spc_save_to_file(s);
  return 0;
}
