#include "../include/menu.h"

void clearbuffer() {
  while(getchar()!='\n');
}

void read_int(char * prompt, int * target, int mini, int maxi) {
  begin_read_int:

  fputs(prompt, stdout);
  if (scanf("%d", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_int;
  }
  clearbuffer();
  if (*target < mini || *target > maxi) {
    printf("O número tem de estar entre %d e %d!\n", mini, maxi);
    goto begin_read_int;
  }
}

void read_double(char * prompt, double * target, unsigned int conditions) {
  begin_read_double:

  fputs(prompt, stdout);
  if (scanf("%lf", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_double;
  }
  clearbuffer();
  if (conditions & COND_BIGGERTHAN0) {
    if (*target < 0) {
      printf("Erro no formato especificado!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_SMALLRTHAN0) {
    if (*target > 0) {
      printf("Erro no formato especificado!\n");
      goto begin_read_double;
    }
  }
}

//@local
int menu_rds_compare (const void * a, const void * b){
  return ((*(double *) a) - (*(double *) b));
}

void read_data_spec(spaceship * s) {
  int i;
  int ponts;
  double p[2];
  polygon * pol;
  pol = poly();
  s->initialized = 1;
  printf("Introduza os dados requisitados: \n");
  read_double("Introduza a massa do módulo (sem combustível) (Kg): ", &(s->mass_tara), COND_BIGGERTHAN0);
  read_double("Altítude no início da alunagem (m): ", &(s->z), 0);
  read_double("Distância horizontal no início da alunagem (m): ", &(s->x), 0);
  read_double("Velocidade vertical no início da alunagem (m/s): ", &(s->vz), 0);
  read_double("Velocidade horizontal no início da alunagem (m/s): ", &(s->vx), 0);
  read_double("Atitude do modulo no início da alunagem (rad): ", &(s->rot), COND_ANGLERAD);

//TODO: Por tudo o que esta abaixo numa funcao so para o modo 2:
  read_int("Introduza a quantidade de pontos de alunagem: ", &ponts, 1, 1000000);
  for (i=0; i<ponts; i++) {
    printf("Ponto %d:\n", i);
    read_double("Introduza a coordenada x do inicio do ponto de alunagem: ", &p[0], 0);
    printf("Iremos usar a coordenada z=0.0 nesta fase intermédia\n"); //Pois ainda nao definimos a superficie lunar
    p[1]=0.0;
    poly_push(pol, p);
    read_double("Introduza a coordenada x do fim do ponto de alunagem: ", &p[0], 0);
    printf("Iremos usar a coordenada z=0.0 nesta fase intermédia\n"); //Pois ainda nao definimos a superficie lunar
    p[1]=0.0;
    poly_push(pol, p);
  }
  qsort(pol, ponts, sizeof(double)*4, menu_rds_compare);
  //adiciona os pontos ao poligono mesmo da nave
  p[0] = -100000;
  p[1] = 0.0;
  sfc_add_point(s->moon, p);
  for (i=0; i<ponts; i++) {
    sfc_add_lp(s->moon, 1+2*i);
    sfc_add_point(s->moon, pol->pts + 4*i);
    sfc_add_point(s->moon, pol->pts + 4*i+2); //Ha um erro deste genero no draw_graph
  }
  p[0] = 100000;
  p[1] = 0.0;
  sfc_add_point(s->moon, p);
  poly_destroy(pol);
}

int menu(spaceship * s) {
  char opcao;

  printf("1. Especificação dos dados do módulo e das condições iniciais do voo.\n");
  printf("2. Simulação do voo em modo de “cockpit”.\n");
  printf("3. Apresentação em modo gráfico da trajectória do módulo.\n");
  printf("4. Definição do perfil da superfície lunar.\n");
  printf("5. Simulação do voo em modo gráfico.\n");
  printf("Opção: ");
  opcao = getchar();
  if (opcao!='\n') clearbuffer();

  switch (opcao)
  {
    case '0':
      return 1;
    case '1':
      read_data_spec(s);
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    case '5':
      break;
    break;
      default:
      printf("Opção desconhecida.");
  }

  return 0;
}
