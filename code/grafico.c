#include "../include/grafico.h"

graph * graph_init(double W, double H, char * x_axis, char * y_axis, int b_color, int p_color, int axisl_color, int axisv_color, int axisn_color) {
  graph * g = malloc(sizeof(graph));
  g->data = poly();
  g->max_x = DBL_MIN;
  g->min_x = 0;
  g->max_y = DBL_MIN;
  g->min_y = 0;
  g->c = c2d_init(0,0,0,0,W,H,0,0);
  g->v = view_init(W,H,"eagle2014 - Ver Grafico");
  g->x_axis = x_axis;
  g->y_axis = y_axis;
  g->p_color = p_color;
  g->b_color = b_color;
  g->axisl_color = axisl_color;
  g->axisv_color = axisv_color;
  g->axisn_color = axisn_color;
  return g;
}

int graph_load_points_from_file (char *nome, graph * g) {
  //TODO: Verificar se o ficheiro existe e e possivel de ser lido e imprimir warning
  int d, dev;
  double massa, tempo, x, z, vx, vz, atitude, combustivel;
  double max_z, max_t;
  FILE * fin = fopen(nome, "r");
  double p[2]= {0};
  poly_destroy(g->data);
  g->data = poly();
  fscanf(fin, "%lf [kg]\n", &massa);
  fscanf(fin, FILE_HEADLINE);
  while (feof(fin)==0) {
    fscanf(fin,"%lf %lf %lf %lf %lf %lf %lf\n", &tempo, &x, &z, &vx, &vz, &atitude, &combustivel);
//  printf("%lf %lf %lf %lf %lf %lf %lf\n", tempo, x, z, vx, vz, atitude, combustivel);
    point(tempo,z,p); poly_push(g->data, p);
    g->max_x = max(g->max_x, p[0]);
    g->min_x = min(g->min_x, p[0]);
    g->max_y = max(g->max_y, p[1]);
    g->min_y = min(g->min_y, p[1]);
  }
  //Ordena os pontos por tempo, para evitar casos em que estes nao estejam por ordem:
  qsort(g->data->pts, g->data->size, sizeof(double)*2, double_increasing);
  return 0;
}

int graph_draw(graph * g) {
  //atualiza a camara pos e dim, para ter as dimensoes do ecra
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
    //desenha o background:
    g2_pen(g->v->id, g->b_color);
    g2_filled_rectangle(g->v->id, 0, 0, g->v->W, g->v->H);

    //desenha os eixos:
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

    //desenha os pontos:
    g2_pen(g->v->id, g->p_color);
    poly_copy(g->data, pol);
    poly_project(pol, g->c, pol);
//    dump_pol(pol);
    //TODO: Descobrir qual o melhor tipo de metodo para desenhar isto: pois podemos usar so pontos em vez de retas
    g2_poly_line(g->v->id, pol->size, pol->pts);

    //desenha escala:
    //TODO: Para graficos generalizados, a escala nao fica muito bonita, mas para graficos so positivos funciona exatamente como esperado
    g2_pen(g->v->id, g->axisv_color);
    g2_set_font_size(g->v->id, 12);
    sum[0]=g->min_x;
    for (i=0; i<9; i++) {
      sum[0] += (g->max_x - g->min_x)/10.0;
      point(sum[0],sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0],tmp[1]-5,tmp[0],tmp[1]+5);
      sprintf(str, "%5.5g", sum[0]);
      g2_string(g->v->id, tmp[0]-10,tmp[1]-20, str);
    }
    sum[0]=0;
    sum[1]=g->min_y;
    for (i=0; i<9; i++) {
      sum[1] += (g->max_y - g->min_y)/10.0;
      point(sum[0],sum[1],tmp);
      project(tmp,g->c,tmp);
      g2_line(g->v->id, tmp[0]-5,tmp[1],tmp[0]+5,tmp[1]);
      sprintf(str, "%4.5g", sum[1]);
      g2_string(g->v->id, tmp[0]-8-6*strlen(str),tmp[1]-4, str);
    }

    //desenha nomes dos eixos:
    g2_pen(g->v->id, g->axisn_color);
    g2_set_font_size(g->v->id, 12);
    g2_string(g->v->id, O[0]-10, O[1]-10, "O");
    g2_string(g->v->id, p3[0]-7*strlen(g->x_axis), p3[1]-10, g->x_axis);
    g2_string(g->v->id, p4[0]-10, p4[1]-20, g->y_axis);
  view_end(g->v);
}

void graph_addpoint(graph * g, double * p) {
  poly_push(g->data,p);
  g->max_x = max(g->max_x, p[0]);
  g->min_x = min(g->min_x, p[0]);
  g->max_y = max(g->max_y, p[1]);
  g->min_y = min(g->min_y, p[1]);
  return;
}

void modo_graph(char * filename) {
  graph * g;
  g = graph_init(800,800,"Z (m)","t (s)",COLOR_WHITE,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK);
  printf("Reading data from file... ");
  graph_load_points_from_file (filename, g);
  printf(" Loaded %ld points!\n", g->data->size);
  graph_draw(g);
  getchar(); //caso o programa seja iniciado por algo tipo echo 3 | eagle2014, garante que nao fecha a janela ate se premir ctrl+c (o que acho que seria pretendido)
}
