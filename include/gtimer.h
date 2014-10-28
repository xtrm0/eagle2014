#ifndef GTIMER_H
#define GTIMER_H
#include "../include/defines.h"
/*
  Esta header e usada nas funcoes de sleep de todos os loops da aplicacao
  TODO: O gclock_sleep esta a funcionar mal, Nao podemos usar um double para calcular quanto tempo queremos dormir
*/
/*
  Perdemos uma boa quantidade de tempo com este ficheiro de modo a tentar maximizar os seguintes fatores:
  1) Permitir que a aplicacao funcione no maximo de sistemas possiveis
  2) Permitir que a aplicacao gaste o minimo tempo de processador possivel

  Decidimos nao usar o sleep, pois todos os botoes da janela deixam de funcionar, dado que o so verificamos uma vez por segundo
  se o rato esta a ser clicado. É um problema interno do g2, que não é possível de corrigir sem deixar de o usar para criar as janelas.
*/
#if _POSIX_C_VERSION >= 199309L
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
typedef struct gtimer {
  struct timespec tstart, tend, tsleep, trem;
}gtimer;
#else
#ifdef _ISOC11_SOURCE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
typedef struct gtimer {
  struct timespec tstart, tend, tsleep, trem;
}gtimer;
/*
  O compilador suporta threads (norma ansi C11). Podemos usar o thrd_sleep para esperar enquanto o processador dorme
*/
#else
/*
  Estamos a compilar para/nalgum sistema estupido. (iex: microprocessador muito antigo)
  Podemos procurar funcoes equivalentes ao nanosleep para sistemas especificos
*/
#endif
#endif

gtimer * gtimer_init();
/*
  Inicia um clock e devolve o tempo desde o ultimo clock
*/
double gtimer_begin(gtimer *);

/*
  Devolve o tempo em segundos que passou entre os 2 ultimos begin (e necessario que no meio tenha ocorrido um gclock_sleep)
*/
double gtimer_getdt(gtimer *);

void gtimer_sleep(gtimer *, double sleeptime);

void gtimer_destroy(gtimer *);

#endif
