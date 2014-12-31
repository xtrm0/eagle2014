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

#if _POSIX_C_SOURCE >= 199309L
#include <unistd.h>
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
#else
#ifdef _ISOC11_SOURCE
/* O compilador suporta threads (C11). Podemos usar o thrd_sleep para esperar
Ha que notar que o glibc ainda nao implementou o threads seguindo o C11, pelo que isto so funcionara no futuro :)
*/
#include <threads.h>
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
#else
/*
  Estamos a compilar para/nalgum sistema estupido. (iex: microprocessador muito antigo)
  Podemos procurar funcoes equivalentes ao nanosleep para sistemas especificos, mas
  nesta caso vamos usar o mysleep
*/
typedef struct gtimer {
  time_t tlu;
  unsigned long int steps; /*Representa o numero de ticks que ja esperou durante este segundo*/
  unsigned long int times;
  double fps;
}gtimer;

/*
  Se nao tivermos bibliotecas de tempo com precisao podemos ter segundos em que a velocidade de jogo esta entre 0,5x e 2x o que e suposto.
  Para alem disso o tempo cpu que o sistema concede a aplicacao nao e sempre o mesmo, pelo que serao de esperar erros ainda maiores
  A melhor forma de corrigir isto e usar o nanosleep(nao usamos usleep, pois o nanosleep tem maior precisao)
  Este metodo nao foi testado e nao aconselhamos a usalo
*/
#endif
#endif




gtimer * gtimer_init(double tfps, int pts, int modo);

double gtimer_begin(gtimer *);

double gtimer_getdt(gtimer *);

void gtimer_sleep(gtimer *);

void gtimer_destroy(gtimer *);

#endif
