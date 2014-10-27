#include "../include/menu.h"

void clearbuffer() {
  while(getchar()!='\n');
}

void read_int(char * prompt, int * target, int mini, int maxi) {
  char c;
  begin_read_int:

  fputs(prompt, stdout);
  if (scanf("%d", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_int;
  }
  while((c=getchar())!='\n') {
    if (!isspace(c)) {
      clearbuffer();
      printf("Erro no formato especificado: Não coloque caracteres depois do numero!\n");
      goto begin_read_int;
    }
  }
  if (*target < mini || *target > maxi) {
    printf("O número tem de estar entre %d e %d!\n", mini, maxi);
    goto begin_read_int;
  }
}

void read_double(char * prompt, double * target, unsigned int conditions) {
  char c;
  begin_read_double:

  fputs(prompt, stdout);
  if (scanf("%lf", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_double;
  }
  while((c=getchar())!='\n') {
    if (!isspace(c)) {
      clearbuffer();
      printf("Erro no formato especificado: Não coloque unidades!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_BIGGERTHAN0) {
    if (*target < 0) {
      printf("Introduza um valor positivo!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_BIGGERTHAN100) {
    if (*target < 0) {
      printf("Introduza um valor superior a 100!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_SMALLRTHAN0) {
    if (*target > 0) {
      printf("Introduza um valor negativo!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_ALTITUDE) {
    if (*target < 44.4) {
      printf("Altitude inicial da nave muito baixa!\n");
      goto begin_read_double;
    }
  }
}


void read_data_spec(spaceship * s) {
  int i;
  int ponts;
  double p[2];
  double tmp;
  polygon * pol;
  pol = poly();
  s->initialized = 1;
  printf("Introduza os dados requisitados: \n");
  read_double("Introduza a massa do módulo (sem combustível) (Kg): ", &(s->mass_tara), COND_BIGGERTHAN100);
  read_double("Introduza a massa de combustível do módulo (kg): ", &(s->mass_comb), COND_BIGGERTHAN100);
  read_double("Altítude do centro de massa no início da alunagem (m): ", &(s->z), COND_ALTITUDE);
  read_double("Distância horizontal do centro de massa no início da alunagem (m): ", &(s->x), 0);
  read_double("Velocidade vertical no início da alunagem (m/s): ", &(s->vz), 0);
  read_double("Velocidade horizontal no início da alunagem (m/s): ", &(s->vx), 0);
  read_double("Atitude do modulo no início da alunagem (rad): ", &(s->rot), COND_ANGLERAD);

/*TODO: Por tudo o que esta abaixo numa funcao so para o modo 2: */
  read_int("Introduza a quantidade de pontos de alunagem: ", &ponts, 1, 1000000);
  for (i=0; i<ponts; i++) {
    printf("Ponto %d:\n", i);
    read_double("Introduza a coordenada x do inicio do ponto de alunagem: ", &p[0], 0);
    printf("Iremos usar a coordenada z=0.0 nesta fase intermédia\n"); /*Pois ainda nao definimos a superficie lunar */
    p[1]=0.0;
    poly_push(pol, p);
    read_double("Introduza a coordenada x do fim do ponto de alunagem: ", &p[0], 0);
    printf("Iremos usar a coordenada z=0.0 nesta fase intermédia\n"); /*Pois ainda nao definimos a superficie lunar */
    p[1]=0.0;
    poly_push(pol, p);
    if (pol->pts[2*pol->size-2] > pol->pts[2*pol->size-4]) {
      /*faz os swap dos pontos, de modo a garantir que estao por ordem crescente (é importante porque o sort so tem em conta o primeiro ponto) */
      tmp = pol->pts[2*pol->size-2];
      pol->pts[2*pol->size-2] = pol->pts[2*pol->size-4];
      pol->pts[2*pol->size-4] = tmp;
      tmp = pol->pts[2*pol->size-1];
      pol->pts[2*pol->size-1] = pol->pts[2*pol->size-3];
      pol->pts[2*pol->size-3] = tmp;
    }
  }
  qsort(pol, ponts, sizeof(double)*4, double_increasing);
  /*adiciona os pontos ao poligono mesmo da nave */
  p[0] = -100000;
  p[1] = 0.0;
  sfc_add_point(s->moon, p);
  for (i=0; i<ponts; i++) {
    sfc_add_lp(s->moon, 1+2*i);
    sfc_add_point(s->moon, pol->pts + 4*i);
    sfc_add_point(s->moon, pol->pts + 4*i+2); /*Ha um erro deste genero no draw_graph */
  }
  p[0] = 100000;
  p[1] = 0.0;
  sfc_add_point(s->moon, p);
  poly_destroy(pol);
}

int menu(spaceship * s) {
  char opcao, c;
  spaceship * d;
  printf("\nSelecione uma opção:\n");
  printf("1. Especificação dos dados do módulo e das condições iniciais do voo.\n");
  printf("2. Simulação do voo em modo de “cockpit”.\n");
  printf("3. Apresentação em modo gráfico da trajectória do módulo.\n");
  printf("4. Definição do perfil da superfície lunar.\n");
  printf("5. Simulação do voo em modo gráfico.\n");
  printf("Opção: ");
  c= opcao = getchar();
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
      d = _spc_copy(s);
      modo_cockpit(d);
      break;
    case '3':
      modo_graph("vooLunarCorrente.txt");
      break;
    case '4':
      printf("EM CONSTRUÇÃO");
      break;
    case '5':
      printf("EM CONSTRUÇÃO");
      break;
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
