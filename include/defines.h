#ifndef DEFINES_H
#define DEFINES_H
/*
  É preciso definir aqui a seguinte macro para escolher o tipo de compilação:
    compativel com POSIX: #define _POSIX_C_VERSION 199309L (199309 e a primeira versao do posix que define o nanosleep)
    C11 ou superior: #define _ISOC11_SOURCE 1
    outro: nao definir nada
#define _ISOC11_SOURCE
*/
#define _POSIX_C_SOURCE 199309L
#define _POSIX_C_VERSION 199309L

/*
  TODO: Remover isto quando o timer.h estiver pronto
  Quando pomos o gcc em modo ansi ele deixa de incluir as bibliotecas POSIX.
  Para pedir-lhe para incluir as bibliotecas utilizamos o define _POSIX_C_SOURCE com o valor de POSIX mais baixo que suporta nanosleep

  Precisamos do nanosleep, pois o c89 nao tem funcoes que permitam a aplicacao guardar informacao sobre o tempo com precisao superior a segundos
  e ao mesmo tempo fazer 'sleep'. Como tal, incluimos a POSIX.

  Para alem disso, a funcao usleep() foi deprecada com o POSIX-2001
*/
/*As linhas acimas sao inuteis, mas impedem que o compilador mande warnings case passe aqui duas vezes */
#define FILE_HEADLINE "tempo [s]         x [m]         z [m]        vx [m]        vz [m]   atitude [graus]     fuel [kg]\n"

#define TESTMEM(s) if (s == NULL) {\
  fprintf(stderr, "(3x23) Erro detetado: Memory Access Error!");\
  exit(ENOMEM);\
}
#endif
