#ifndef DEFINES_H
#define DEFINES_H
#define _POSIX_C_SOURCE 199309L
/*
  Quando pomos o gcc em modo ansi ele deixa de incluir as bibliotecas POSIX.
  Para pedir-lhe para incluir as bibliotecas utilizamos o define _POSIX_C_SOURCE com o valor de POSIX mais baixo que suporta nanosleep

  Precisamos do nanosleep, pois o c89 nao tem funcoes que permitam a aplicacao guardar informacao sobre o tempo com precisao superior a segundos
  e ao mesmo tempo fazer 'sleep'. Como tal, incluimos a POSIX.

  Para alem disso, a funcao usleep(), a unica de c que permite o computador fazer sleep com precisao aceitavel para simulacoes, foi deprecada com
  o POSIX-2001
*/
/*As linhas acimas sao inuteis, mas impedem que o compilador mande warnings case passe aqui duas vezes */
#define FILE_HEADLINE "tempo [s]         x [m]         z [m]        vx [m]        vz [m]   atitude [graus]     fuel [kg]\n"

#define TESTMEM(s) if (s == NULL) {\
  fprintf(stderr, "(3x23) Erro detetado: Memory Access Error!");\
  exit(ENOMEM);\
}
#endif
