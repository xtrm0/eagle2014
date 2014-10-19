#include "../include/geometry.h"
//TODO: make all implementations be pass by arg, instead of returning a pointer (they should all return void)

//WARNING: all functions starting with _ allocate memory for the result, and are therefore slower than without the _
//TODO: Nas comparacoes, e capaz de nao ser preciso usar typecasting

double * point2d(double x, double y, double e, double * s) {
  ind sz = 2;
  s[0] = ITD(sz);
  s[1] = x;
  s[2] = y;
  s[3] = e;
  return s;
}
double * _point2d(double x, double y, double e) {
  ind sz = 2;
  double * s = malloc(sizeof(double)*4);
  s[0] = ITD(sz);
  s[1] = x;
  s[2] = y;
  s[3] = e;
  return s;
}

double * cross3d(double * a, double * b, double * s) {
  int i;
  if (DTI(a)!=DTI(b)) {
    return NULL;
  }
  s[0] = a[0];
  s[DTI(a)+1] = 1;
  s[1] = a[2]*b[3] - a[3]*b[2];
  s[2] = a[3]*b[1] - a[1]*b[3];
  s[3] = a[1]*b[2] - a[2]*b[1];
  return s;
}

double * _cross3d(double * a, double * b) {
  double * s = (double *)malloc(sizeof(double) * (DTI(a)+2));
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
  if (DTI(a)!=DTI(b)) {
    return 0;
  }
  for (i=1; i<DTI(a); i++) {
    r += a[i]*b[i];
  }
  return r;
}

double * rotate2d(double * p, double rad, double * s) {
  double aux1, aux2;
  s[0] = p[0];
  s[DTI(p)+1] = 1;
  aux1 = cos(rad)*p[1] - sin(rad)*p[2];
  aux2 = sin(rad)*p[1] + cos(rad)*p[2];
  s[1] = aux1;
  s[2] = aux2;
  return s;
}
double * _rotate2d(double * p, double rad) {
  double * s = (double *)malloc(sizeof(double) * (DTI(p)+2));
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
  s = (double *)malloc(sizeof(double) * (DTI(p)+2));
  aux = (double *)malloc(sizeof(double) * (DTI(p)+2));
  rotate2d_p(p, rad, origin, s, aux);
  free(aux);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

//TODO: Isto devia chamar-se hadamart
double * scale2d(double * p, double * s, double fx, double fy) {
  s[3] = 1.0;
  s[0] = p[0];
  s[1] = fx*p[1];
  s[2] = fx*p[2];
  return s;
}
double * _scale2d(double * p, double fx, double fy) {
  double * s = malloc(sizeof(double)*4);
  s[3] = 1.0;
  s[0] = p[0];
  s[1] = fx*p[1];
  s[2] = fx*p[2];
  return s;
}

double * translate(double * p, double * T, double *s) {
  int i;
  if (DTI(p)!=DTI(T)) {
    return NULL;
  }
  s[0] = p[0];
  s[DTI(p)+1] = 1;
  for (i=1; i<=DTI(p); i++) {
    s[i] = p[i]*p[DTI(p)+1] + T[i]*T[DTI(T)+1];
  }
  return s;
}
double * _translate(double * p, double * T) {
  double * s = (double *)malloc(sizeof(double) * (DTI(p)+2));
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
  s[DTI(p)+1] = 1;
  for (i=1; i<=DTI(p); i++) {
    s[i] = -p[i]*p[DTI(p)+1];
  }
  return s;
}
double * _simetric(double * p) {
  int i;
  double * s = (double *)malloc(sizeof(double) * (DTI(p)+2));
  simetric(p,s);
  if (s==NULL) {
    free(s);
    return NULL;
  }
  return s;
}

double * normalize(double * p){ //Transforma as coordenadas de um ponto em (n,x,y,...,1)
  int i;
  for (i=1; i<DTI(p); i++) {
    p[i] = p[i]/p[DTI(p)+1];
  }
  p[DTI(p)+1] = 1;
  return p;
}
double * _normalize(double * p){ //Transforma as coordenadas de um ponto em (n,x,y,...,1)
  int i;
  double * s = (double *)malloc(sizeof(double) * (DTI(p)+2));
  s[0]=p[0];
  for (i=1; i<DTI(p); i++) {
    s[i] = p[i]/p[DTI(p)+1];
  }
  s[DTI(p)+1] = 1;
  return s;
}

double * project(double * p, camera2d * c) {
  p[1] = p[1] - c->x;
  p[1] = p[1] * c->W/c->w;
  p[1] = p[1] + c->x;
}


/*
------------------------------------------------
POLYGON FUNCTIONS
------------------------------------------------
*/


polygon * poly(ind dim) {
  polygon * s = malloc(sizeof(polygon));
  s->size = (ind)0;
  s->max_size = (ind)1;
  s->dim = dim;
  s->pts = malloc(sizeof(double)*(dim + 2));
  return s;
}

void poly_destroy(polygon * s) {
  free(s->pts);
  free(s);
}

polygon * poly_push(polygon * s, double * p) {
  ind i;
  double * d;
  if (s->dim < DTI(p)){
    printf("ERRO: POLYGON DIMENSION CHECK FAIL!");
    exit(0);
  }
  if (s->max_size==s->size) {
    s->max_size = s->max_size * 2;
    d = malloc(sizeof(double) * s->max_size * (s->dim+2));
    memcpy(d, s->pts, sizeof(double) * s->size * (s->dim + 2));
    free(s->pts);
    s->pts = d;
  }
  for (i=0; i < (s->dim + 2); i++)
    s->pts[(s->dim + 2) * s->size + i] = p[i];
  s->size++;
  return s;
}

polygon * poly_rotate2d(polygon * s, double rot) {
  ind i;
  for (i=0; i < (s->dim + 2); i++)
    rotate2d(s->pts + (s->dim+2)*i, rot, s->pts + (s->dim+2)*i);
  return s;
}

//TODO: polygon * poly_rotate2d_p(polygon *, double, double *);

polygon * poly_translate(polygon * s, double * T) {
  ind i;
  for (i=0; i < (s->dim + 2); i++)
    translate(s->pts + (s->dim+2)*i, T, s->pts + (s->dim+2)*i);
  return s;
}

double * poly_to_g2poly(polygon * s) {
  ind i;
  double * p = malloc(sizeof(double)*s->dim*2);
  for (i=0; i < (s->dim + 2); i++) {
    normalize(s->pts + (s->dim+2)*i);
    p[i*2] = s->pts[(s->dim+2)*i + 1];
    p[i*2+1] = s->pts[(s->dim+2)*i + 2];
  }
  return p;
}

#ifdef DEBUF
void dump_pol(polygon * pol) {
  int i,j;
  printf("\n====================\nPOLYGON DUMP\n====================\n");
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      printf("%lf ", pol->pts[i*4+j]);
    }
    printf("\n");
  }
}
#endif
