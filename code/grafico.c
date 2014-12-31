#include "../include/grafico.h"

graph * graph_init(double W, double H, int t1, int t2, int b_color, int p_color, int axisl_color, int axisv_color, int axisn_color) {
  graph * g = malloc(sizeof(graph));
  TESTMEM(g);
  g->data = poly();
  /* Inicializamos estes valores assim para garantir que nunca e pedido para representar o grafico de dimensoes 0, e que a origem esta sempre presente*/
  g->max_x = 0.001;
  g->min_x = -0.001;
  g->max_y = 0.001;
  g->min_y = -0.001;
  g->c = c2d_init(0,0,0,0,W,H,0,0);
  g->v = view_init(W,H,"eagle2014 - Ver Grafico");
  g->p_color = p_color;
  g->b_color = b_color;
  g->t1=t1;
  g->t2=t2;
  g->axisl_color = axisl_color;
  g->axisv_color = axisv_color;
  g->axisn_color = axisn_color;
  return g;
}

void graph_destroy(graph * g){
  if(g!=NULL) {
    poly_destroy(g->data);
    c2d_destroy(g->c);
    view_destroy(g->v);
    free(g);
  }
}

int graph_load_points_from_file (char *nome, graph * g, int t1, int t2) {
  double massa=0;
  double o[7];
  char tmp;
  FILE * fin;
  double p[2]= {0};
  char line[301]; /*estamos a dar um valor muito alto para deixar o usar criar o ficheiro à mão. idealmente o tamanho strlen(FILE_HEADLINE)+2 */
  if ((fin = fopen(nome, "r")) == NULL) {
    fprintf(stderr, "E: Não foi possível abrir o ficheiro");
    return 1;
  }
  poly_destroy(g->data);
  g->data = poly();

  if (fgets(line, 300, fin)==NULL) {
    fprintf(stderr, "W: Erro na leitura do ficheiro: Ficheiro Vazio!\n");
  }
  line[300]='\0';
  if (line[strlen(line)-1]!='\n') {
    fprintf(stderr, "W: Linha muito longa na leitura do ficheiro\n");
    while(fgetc(fin)!='\n');
  }
  if (sscanf(line, "%lf [kg]%*[ \n\t]%c", &massa, &tmp)!=1) {
      fprintf(stderr, "W: Problema ao ler a massa a partir do ficheiro (percebemos: %f kg)\n", massa);
  }

  if (fgets(line, 300, fin)==NULL) {
    fprintf(stderr, "W: Erro na leitura do ficheiro: O ficheiro só tem 1 linha!\n");
  }
  line[300]='\0';
  if (line[strlen(line)-1]!='\n') {
    fprintf(stderr, "W: Linha muito longa na leitura do ficheiro\n");
    while(fgetc(fin)!='\n');
  }
  if (strcmp(line, FILE_HEADLINE)){
    fprintf(stderr, "W: A linha de coluna nao se encontra igual à do programa!\n");
  }

  while (fgets(line, 300, fin)) {
    line[300]='\0';
    if (line[strlen(line)-1]!='\n') {
      fprintf(stderr, "W: Linha muito longa na leitura do ficheiro\n");
      while(fgetc(fin)!='\n');
      continue;
    }
    /*estamos a ler:$<tempo> <x> <z> <vx> <vz> <atitude> <combustivel>%*[ \n\t]%c*/
    if (sscanf(line,"%lf %lf %lf %lf %lf %lf %lf%*[ \n\t]%c", o, o+1, o+2, o+3, o+4, o+5, o+6, &tmp)!=7) {
      fprintf(stderr, "W: Linha invalida na leitura do ficheiro\n");
      continue;
    }

    point(o[t1],o[t2], p); poly_push(g->data, p);
    g->max_x = max(g->max_x, p[0]);
    g->min_x = min(g->min_x, p[0]);
    g->max_y = max(g->max_y, p[1]);
    g->min_y = min(g->min_y, p[1]);
  }
  fclose(fin);
  /*Ordena os pontos por tempo, para evitar casos em que estes nao estejam por ordem: */
  qsort(g->data->pts, g->data->size, sizeof(double)*2, double_increasing);
  return 0;
}

void graph_draw(graph * g, int t1, int t2) {
  /*atualiza a camara pos e dim, para ter as dimensoes do ecra */
  /* Aqui e um local onde faria sentido usar uma variavel global, para nao estar a perder tempo a por tanta coisa no stack */
  /*static const*/ char axisname[7][20]={"t(s)\0","x(m)\0","z(m)\0","vx(m/s)\0","vz(m/s)\0","0(\xb0) \0","m(kg)\0"};
  polygon * pol;
  double O[2]={0}, p1[2]={0}, p2[2]={0}, p3[2]={0}, p4[2]={0};
  double sum[2]={0};
  double tmp[2]={0};
  int i;
  char str[100];
  pol = poly();
  g->c->dim[0] = (g->max_x - g->min_x)*1.14;
  g->c->dim[1] = (g->max_y - g->min_y)*1.14;
  g->c->pos[0] = g->min_x - (g->max_x - g->min_x)*0.090;
  g->c->pos[1] = g->min_y - (g->max_y - g->min_y)*0.090;

  view_begin(g->v);
    /*desenha o background: */
    g2_pen(g->v->id, g->b_color);
    g2_filled_rectangle(g->v->id, 0, 0, g->v->W, g->v->H);

    /*desenha os eixos: */
    g2_pen(g->v->id, g->axisl_color);
    point(0,0,O); project(O,g->c,O);
    point(g->min_x,0,p1); project(p1,g->c,p1);
    point(0,g->min_y,p2); project(p2,g->c,p2);
    point(0,g->max_y,p3); project(p3,g->c,p3);
    point(g->max_x,0,p4); project(p4,g->c,p4);
    g2_line(g->v->id, p1[0],p1[1],p4[0],p4[1]);
    g2_filled_triangle(g->v->id, p4[0], p4[1]-5, p4[0], p4[1]+5, p4[0]+14, p4[1]);
    g2_line(g->v->id, p2[0],p2[1],p3[0],p3[1]);
    g2_filled_triangle(g->v->id, p3[0]-5, p3[1], p3[0]+5, p3[1], p3[0], p3[1]+14);

    /*desenha os pontos: (estamos a assumir que nao ha so 1 ponto)*/
    if (t1==t2) {
      point(g->min_x, g->min_y, p1); project(p1,g->c,p1);
      point(g->max_x, g->max_y, p2); project(p1,g->c,p2);
      g2_pen(g->v->id, g->p_color);
      g2_line(g->v->id, p1[0],p1[1],p2[0],p2[1]);
    } else {
      g2_pen(g->v->id, g->p_color);
      poly_copy(g->data, pol);
      poly_project(pol, g->c, pol);
      g2_poly_line(g->v->id, pol->size, pol->pts);
    }

    /*desenha escala: */
    g2_pen(g->v->id, g->axisv_color);
    g2_set_font_size(g->v->id, 12);
    sum[0]=(g->max_x-g->min_x)/10;
    sum[1]=0;
    for (i=1; i<=10 && i*sum[0]<=0.97*g->max_x; i++) {
      point(i*sum[0],sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0],tmp[1]-5,tmp[0],tmp[1]+5);
      sprintf(str, "%4.2g", i*sum[0]);
      g2_string(g->v->id, tmp[0]-10,tmp[1]-20, str);
    }
    for (i=1; i<=10 && -i*sum[0]>=0.97*g->min_x; i++) {
      point(-i*sum[0],sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0],tmp[1]-5,tmp[0],tmp[1]+5);
      sprintf(str, "%4.2g", -i*sum[0]);
      g2_string(g->v->id, tmp[0]-10,tmp[1]-20, str);
    }
    sum[0]=0;
    sum[1]=(g->max_y-g->min_y)/10;
    for (i=1; i<=10 && i*sum[1]<=0.97*g->max_y; i++) {
      point(sum[0],i*sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0]-5,tmp[1],tmp[0]+5,tmp[1]);
      sprintf(str, "%4.3g", i*sum[1]);
      g2_string(g->v->id, tmp[0]-8-6*strlen(str),tmp[1]-4, str);
    }
    for (i=1; i<=10 && -i*sum[1]>=0.97*g->min_y; i++) {
      point(sum[0],-i*sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0]-5,tmp[1],tmp[0]+5,tmp[1]);
      sprintf(str, "%4.3g", -i*sum[1]);
      g2_string(g->v->id, tmp[0]-8-6*strlen(str),tmp[1]-4, str);
    }
    /*desenha nomes dos eixos: */
    g2_pen(g->v->id, g->axisn_color);
    g2_set_font_size(g->v->id, 12);
    g2_string(g->v->id, O[0]-10, O[1]-10, "O");
    g2_string(g->v->id, p3[0]-7*strlen(axisname[g->t2]), p3[1]-10, axisname[g->t2]);
    g2_string(g->v->id, p4[0]-10, p4[1]-20, axisname[g->t1]);
  view_end(g->v);

  poly_destroy(pol);
}

int modo_graph(char * filename, int t1, int t2) {
  graph * g;
  g = graph_init(650,650,t1,t2,COLOR_WHITE,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
  printf("Reading data from file... ");
  fflush(stdout);
  if (graph_load_points_from_file (filename, g, t1, t2)) {
    graph_destroy(g);
    return 1;
  }
  printf(" Loaded %lu points!\n", (unsigned long)g->data->size);
  if((unsigned long)g->data->size != 0 )
    graph_draw(g, t1, t2);
  else 
    printf("Se nao ha pontos, nao ha grafico :P!\n");
  printf("Carregue nalguma tecla para fechar a janela...\n");
  getchar();

  graph_destroy(g);
  return 0;
}
