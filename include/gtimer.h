#ifndef GTIMER_H
#define GTIMER_H
#include "../include/defines.h"
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
/*
  Esta header e usada nas funcoes de sleep de todos os loops da aplicacao
  NOTA: As funcoes para C11 so funcinam em versoes muito recentes do glibc
*/
/*
  Perdemos uma boa quantidade de tempo com este ficheiro de modo a tentar maximizar os seguintes fatores:
  1) Permitir que a aplicacao funcione no maximo de sistemas possiveis
  2) Permitir que a aplicacao gaste o minimo tempo de processador possivel

  Decidimos nao usar o sleep, pois todos os botoes da janela deixam de funcionar, dado que o so verificamos uma vez por segundo se o rato esta a ser clicado. É um problema interno do g2, que não é possível de corrigir sem deixar de o usar para criar as janelas. Uma melhor implementação do g2 teria a possibilidade de usar o modo de eventos do X11.
*/

/*
  Estes defines servem para descobrir qual o tipo de sleep vamos usar
 */
#if _POSIX_C_VERSION >= 199309L
#include <unistd.h>
#else
#ifdef _ISOC11_SOURCE
#include <threads.h>
/* O compilador suporta threads (norma ansi C11). Podemos usar o thrd_sleep para esperar */
#else
/*
  Estamos a compilar para/nalgum sistema estupido. (iex: microprocessador muito antigo)
  Podemos procurar funcoes equivalentes ao nanosleep para sistemas especificos
*/
#endif
#endif

/*
  Representa um clock para usar em loops de logica/desenhar.
  O target_fps indica o numero de fps que queriamos que gtimer atinja.
  O fps indica o numero de fps que estamos a usar atualmente com base no score indicado no cnt.
  Utilização:
    Basicamente, pomos gtimer_begin no inicio do loop
    E gtimer_end no fim do loop.
 */
typedef struct gtimer {
  struct timespec tstart, tend, tsleep, trem;
  double target_fps;
  double fps;
  int cnt;
}gtimer;

gtimer * gtimer_init(double tfps);

/*
  Inicia um clock e devolve o tempo desde o ultimo clock
*/
double gtimer_begin(gtimer *);

/*
  Devolve o tempo em segundos que passou entre os 2 ultimos begin (e necessario que no meio tenha ocorrido um gclock_sleep)
*/
double gtimer_getdt(gtimer *);

void gtimer_sleep(gtimer *);

void gtimer_destroy(gtimer *);

#endif
