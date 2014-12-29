#include "../include/geometry.h"
/*@WARNING: all functions starting with _ allocate memory for the result and may not dealocate it */

double * point(double x, double y, double * s) {
  s[0] = x;
  s[1] = y;
  return s;
}
double * _point(double x, double y) {
  double * s = malloc(sizeof(double)*2);
  TESTMEM(s);
  s[0] = x;
  s[1] = y;
  return s;
}
double dot(double * a, double * b) {
  double r = 0;
  int i;
  for (i=0; i<2; i++) {
    r += a[i]*b[i];
  }
  return r;
}

double * rotate(double * p, double rad, double * s) {
  double aux1, aux2;
  aux1 = cos(rad)*p[0] - sin(rad)*p[1];
  aux2 = sin(rad)*p[0] + cos(rad)*p[1];
  s[0] = aux1;
  s[1] = aux2;
  return s;
}
double * _rotate(double * p, double rad) {
  double * s = (double *)malloc(sizeof(double) * 2);
  TESTMEM(s);
  rotate(p,rad,s);
  return s;
}
double * rotate_p(double * p, double rad, double * origin, double * s, double * aux) {
  simetric(origin, aux);
  translate(p, aux, s);
  rotate(s, rad, aux);
  translate(aux, origin, s);
  return s;
}
double * _rotate_p(double * p, double rad, double * origin) {
  double * s, * aux;
  s = (double *)malloc(sizeof(double) * 2);
  TESTMEM(s);
  aux = (double *)malloc(sizeof(double) * 2);
  TESTMEM(aux);
  rotate_p(p, rad, origin, s, aux);
  free(aux);
  return s;
}

double * hadamart(double * p, double * q, double * s) {
  s[0] = q[0]*p[0];
  s[1] = q[1]*p[1];
  return s;
}
double * _scale2d(double * p, double * q) {
  double * s = malloc(sizeof(double)*2);
  TESTMEM(s);
  hadamart(p,q,s);
  return s;
}

double * translate(double * p, double * T, double *s) {
  int i;
  for (i=0; i<2; i++) {
    s[i] = p[i] + T[i];
  }
  return s;
}
double * _translate(double * p, double * T) {
  double * s = (double *)malloc(sizeof(double)*2);
  TESTMEM(s);
  translate(p,T,s);
  return s;
}

double * simetric(double * p, double * s) {
  int i;
  for (i=0; i<2; i++) {
    s[i] = -p[i];
  }
  return s;
}
double * _simetric(double * p) {
  double * s = (double *)malloc(sizeof(double)*2);
  TESTMEM(s);
  simetric(p,s);
  return s;
}
double * inverse(double *p, double *s) {
  int i;
  for (i=0; i<2; i++) {
    s[i] = 1.0/p[i];
  }
  return s;
}
double * _inverse(double * p) {
  double * s = (double *)malloc(sizeof(double)*2);
  TESTMEM(s);
  inverse(p,s);
  return s;
}

double * project(double * p, camera2d * c, double * s) {
  double aux1[2] = {0,0};
  double aux2[2] = {0,0};
  double aux3[2] = {0,0};
  /*P = P - CAMERA.POSITION */
  simetric(c->pos, aux1);
  translate(p, aux1, aux2);

  /*P = P * SCREEN.DIMENSIONS */
  hadamart(aux2, c->vdim, aux1);

  /*P = P / CAMERA.DIMENSIONS */
  inverse(c->dim, aux2);
  hadamart(aux1, aux2, aux3);

  /*P = P + SCREEN.POSITION */
  translate(aux3, c->vpos, s);
  return s;
}



/*
------------------------------------------------
POLYGON FUNCTIONS
------------------------------------------------
*/

polygon * poly() {
  polygon * s = malloc(sizeof(polygon));
  TESTMEM(s);
  s->size = 0;
  s->max_size = 1;
  s->pts = malloc(sizeof(double)*2);
  TESTMEM(s->pts);
  return s;
}

void poly_destroy(polygon * s) {
  if (s!=NULL) {
    if(s->pts!=NULL)
      free(s->pts);
    free(s);
  }
}

polygon * poly_allocate(polygon * s, size_t sz) {
  double * d;
  if (sz <= s->max_size) return s;
  while (sz > (s->max_size *= 2));
  d = malloc(sizeof(double) * s->max_size * 2);
  TESTMEM(d);
  memcpy(d, s->pts, sizeof(double) * s->size * 2);
  free(s->pts);
  s->pts = d;
  return s;
}

polygon * poly_copy(polygon * s, polygon * d) {
  if (d->max_size < s->size) poly_allocate(d, s->size);
  d->size = s->size;
  memcpy(d->pts, s->pts, sizeof(double) * s->size * 2);
  return d;
}

polygon * _poly_copy(polygon * s) {
  polygon * d = malloc(sizeof(polygon));
  TESTMEM(d);
  d->size = s->size;
  d->max_size = s->max_size;
  d->pts = malloc(sizeof(double) * s->max_size * 2);
  TESTMEM(d->pts);
  memcpy(d->pts, s->pts, sizeof(double) * s->size * 2);
  return d;
}

polygon * poly_clear(polygon * s) {
  s->size=0;
  return s;
}

polygon * poly_clean(polygon * s) {
  poly_destroy(s);
  s = poly();
  return s;
}

void poly_pop(polygon * s) {
  if (s->size > 0)
    s->size = s->size-1;
}

polygon * poly_push(polygon * s, double * p) {
  size_t i;
  double * d;
  if (s->max_size==s->size) {
    s->max_size = s->max_size * 2;
    d = malloc(sizeof(double) * s->max_size * 2);
    TESTMEM(d);
    memcpy(d, s->pts, sizeof(double) * s->size * 2);
    free(s->pts);
    s->pts = d;
  }
  for (i=0; i < 2; i++)
    s->pts[2 * s->size + i] = p[i];
  s->size++;
  return s;
}

polygon * poly_rotate(polygon * s, double rot) {
  size_t i;
  for (i=0; i < s->size; i++)
    rotate(s->pts + 2*i, rot, s->pts + 2*i);
  return s;
}



polygon * poly_translate(polygon * s, double * T) {
  size_t i;
  for (i=0; i < s->size; i++)
    translate(s->pts + 2*i, T, s->pts + 2*i);
  return s;
}

polygon * poly_project(polygon * p, camera2d *c, polygon * s) {
  size_t i;
  for (i=0; i < p->size; i++)
    project(p->pts + 2*i, c, s->pts + 2*i);
  return s;
}

/*
 *
 * 	Colision detection
 *
 */

/*O(1) */
int lineseg_colide(double * p1, double * p2, double * p3, double * p4) {
	double a1, a2, a3, a4;
  a1 = (p2[0] - p1[0])*(p3[1] - p2[1]) - (p2[1] - p1[1])*(p3[0] - p2[0]);
  a2 = (p2[0] - p1[0])*(p4[1] - p2[1]) - (p2[1] - p1[1])*(p4[0] - p2[0]);
  a3 = (p4[0] - p3[0])*(p1[1] - p4[1]) - (p4[1] - p3[1])*(p1[0] - p4[0]);
  a4 = (p4[0] - p3[0])*(p2[1] - p4[1]) - (p4[1] - p3[1])*(p2[0] - p4[0]);
  if ((a1>0 && a2>0) || (a1<0 && a2<0) || (a3>0 && a4>0) || (a3<0 && a4<0))
    return 0;
  return 1;
}

/*O(n) */
int poly_colide_lineseg(polygon * s, double * p1, double * p2) {
	size_t i;
	for (i=0; i < s->size-1; i++) {
		if (lineseg_colide(p1,p2,s->pts+(2*i), s->pts + 2*i+2)) {
			return 1;
		}
	}
	if (lineseg_colide(p1,p2,s->pts,s->pts+2*i))
		return 1;
	return 0;
}


#ifdef _DEBUG
void dump_pol(polygon * pol) {
  int i,j;
  printf("\n====================\nPOLYGON DUMP\n====================\n");
  for (i=0; i<pol->size; i++) {
    for (j=0; j<2; j++) {
      printf("%f ", pol->pts[i*2+j]);
    }
    printf("\n");
  }
}
#endif



/*
  ----------------------------------------------
  CAMERA RELATED FUNCTIONS
  ----------------------------------------------
*/

camera2d * c2d_init(double w, double h, double x, double y, double W, double H, double X, double Y) {
  camera2d * c = (camera2d *)malloc(sizeof(camera2d));
  if (c == NULL) {
    printf("(3x23) Erro detetado: Memory Access Error!");
    exit(ENOMEM);
  }
  c->dim[0]=w;
  c->dim[1]=h;
  c->pos[0]=x;
  c->pos[1]=y;
  c->vdim[0]=W;
  c->vdim[1]=H;
  c->vpos[0]=X;
  c->vpos[1]=Y;

  return c;
}
void c2d_destroy(camera2d * c) {
  if (c!=NULL)
    free(c);
}

//cordenadas do canto inferior esquerdo
void c2d_fit(camera2d *c, double x, double y, double w, double h) {
  c->pos[0] = x;
  c->pos[1] = y;
  if (w==0) w=1;
  if (h==0) h=1;
  //TEST
  c->dim[0] = c->dim[1] = max(w,h);
}

//cordenadas do centro
void c2d_centerfit(camera2d *c, double x, double y, double w, double h) {
  //Nota isto assume que queremos a escala w=h, que e o caso para todo o trabalho
  c->dim[0] = c->dim[1] = max(w,h);
  c->pos[0]= x - c->dim[0]/2;
  c->pos[1]= y - c->dim[1]/2;
}

void c2d_zoom(camera2d *c, double per) {
  c->pos[0] += c->dim[0]/2;
  c->pos[1] += c->dim[1]/2;
  c->dim[0] *= per;
  c->dim[1] *= per;
  c->pos[0] -= c->dim[0]/2;
  c->pos[1] -= c->dim[1]/2;
}




/*
  Helper functions:
*/
int double_increasing (const void * a, const void * b){
  return ((*(double *) a) - (*(double *) b));
}
