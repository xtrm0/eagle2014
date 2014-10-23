#include "../include/grafico.h"

void modograph (char *nome) {
  //TODO: Verificar se o ficheiro e possivel de ser lido e imprimir warning
  int d, dev;
  double massa, tempo, x, z, vx, vz, atitude, combustivel;
  double max_z, max_t;
  FILE * fin = fopen(nome, "r");

  dev=g2_open_X11X(775, 575, 0, 0, "eagle2014 - Ver Gráfico", "eagle2014 - Ver Gráfico", "/dev/null", 0, 0);
  d=g2_open_vd();
  g2_clear(d);
  g2_attach(d, dev);

  //TODO: Criar uma funcao que define as cores basicas e usar aqui e no view.c
  polygon * pol;
  double p[2]= {0};

  pol = poly();

  fscanf(fin, "%lf [kg]", &massa);

  while (feof(fin)!=0) {
    fscanf(fin,"%lf [s] %lf [m] %lf [m] %lf [m/s] %lf [m/s] %lf [graus] %lf [kg]", &tempo, &x, &z, &vx, &vz, &atitude, &combustivel);
    point(tempo,z,p); poly_push(pol, p);
    max_z = max(max_z, z);
    max_t = max(max_t, tempo);
  }


  //TODO: escolher a cor
  g2_poly_line(d, pol->size, pol->pts); //TODO: Descobrir qual o melhor tipo de metodo para desenhar isto: se com poly_line, se com spline
}
