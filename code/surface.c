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

double mp_pos_cmp(moon_point *ma, moon_point *mb) {
  if (mb->c[0]-ma->c[0] != 0)
    return mb->c[0]-ma->c[0];
  else
    return mb->c[1]-ma->c[1];
}

int arr_find_pos(void *a, void *b) {
  moon_point *ma, *mb;
  ma = (moon_point *)(((list_no *)a)->val);
  mb = (moon_point *)b;
  return (mp_pos_cmp(ma,mb)>=0);
}

void sfc_add_point_sorted(surface * s, moon_point * p) {
  int flag=0;
  list_no * aux = l_find(s->arr,&arr_find_pos,p);
  if (aux == NULL) {
    flag=1;
    aux = s->arr_back;
  }
  l_push_next(aux, p, sizeof(moon_point));
  if (flag) {
    s->arr_back = s->arr_back->next;
  }
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

  g2_set_line_width(v->id, 2);
  g2_pen(v->id, COLOR_MOON);
  if (s->arr->next==NULL) {
      p3[0] = 0;
      p3[0] = -MAX_COORD;
      project(p3, c, p1);
      p3[0] = MAX_COORD;
      project(p3, c, p2);
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
    g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);
    p1[0]=p2[0];
    p1[1]=p2[1];
    aux = aux->next;
  }
  p1[1] = p2[1];
  p1[0] = c->vdim[0] + 100 + c->vpos[0];
  g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);

  /*Desenha o objetivo atual*/
  if (s->curr_lp!=NULL) {
    if ((*(list_no**)s->curr_lp->val)->next!=NULL) {
      aux = *(list_no**)s->curr_lp->val;
      p3[0] = ((moon_point *)(aux->val))->c[0];
      p3[1] = ((moon_point *)(aux->val))->c[1];
      project(p3, c, p1);
      aux = (*(list_no**)s->curr_lp->val)->next;
      p3[0] = ((moon_point *)(aux->val))->c[0];
      p3[1] = ((moon_point *)(aux->val))->c[1];
      project(p3, c, p2);
      g2_pen(v->id, COLOR_RED);
      g2_set_line_width(v->id, 4);
      g2_line(v->id,p2[0],p2[1],p1[0],p1[1]);
    }
  }
  g2_set_line_width(v->id, 1);
}



void sfc_draw_labels(surface * s, camera2d * c, view * v) {
  double p[2] = {0};
  list_no * aux;
  aux = s->arr->next;
  while (aux!=NULL) {
    project(((moon_point *)aux->val)->c, c, p);
    g2_pen(v->id, COLOR_CLICK);
    g2_filled_circle(v->id, p[0], p[1], 2);
    g2_pen(v->id, COLOR_BLACK);
    g2_string(v->id,p[0], p[1]+5,((moon_point *)aux->val)->name);
    aux = aux->next;
  }
}


void sfc_clear_lp (surface * s) {
  l_destroy(s->lp);
  s->lp = s->lp_back = l_init(sizeof(void *));
  s->lp_size=0;
}