#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include <math.h>


/*
  Vamos definir vetores como uma lista de tamanho n+1. Em que a[0] nos diz o tamanho do vetor e a[1]...a[n] as coordenadas do vetor
  Um ponto em 2d, sera uma lista de tamanho 4:
    p2d = {2, x, y, e}; //e is the basis os the system: (x/e,y/e,1) = (x,y,e)
    //We need a base to allow normalization of coordinates

*/
//TODO: Transformar todas as funcoes para usarem point?
typedef struct point {
  unsigned long long n;
  double * u;
} point;

double * cross3d_(double * a, double * b, double * s);
double * _cross3d_(double * a, double * b);
double dot(double * a, double * b);
double * rotate2d(double * p, double rad, double * s);
double * _rotate2d(double * p, double rad);
double * rotate2d_p(double * p, double rad, double * origin, double * s, double * aux);
double * _rotate2d_p(double * p, double rad, double * origin);
double * scale(double * p, double factor);
double * scale_p(double * p, double factor, double * origin);
double * _scale(double * p, double factor);
double * _scale_p(double * p, double factor, double * origin);
double * translate(double * p, double * T, double *s);
double * _translate(double * p, double * T);
double * simetric(double * p, double * s);
double * _simetric(double * p);
double * normalize(double * p); //Transforma as coordenadas de um ponto em (n,x,y,...,1)
double * _normalize(double * p); //Transforma as coordenadas de um ponto em (n,x,y,...,1)

#endif
