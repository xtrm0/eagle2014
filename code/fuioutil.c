#include "../include/fuioutil.h"
void clearbuffer() {
  while(getchar()!='\n');
}

void read_int(char * prompt, int * target, int mini, int maxi) {
  char c;
  int flag;

  do {
    flag=0;
    fputs(prompt, stdout);
    if (scanf("%d", target)!=1) {
      clearbuffer();
      printf("Erro no formato especificado!\n");
      flag=1; continue;
    }

    while((c=getchar())!='\n') {
      if (!isspace(c)) {
        clearbuffer();
        printf("Erro no formato especificado: Não coloque caracteres depois do numero!\n");
        flag=1; break;
      }
    }
    if (flag) continue;

    if (*target < mini || *target > maxi) {
      printf("O número tem de estar entre %d e %d!\n", mini, maxi);
      flag=1; continue;
    }
  } while (flag);
}

void read_double(char * prompt, double * target, unsigned int conditions) {
  int flag;
  char c;

  do {
    flag=0;
    fputs(prompt, stdout);
    if (scanf("%lf", target)!=1) {
      clearbuffer();
      printf("Erro no formato especificado!\n");
      flag=1; continue;
    }
    while((c=getchar())!='\n') {
      if (!isspace(c)) {
        clearbuffer();
        printf("Erro no formato especificado: Não coloque unidades!\n");
        flag=1; break;
      }
    }
    if (flag) continue;

    if (conditions & (COND_MASS_S|COND_MASS_C)) {
      if (*target < 100) {
        printf("Introduza um valor superior a 100kg!\n");
        flag=1; continue;
      }
      if (*target > 100000) {
        printf("Introduza um valor inferior a 100000kg!\n");
        flag=1; continue;
      }
    }

    if (conditions & (COND_VELOC)) {
      if (*target < -0.1*LIGHT_SPEED || *target > 0.1*LIGHT_SPEED) {
        printf("A simulacao nao suporta velocidades relativistas!\n");
        flag=1; continue;
      }
    }

    if (conditions & (COND_COORD|COND_ANGLE)) {
      if (*target < -MAX_COORD || *target > MAX_COORD) {
        printf("Valor inválido! (tem de estar no intervalo [-" PRETOSTRING(MAX_COORD) "," PRETOSTRING(MAX_COORD) "])\n");
        flag=1; continue;
      }
    }

    if (conditions & COND_ALTITUDE) {
      if (*target < 14) {
        printf("A altitude inicial tem de ser superior a 14m\n");
        flag=1; continue;
      }
    }
  } while(flag);
}


void read_string(char * prompt, char * target, size_t min_len, size_t max_len, unsigned int conditions) {
  int flag;
  char * a = calloc (max_len+2,sizeof(char));
  TESTMEM(a);
  do {
    puts(prompt);
    flag = 0;
    a[max_len]='a';
    if (fgets(a, max_len+1, stdin)==NULL) {
      flag = 1;
      printf("Erro Desconhecido :S");
      continue;
    }
    if (a[max_len]=='\0' && a[max_len-1]!='\n') {
      clearbuffer();
      printf("Input muito comprido (maximo %ld caracteres)", max_len-1);
      flag = 1;
      continue;
    }
    *(strchr(a, '\n')) = '\0';
    if (strlen(a)<min_len) {
      printf("Input muito curto (minimo %ld caracteres)", min_len);
      flag = 1;
      continue;
    }
    if (conditions & COND_NOSPACE) {
      if (strchr(a, ' ')!=NULL || strchr(a, '\t')!=NULL || strchr(a, '\v')!=NULL || strchr(a, '\f')!=NULL || strchr(a, '\r')!=NULL) {
        printf("Espacos nao permitidos (sao considerados todos os espacos)");
        flag = 1;
        continue;
      }
    }
  } while (flag);
  strcpy(target, a);
}

int ask_yes_no() {
  int c,opcao;
  do {
      printf("y/n:");
      c= opcao = getchar();
      if (c!='\n') clearbuffer();

    } while (tolower(opcao)!='y' && tolower(opcao)!='n');
  return (tolower(opcao)=='y' ? 1 : 0);
}