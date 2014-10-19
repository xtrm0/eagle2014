#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
  Vamos definir vetores como uma lista de tamanho n+2. Em que a[0] nos diz o tamanho do vetor e a[1]...a[n] as coordenadas do vetor e a[n+1] a unidade do vetor
  Um ponto em 2d, sera uma lista de tamanho 4.
    p2d = {2, x, y, e}; //e is the base of the system: (x/e,y/e,1) = (x,y,e)
    //We need a base to allow normalization of coordinates
  É de notar que apesar de o primeiro valor de p2d ser um double, ele não deve ser guardado como double, mas sim com a representacao de size_t
  de modo a que guarde uma posicao numa array
*/

//TODO: Transformar todas as funcoes para usarem point?
typedef size_t ind; //usamos isto para posteriormente pormos alguns defines aqui para garantir que o tamanho de double e de ind sao iguais
#define ITD(x) *((double *)&x)
#define DTI(x) ((ind *)x)[0]
typedef struct polygon {
  //Isto e basicamente uma implementacao de uma array de tamanho variavel
  //Complexidades:
    //push: O(1+)
    //pop: O(1)
    //Qualquer transformacao geometrica: O(n)
  ind size;
  ind max_size;
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


/*
  TODO: As projecoes sao feitas sem ter em conta ratio x,y,
  TODO: Corrigir isto
*/


/*
  Estrutura que representa uma camara bidimensional, para o qual imagens sao desenhadas.
  Esta camara contem internamente a implementacao de um screen, e serve apenas para guardar dados sobre referenciais
  (W, H): Width and Height of the camera
  (X, Y): Position of the bottom left corner of the camera
*/
typedef struct camera2d {
  //tamanho da camara no referencial da view
  double dim[2];
  //posicao da camara no referencial da view
  double pos[2];
  //tamanho da view num referencial de pixeis (referencial do virtual device)
  double vdim[2];
  //posicao da view num referencial de pixeis (referencial do virtual device)
  double vpos[2];

} camera2d;


camera2d * c2d_init(double,double,double,double,double,double,double,double);
void c2d_destroy(camera2d *);









#ifdef DEBUG
void dump_pol(polygon * pol);
#endif





#endif
