#include "../include/surface_planner.h"
void s_p_update_window(surface * s, camera2d * c, view * v) {
	char str[60];
	view_begin(v);
		g2_clear(v->id);
		g2_pen(v->id, COLOR_MOON);
		sfc_draw(s,c,v);
		g2_pen(v->id, COLOR_RED);
		sfc_draw_labels(s,c,v);
		g2_pen(v->id, COLOR_BLACK);
		sprintf(str, "Numero de pontos: %ld", (long int)s->arr_size);
		g2_string(v->id, 20, v->H-20, str);
		sprintf(str, "Numero de pontos de alunagem: %ld", (long int)s->lp_size);
		g2_string(v->id, 20, v->H-40, str);
	view_end(v);
}

void read_mp(moon_point * p, surface * s) {
	int flag;
  do {
  	flag = 0;
  	read_string("Insira o nome do ponto [sem espacos]:", p->name, 4, MAX_POINT_NAME, COND_NOSPACE);
  	if (l_find(s->arr,&arr_find_byname,p->name)!=NULL) {
  		printf("Ja existe um ponto com esse nome!\n");
  		flag = 1;
  	}
  } while (flag);
  read_double("Introduza a coordenada x do ponto: ", p->c, COND_COORD);
  read_double("Introduza a coordenada y do ponto: ", p->c+1, COND_COORD);
}

void surface_planner_menu_text() {
	printf("[ Modo de desenho da superficie lunar ]\n"
		"0 - Acabar superficie lunar e gravar para ficheiro\n"
		"1 - Adicionar ponto\n"
		"2 - Remover ponto\n"
		"3 - Imprimir pontos\n"
		"4 - Definir ponto de alunagem\n"
		"5 - Imprimir sequencia dos pontos de alunagem\n"
		"6 - Nova sequencia de alunagem (apaga a sequencia de alunagem atual)\n"
		"7 - Nova lua\n"
		"opcao: ");
}

int read_surface_from_file(surface * s) {
  double o[2];
  size_t readed=0;
  FILE * fin;
  moon_point aux;
  char line[301];
  if ((fin = fopen(FILENAME_MOON, "r")) == NULL) {
    fprintf(stderr, "E: Não foi possível abrir o ficheiro");
    return 1;
  }

  if (fgets(line, 300, fin)==NULL) {
    fprintf(stderr, "W: Erro na leitura do ficheiro: Ficheiro Vazio!\n");
  }
  line[300]='\0';
  if (line[strlen(line)-1]!='\n') {
    fprintf(stderr, "W: Linha muito longa na leitura do ficheiro\n");
    while(fgetc(fin)!='\n');
  }
  if (strcmp(line, FILE_MOON_HEADLINE)){
    fprintf(stderr, "W: A linha de coluna nao se encontra igual à do programa!\n");
  }

  s->lp_size = 0;
  s->arr_size = 0;
  l_destroy(s->arr);
  l_destroy(s->lp);
  s->arr = s->arr_back = l_init(sizeof(moon_point));
  s->lp = s->lp_back = l_init(sizeof(void *));

  while (fgets(line, 300, fin)) {
  	line[300]='\0';
    if (line[strlen(line)-1]!='\n') {
      fprintf(stderr, "W: Linha muito longa na leitura do ficheiro\n");
      while(fgetc(fin)!='\n');
      continue;
    }
    if (strchr(line,' ')-line>=30 || strchr(line,' ')-line < 4){
    	fprintf(stderr, "W: Linha invalida na leitura do ficheiro\n");
    	continue;
    }
    if (sscanf(strchr(line,' '),"%lf %lf", o, o+1)!=2) {
      fprintf(stderr, "W: Linha invalida na leitura do ficheiro\n");
      continue;
    }
    strncpy(aux.name, line, 29);
    aux.name[29]=' ';
    *strchr(aux.name, ' ')='\0';
    aux.c[0]=o[0];
    aux.c[1]=o[1];
    sfc_add_point_sorted(s, &aux);
    readed++;
  }
  fclose(fin);
  printf("Carregados %d pontos!", (unsigned int)readed);
  return 0;
}

void save_surface_to_file(surface * s) {
  FILE *fileout;
  list_no * aux;
  moon_point * p;
  if ((fileout = fopen (FILENAME_MOON, "w")) == NULL) {
    fprintf(stderr, "E: Não foi possível abrir o ficheiro '" FILENAME_MOON "'\n");
    return;
  }
  fprintf(fileout, FILE_MOON_HEADLINE);
  aux = s->arr;
  while (aux->next!=NULL) {
  	p = aux->next->val;
  	fprintf(fileout, "%s                              %14.3f %14.3f\n", p->name, p->c[0], p->c[1]);
  	aux = aux->next;
  }
  fclose(fileout);
}

int surface_planner_menu(surface * s) {
	char opcao, c;
	char nm[MAX_POINT_NAME];
	moon_point aux;
	list_no * tmp;
	moon_point * ap;
	surface_planner_menu_text();
	c= opcao = getchar();
	while(c!='\n') {
		c=getchar();
		if (!isspace(c)) {
		  clearbuffer();
		  printf("Erro na leitura da opcao!\n");
		  return 1;
		}
	}
	switch (opcao) {
	case '0':
		save_surface_to_file(s);
		return 0;
	break;
	case '1':
		if (s->lp_size!=0) {
			printf ("W: isto vai apagar todos os pontos de alunagem!\n Deseja continuar?");
			if (ask_yes_no()==0)
				break;
			sfc_clear_lp(s);
		}
		read_mp(&aux, s);
		sfc_add_point_sorted(s, &aux);
	break;
	case '2':
		if (s->lp_size!=0) {
			printf ("W: isto vai apagar todos os pontos de alunagem!\n Deseja continuar?");
			if (ask_yes_no()==0)
				break;
			sfc_clear_lp(s);
		}
		read_string("Insira o nome do ponto [sem espacos]:", nm, 4, MAX_POINT_NAME, COND_NOSPACE);
		tmp = l_find(s->arr, &arr_find_byname, nm);
		if (tmp == NULL) {
			printf("Ponto nao encontrado!\n");
		} else {
			sfc_remove_arr(s, tmp);
		}
	break;
	case '3':
		tmp = s->arr;
		if (s->arr->next==NULL) {
			printf("Vazio!\n");
			break;
		}
		printf("Nome\tx\tz\n");
		while (tmp->next!=NULL) {
			ap = tmp->next->val;
			printf("%s\t%f\t%f\n", ap->name, ap->c[0], ap->c[1]);
			tmp = tmp->next;
		}
	break;
	case '4':
		read_string("Insira o nome do ponto [sem espacos]:", nm, 4, MAX_POINT_NAME, COND_NOSPACE);
		tmp = l_find(s->arr, &arr_find_byname, nm);
		if (tmp == NULL) {
			printf("Ponto nao encontrado!\n");
		} else if(tmp->next->next==NULL) {
			printf("Ponto nao define aresta: ponto terminal!\n");
		} else if(distsq(((moon_point *)tmp->next->val)->c, ((moon_point *)tmp->next->next->val)->c) < 100) {
			printf("Ponto nao define local de alunagem valido: comprimento da aresta (%fm) inferior a 10m!\n", distsq(((moon_point *)tmp->next->val)->c, ((moon_point *)tmp->next->next->val)->c));
		} else if(!valid_land_line(((moon_point *)tmp->next->val)->c, ((moon_point *)tmp->next->next->val)->c)) { 
			printf("Ponto nao define local de alunagem valido: inclinacao superior a 5 graus!\n");
		} else if (s->lp_back!=s->lp && (tmp->next)==*(list_no**)s->lp_back->val) {
			printf("O ponto nao pode ser o mesmo que o anterior!\n");
		} else {
			sfc_add_lp(s, nm);
			printf("done");
		}
		break;
	case '5':
		if (s->lp_size == 0) {
			printf("Vazio!\n");
			break;
		}
		tmp = s->lp->next;
		printf("%s", ((moon_point*)((*((list_no**)(tmp->val)))->val))->name);
		tmp = tmp->next;
		while (tmp!=NULL) {
			printf("->%s", ((moon_point*)((*((list_no**)(tmp->val)))->val))->name);
			tmp = tmp->next;
		}
		printf("\n");
	break;
	case '6':
		printf("Todos os pontos de alunagem foram apagados!\n");
		sfc_clear_lp(s);
	break;
	case '7':
		s->lp_size = 0;
		s->arr_size = 0;
		l_destroy(s->arr);
    	l_destroy(s->lp);
		s->arr = s->arr_back = l_init(sizeof(moon_point));
 		s->lp = s->lp_back = l_init(sizeof(void *));
 		printf("Nova lua criada!\n");
	default:
		printf("Opcao desconhecida! :S\n");
	break;
	}
	return 1;
}


int surface_planner(surface * s) {
	view * v;
	camera2d * c;
	double minx, miny, maxx, maxy;
	list_no * aux;
	moon_point * tmp;
	read_surface_from_file(s);
	v = view_init(800, 600, "eagle2014 - Desenhar superficie lunar");
  	c = c2d_init(600, 600, 0, 0, 800, 600, 0, 0);
  	g2_set_font_size(v->id, PLANNER_FONT_SIZE);
  	s_p_update_window(s,c,v);
  	do {
		minx = -600;
		miny = -800;
		maxx = 600;
		maxy = 800;
		if (s->arr_size!=0) {
			aux = s->arr->next;
			minx=miny=INT_MAX;
			maxx=maxy=INT_MIN;
			while (aux!=NULL) {
				tmp = (moon_point *) aux->val;
				minx = min(minx, tmp->c[0]);
				maxx = max(maxx, tmp->c[0]);
				miny = min(miny, tmp->c[1]);
				maxy = max(maxy, tmp->c[1]);
				aux = aux->next;
			}
		}
		c2d_fit(c,minx,miny,maxx-minx,maxy-miny);
		c2d_zoom(c, 1.10);
  		s_p_update_window(s,c,v);
  	} while (surface_planner_menu(s));
  	view_destroy(v);
  	c2d_destroy(c);
  	return (s->arr_size==0 ? 0 : INIT_SURFACE)|(s->lp_size==0 ? 0 : INIT_LANDING);
}