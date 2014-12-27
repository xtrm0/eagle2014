#include "../include/surface.h"

surface * sfc_init() {
  surface * s = calloc(1, sizeof(surface));
  TESTMEM(s);
  s->arr = s->arr_back = l_init(sizeof(moon_point));
  s->lp = s->lp_back = l_init(sizeof(void *));
  return s;
}

void sfc_destroy(surface * s) {
  if (s!=NULL) {
    l_destroy(s->arr);
    l_destroy(s->lp);
    free(s);
  }
}

surface * _sfc_copy(surface * a) {
  surface * s = sfc_init();
  s->arr_size = a->arr_size;
  s->lp_size = a->lp_size;
  s->arr_back = a->arr_back;
  s->lp_back = a->lp_back;
  l_copy(a->arr, s->arr, sizeof(moon_point));
  l_copy(a->lp, s->lp, sizeof(void *));
  return s;
}

void sfc_add_point_back(surface * s, moon_point * p) {
  l_push_next(s->arr_back, p, sizeof(*p));
  s->arr_back= s->arr_back->next;
  s->arr_size++;
}

int arr_find_byname(void *a, void *b) {
  return strcmp(((moon_point *)(((list_no *)a)->val))->name,(char *)b);
}

void sfc_add_point_after(surface * s, char name[MAX_POINT_NAME], moon_point p) {
  int flag=0;
  list_no * aux = l_find(s->arr,&arr_find_byname,name);
  if (aux->next == s->arr_back) flag=1;
  l_push_next(aux->next, &p, sizeof(p));
  if (flag) s->arr_back= s->arr_back->next;
  s->arr_size++;
}

void sfc_remove_arr(surface * s, list_no * tmp) {
  list_no * aux;
  if (tmp==NULL) return;
  if (s->arr_back == tmp->next) {
    s->arr_back = tmp;
  }
  aux = tmp->next;
  tmp->next=aux->next;
  free(aux->val);
  free(aux);
  s->arr_size--;
}

void sfc_add_lp(surface * s, char name[MAX_POINT_NAME]) {
  list_no * aux = l_find(s->arr,&arr_find_byname,name);
  l_push_next(s->lp_back, (void*)&(aux->next), sizeof(void*));
  s->lp_back= s->lp_back->next;
  s->lp_size++;
}

void sfc_draw(surface * s, camera2d * c, view * v) {
  double p1[2] = {0};
  double p2[2] = {0};
  double p3[3] = {0};
  list_no * aux;
  if (s->arr->next==NULL) {
      p3[0] = -MAX_COORD;
      project(p3, c, p1);
      p3[0] = MAX_COORD;
      project(p3, c, p2);
      printf("((%f, %f), (%f, %f))\n", p2[0],p2[1],p1[0],p1[1]);
      g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);
      return;
  }

  aux = s->arr->next;
  p3[1] = ((moon_point *)(aux->val))->c[1];
  project(p3, c, p1);
  p1[0]=-10.0;
  while (aux!=NULL) {
    p3[0]=((moon_point *)(aux->val))->c[0];
    p3[1]=((moon_point *)(aux->val))->c[1];
    project(p3, c, p2);
    printf("((%f, %f), (%f, %f))\n", p2[0],p2[1],p1[0],p1[1]);
    g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);
    p1[0]=p2[0];
    p1[1]=p2[1];
    aux = aux->next;
  }
  p1[1] = p2[1];
  p1[0] = c->vdim[0] + 100 + c->vpos[0];
  g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);
}



void sfc_draw_labels(surface * s, camera2d * c, view * v) {
  //TODO: desenha as labels dos pontos de uma surface
  //TODO: desenha os pontos de aterragem
  double p[2] = {0};
  list_no * aux;
  aux = s->arr->next;
  while (aux!=NULL) {
    project(((moon_point *)aux->val)->c, c, p);
    //TODO: desenha o nome na posicao dada
    //g2_string(v->id, aux);
    aux = aux->next;
  }
  //TODO: muda de cor
  aux = s->lp->next;
  while (aux!=NULL) {
    project(((moon_point *)aux->val)->c, c, p);
    //TODO: desenha o nome de pontos de aterragem na posicao dada
    //g2_string(v->id, aux);
    aux = aux->next;
  }
}


void sfc_clear_lp (surface * s) {
  l_destroy(s->lp);
  s->lp = s->lp_back = l_init(sizeof(void *));
  s->lp_size=0;
}