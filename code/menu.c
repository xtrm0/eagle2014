#include "../include/menu.h"

void read_data_spec(spaceship * s) {
  s->initialized |= 1;
  printf("Introduza os dados requisitados: \n");
  read_double("Introduza a massa do módulo (sem combustível) (Kg): ", &(s->mass_tara), COND_MASS_S);
  read_double("Introduza a massa de combustível do módulo (kg): ", &(s->mass_comb), COND_MASS_C);
  read_double("Altítude do centro de massa no início da alunagem (m): ", &(s->z), COND_ALTITUDE|COND_COORD);
  read_double("Distância horizontal do centro de massa no início da alunagem (m): ", &(s->x), COND_COORD);
  read_double("Velocidade vertical no início da alunagem (m/s): ", &(s->vz), COND_VELOC);
  read_double("Velocidade horizontal no início da alunagem (m/s): ", &(s->vx), COND_VELOC);
  read_double("Atitude do modulo no início da alunagem (rad): ", &(s->rot), COND_ANGLE);
}

int menu(spaceship * s) {
  char opcao, c;
  int t1, t2;
  spaceship * d;
  printf("\nSelecione uma opção:\n"
         "1. Especificação dos dados do módulo e das condições iniciais do voo.\n"
         "2. Simulação do voo em modo de “cockpit”.\n"
         "3. Apresentação em modo gráfico da trajectória do módulo.\n"
         "4. Definição do perfil da superfície lunar.\n"
         "5. Simulação do voo em modo gráfico.\n"
         "0. Sair\n"
         "Opção: ");
  c= opcao = getchar();
  /* Este while ignora whitespaces a seguir a opcao introduzida */
  while(c!='\n') {
    c=getchar();
    if (!isspace(c)) {
      clearbuffer();
      printf("Erro na leitura da opcao!\n");
      return 0;
    }
  }
  switch (opcao)
  {
    case '0':
      return 1;
    case '1':
      read_data_spec(s);
      break;
    case '2':
      if ((s->initialized & INIT_SURFACE) && !(s->initialized & INIT_LANDING)) {
        printf("Falta inicializar o plano de voo e/o a superficie lunar!");
        break;
      }
      d = _spc_copy(s);
      game_engine(d, MODE_COCKPIT);
      break;
    case '3':
      printf("O que deseja representar horizontalmente?\n");
      printf("0-tempo      |  3-velocidade horizontal  |  6-massa combustivel\n"
             "1-longitude  |  4-velocidade vertical    |                     \n"
             "2-altitude   |  5-atitude                |                     \n");
      read_int("opcao:", &t1, 0,6);
      printf("O que deseja representar verticalmente?\n");
      printf("0-tempo      |  3-velocidade horizontal  |  6-massa combustivel\n"
             "1-longitude  |  4-velocidade vertical    |                     \n"
             "2-altitude   |  5-atitude                |                     \n");
      read_int("opcao:", &t2, 0,6);
      modo_graph("vooLunarCorrente.txt",t1,t2);
      break;
    case '4':
      if (s->moon->lp_size!=0) {
        printf ("W: isto vai apagar todos os pontos de alunagem!\n Deseja continuar?");
        if (ask_yes_no()==0)
          break;
      }
      s->initialized |= surface_planner(s->moon);
      break;
    case '5':
      if (s->initialized & INIT_SPACESHIP && (!(s->initialized & INIT_SURFACE) || !(s->initialized & INIT_LANDING))) {
        printf("Falta inicializar o plano de voo e/o a superficie lunar!");
        break;
      }
      d = _spc_copy(s);
      game_engine(d, MODE_GRAPHIC);
      break;
    default:
      printf("Opção desconhecida.\n");
  }

  return 0;
}

void print_banner() {
  printf(" ________________________________________________________________ \n");
  printf("/                        |---------------------------------------|\n");
  printf("|    _  _____   _______  |---------------------------------------|\n");
  printf("|   / |/ / _ | / __/ _ | |---------------------------------------|\n");
  printf("|  /    / __ |_\\ \\/ __ | |---------------------------------------|\n");
  printf("| /_/|_/_/ |_/___/_/ |_| |---------------------------------------|\n");
  printf("|                        |---------------------------------------|\n");
  printf("|________________________/---------------------------------------|\n");
  printf("|----------------------------------------------------------------|\n");
  printf("|----------------------------------------------------------------|\n");
  printf("|----------------------------------------------------------------|\n");
  printf("|----------------------------------------------------------------|\n");
  printf("|----------------------------------------------------------------|\n");
  printf("|------------------------PROJECT-EAGLE2014-----------------------|\n");
  printf("|---------------------------TOP-SECRET---------------------------|\n");
  printf("\\----------------------------------------------------------------/\n");
  printf("\n\n");
  printf("          __.oOo.__                                               \n");
  printf("         /'(  _  )`\\           ____   __    ___  __    ____       \n");
  printf("        / . \\/^\\/ . \\         (  __) / _\\  / __)(  )  (  __)      \n");
  printf("       /  _)_`-'_(_  \\         ) _) /    \\( (_ \\/ (_/\\ ) _)       \n");
  printf("      /.-~   ).(   ~-.\\       (____)\\_/\\_/ \\___/\\____/(____)      \n");
  printf("     /'     /\\_/\\     `\\                                          \n");
  printf("   -=-=-=-=-\"-V-\"-=-=-=-=                                         \n");
  printf("\n");
}
