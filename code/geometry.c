#include "../include/geometry.h"
//nao verificamos se (dim(a)==dim(b))
//Portanto temos de ter cuidado para nao fazer contas mal

//TODO: make all implementations be pass by arg, instead of returning a pointer (they should all return void)

//warning, all functions starting with _ allocate memory for the result, and are therefore unsafe

double * cross3d_(double * a, double * b, double * s) {
  int i;
  if (a[0]!=b[0]) {
    return NULL;
  }
  s[0] = a[0];
  s[a[0]+1] = 1;
  s[1] = a[2]*b[3] - a[3]*b[2];
  s[2] = a[3]*b[1] - a[1]*b[3];
  s[3] = a[1]*b[2] - a[2]*b[1];
  return s;
}
double * _cross3d_(double * a, double * b) {
  double * s = (double *)malloc(sizeof(double) * (a[0]+2));
  cross3d(a,b,s);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

double dot(double * a, double * b) {
  double r = 0;
  int i;
  if (a[0]!=b[0]) {
    return NULL;
  }
  for (i=1; i<a[0]; i++) {
    r += a[i]*b[i];
  }
  return r;
}

double * rotate2d(double * p, double rad, double * s) {
  s[0] = p[0];
  s[p[0]+1] = 1;
  s[1] = cos(rad)*p[1] - sin(rad)*p[2];
  s[2] = sin(rad)*p[1] + cos(rad)*p[2];
  return s;
}
double * _rotate2d(double * p, double rad) {
  double * s = (double *)malloc(sizeof(double) * (p[0]+2));
  rotate2d(p,rad,s);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

double * rotate2d_p(double * p, double rad, double * origin, double * s, double * aux) {
  simetric(origin, aux);
  translate(p, aux, s);
  rotate2d(s, rad, aux);
  translate(aux, origin, s);
  return s;
}
double * _rotate2d_p(double * p, double rad, double * origin) {
  double * s, * aux;
  s = (double *)malloc(sizeof(double) * (p[0]+2));
  aux = (double *)malloc(sizeof(double) * (p[0]+2));
  rotate2d_p(p, rad, origin, s, aux);
  free(aux);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}


double * scale(double * p, double factor) {
//TODO: implementa e so multiplicares x e y por factor
  return NULL;
}
double * scale_p(double * p, double factor, double * origin) {
//TODO: implementa igual ao rotade2d_p
  return NULL;
}
double * _scale(double * p, double factor) {
//TODO: implementa e so multiplicares x e y por factor
  return NULL;
}
double * _scale_p(double * p, double factor, double * origin) {
//TODO: implementa igual ao _rotade2d_p
  return NULL;
}

double * translate(double * p, double * T, double *s) {
  int i;
  if (p[0]!=T[0]) {
    return NULL;
  }
  s[0] = p[0];
  s[p[0]+1] = 1;
  for (i=1; i<=p[0]; i++) {
    s[i] = p[i]*p[p[0]+1] + T[i]*T[T[0]+1];
  }
  return s;
}
double * _translate(double * p, double * T) {
  double * s = (double *)malloc(sizeof(double) * (p[0]+2));
  translate(p,T,s);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

double * simetric(double * p, double * s) {
  int i;
  s[0] = p[0];
  s[p[0]+1] = 1;
  for (i=1; i<=p[0]; i++) {
    s[i] = -p[i]*p[p[0]+1];
  }
  return s;
}
double * _simetric(double * p) {
  int i;
  double * s = (double *)malloc(sizeof(double) * (p[0]+2));
  simetric(p,s);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

double * normalize(double * p){ //Transforma as coordenadas de um ponto em (n,x,y,...,1)
  int i;
  for (i=1; i<p[0]; i++) {
    p[i] = p[i]/p[p[0]+1];
  }
  p[p[0]+1] = 1;
  return p;
}
double * _normalize(double * p){ //Transforma as coordenadas de um ponto em (n,x,y,...,1)
  int i;
  double * s = (double *)malloc(sizeof(double) * (p[0]+2));
  s[0]=p[0];
  for (i=1; i<p[0]; i++) {
    s[i] = p[i]/p[p[0]+1];
  }
  s[p[0]+1] = 1;
  return s;
}
