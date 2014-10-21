#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
  Um ponto e um double pt[2]:
    pt[0] := coordenada x;
    pt[1] := coordenada y;
*/

//TODO: Transformar todas as funcoes para usarem point?
#define ITD(x) *((double *)&x)
#define DTI(x) ((size_t *)x)[0]
typedef struct polygon {
  //Isto e basicamente uma implementacao de uma array de tamanho variavel
  //Complexidades:
    //push: O(1+)
    //pop: O(1)
    //Qualquer transformacao geometrica: O(n)
  size_t size;
  size_t max_size;
  double * pts;
} polygon;



/* Funcoes para trabalhar com vetores a n dimensoes: */
double * point(double x, double y, double * s);
double * _point(double x, double y);

double dot(double * a, double * b);

double * rotate(double * p, double rad, double * s);
double * _rotate(double * p, double rad);

double * rotate_p(double * p, double rad, double * origin, double * s, double * aux);
double * _rotate_p(double * p, double rad, double * origin);

double * hadamart(double * p, double *, double *);
double * _hadamart(double * p, double *, double *);

double * translate(double * p, double * T, double *s);
double * _translate(double * p, double * T);

double * simetric(double * p, double * s);
double * _simetric(double * p);

double * normalize(double * p); //Transforma as coordenadas de um ponto em (n,x,y,...,1)
double * _normalize(double * p); //Transforma as coordenadas de um ponto em (n,x,y,...,1)



/* Funcoes para trabalhar com poligonos (conjuntos de n pontos a duas dimensoes)*/
/*
  Vamos definir um poligono como um conjunto de n pontos, todos com as mesmas dimensoes, mas nao necessariamente com a mesma base:
  polygon = {n, p2d, ..., p2d};
  em que os p2d tem todos a entrada [0] igual
  Nenhuma das operacoes com poligonos usara o malloc, excepto o polygon, o polygon_push e o poly_to_g2poly
*/

polygon * poly();
//Liberta a memoria de um poligono
void poly_destroy(polygon *);
/*
  Adiciona um ponto a um poligono de n dimensoes
  Se o ponto tiver dimensoes inferiores a do poligino termina o programa
  Se o ponto tiver dimensoes superiores a do poligono copia so as primeiras dimensoes ate ficar igual a do poligono
*/
polygon * poly_push(polygon *, double *);

void poly_pop(polygon *);
/*
Nao liberta memoria
*/
polygon * poly_clear(polygon *);
/*
O clean garante a libertacao da memoria
*/
polygon * poly_clean(polygon *);

/*
  Roda um poligono
*/
polygon * poly_rotate(polygon *, double);
//TODO: polygon * poly_rotate_p(polygon *, double, double *);
/*
  Translaciona um poligono
*/
polygon * poly_translate(polygon *, double *);

/*
double ** poly_scale();
double ** poly_simetric();
double ** poly_normalize();
*/
polygon * poly_allocate(polygon * s, size_t sz);
polygon * poly_copy(polygon * s, polygon * d);
polygon * _poly_copy(polygon * s);

/*
  TODO: As projecoes sao feitas sem ter em conta manter o aspect ratio do x,y
  TODO: Corrigir isto
*/


/*
  Estrutura que representa uma camara bidimensional, para o qual imagens sao desenhadas.
  Esta camara contem internamente a implementacao de um screen, e serve apenas para guardar dados sobre referenciais

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


camera2d * c2d_init(double,double,double,double,double,double,double,double);
void c2d_destroy(camera2d *);









#ifdef DEBUG
void dump_pol(polygon * pol);
#endif





#endif
