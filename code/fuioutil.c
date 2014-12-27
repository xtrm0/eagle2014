#include "../include/fuioutil.h"
void clearbuffer() {
  while(getchar()!='\n');
}

//TODO: falta verificar se o numero esta grande ou pequeno demais para ser int
void read_int(char * prompt, int * target, int mini, int maxi) {
  char c;
  begin_read_int:

  fputs(prompt, stdout);
  if (scanf("%d", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_int;
  }
  while((c=getchar())!='\n') {
    if (!isspace(c)) {
      clearbuffer();
      printf("Erro no formato especificado: Não coloque caracteres depois do numero!\n");
      goto begin_read_int;
    }
  }
  if (*target < mini || *target > maxi) {
    printf("O número tem de estar entre %d e %d!\n", mini, maxi);
    goto begin_read_int;
  }
}

//TODO: falta verificar se o numero esta grande ou pequeno demais para ser double
void read_double(char * prompt, double * target, unsigned int conditions) {
  char c;
  begin_read_double:

  fputs(prompt, stdout);
  if (scanf("%lf", target)!=1) {
    clearbuffer();
    printf("Erro no formato especificado!\n");
    goto begin_read_double;
  }
  while((c=getchar())!='\n') {
    if (!isspace(c)) {
      clearbuffer();
      printf("Erro no formato especificado: Não coloque unidades!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_BIGGERTHAN0) {
    if (*target < 0) {
      printf("Introduza um valor positivo!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_BIGGERTHAN100) {
    if (*target < 100) {
      printf("Introduza um valor superior a 100!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_SMALLRTHAN0) {
    if (*target > 0) {
      printf("Introduza um valor negativo!\n");
      goto begin_read_double;
    }
  }

  if (conditions & COND_ALTITUDE) {
    if (*target < 14) {
      printf("Altitude inicial da nave muito baixa!\n");
      goto begin_read_double;
    }
  }
}


void read_string(char * prompt, char * target, size_t min_len, size_t max_len, unsigned int conditions) {
  int flag;
  char * a = calloc (max_len+2,sizeof(char));
  TESTMEM(a);
  do {
    puts(prompt);
    flag = 0;
    a[max_len]='a';
    fgets(a, max_len+1, stdin);
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
    if (conditions ^ COND_NOSPACE) {
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