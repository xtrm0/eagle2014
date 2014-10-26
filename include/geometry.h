#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max(a,b) ((a) >= (b) ? (a) : (b))
#define min(a,b) ((a) <= (b) ? (a) : (b))


/*
  Um ponto e um double pt[2]:
    pt[0] := coordenada x;
    pt[1] := coordenada y;
*/

/*
  Um polygon e um array de pontos
*/
typedef struct polygon {
/*
  Isto e basicamente uma implementacao de uma array de doubles[2] de tamanho variavel
  Complexidades:
    push_back: O(1+)
    pop_back: O(1)
    Qualquer transformacao geometrica: O(n)
*/
  size_t size;
  size_t max_size;
  double * pts;
} polygon;


/*
  Estrutura que representa uma camara bidimensional, para o qual imagens sao desenhadas.
  Esta camara contem internamente a implementacao de um screen, e serve apenas para guardar dados geometricos sobre referenciais

  Values:
    dim: dimensoes x, y da camara no refencial da lua (unidades SI)
    pos: posicoes x, y da camara no referancial da lua (unidades SI)
    vdim: dimensoes x,y da camara no referencial do virtual device (pixeis)
    vpos: posicoes x,y da camara no referncial do virtual device (pixeis)
*/
typedef struct camera2d {
  double dim[2];
  double pos[2];
  double vdim[2];
  double vpos[2];

} camera2d;



/*
  Funcoes para trabalhar com pontos:

  As funcoes que comecam com _ reservam memoria para o valor devolvido, e nao a libertam
  As funcoes sem o _ têm em vista performance, e nao reservam memoria
*/
double * point(double x, double y, double * s);
double * _point(double x, double y);

double dot(double * a, double * b);

double * rotate(double * p, double rad, double * s);
double * _rotate(double * p, double rad);

double * rotate_p(double * p, double rad, double * origin, double * s, double * aux);
double * _rotate_p(double * p, double rad, double * origin);

double * hadamart(double * p, double *, double *);
double * _hadamart(double * p, double *, double *);

double * _scale2d(double * p, double * q);

double * translate(double * p, double * T, double *s);
double * _translate(double * p, double * T);

double * simetric(double * p, double * s);
double * _simetric(double * p);

double * inverse(double *p, double *s);
double * _inverse(double * p);

//Projeta um ponto para o referencial de uma view
double * project(double * p, camera2d * c, double * s);

/*
  Indica se dois segmentos de reta colidem.
  Devolve:
    1 caso colidam
    0 caso contrario
*/
int lineseg_colide(double * p1, double * p2, double * p3, double * p4);


/*
  Funcoes para trabalhar com poligonos

  As funcoes abaixo devolvem um apontador igual ao que receberam como argumentos
*/

//Cria um poligono
polygon * poly();

//Liberta a memoria de um poligono
void poly_destroy(polygon *);

/*
  Adiciona um ponto a um poligono
*/
polygon * poly_push(polygon *, double *);

/*
  Apaga o ultimo ponto de um poligono
*/
void poly_pop(polygon *);

/*
  Nao liberta memoria
  Apaga todos os pontos de um poligono
*/
polygon * poly_clear(polygon *);

/*
  O clean garante a libertacao da memoria
  Apaga todos os pontos de um poligono, e liberta a memoria toda que eles ocupavam
*/
polygon * poly_clean(polygon *);

/*
  Roda um poligono em torno do ponto (0,0)
*/
polygon * poly_rotate(polygon *, double);

/*
  Translaciona um poligono por um vetor (p[0],p[1])
*/
polygon * poly_translate(polygon *, double *);

/*
  Garante que o poligono x tem memoria para n pontos
*/
polygon * poly_allocate(polygon * s, size_t sz);

/*
  Copia o poligono s para o poligono d
*/
polygon * poly_copy(polygon * s, polygon * d);

/*
  Devolve um apontador para uma copia do poligono s
*/
polygon * _poly_copy(polygon * s);

/*
  Projeta um poligono para o referencial de uma view
*/
polygon * poly_project(polygon * p, camera2d *c, polygon * s);

/*
  Indica se um poligono colide com um segmento de reta.
  Devolve:
    1 caso colida
    0 caso contrario
*/
int poly_colide_lineseg(polygon * s, double * p1, double * p2);


/*
  Funcoes para trabalhar com camaras
*/


/*
  Cria uma camara
*/
camera2d * c2d_init(double,double,double,double,double,double,double,double);
/*
  Destroi uma camara
*/
void c2d_destroy(camera2d *);






/*
  Helper functions:
*/
//Funcao para usar no quicksort para ordenar doubles por ordem crescente
int double_increasing (const void * a, const void * b);






#ifdef DEBUG
void dump_pol(polygon * pol);
#endif
#endif
