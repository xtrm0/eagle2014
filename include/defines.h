#ifndef DEFINES_H
#define DEFINES_H
#include <stdio.h>
#include <errno.h>
/*
  É preciso definir aqui a seguinte macro para escolher o tipo de compilação:
    compativel com POSIX: #define _POSIX_C_VERSION 199309L (199309 e a primeira versao do posix que define o nanosleep)
    C11 ou superior: #define _ISOC11_SOURCE 1
    outro: nao definir nada

  Quando pomos o gcc em modo ansi ele deixa de incluir as bibliotecas POSIX.
  Para pedir-lhe para incluir as bibliotecas utilizamos o define _POSIX_C_SOURCE com o valor de POSIX mais baixo que suporta nanosleep

  Precisamos do nanosleep, pois o c89 nao tem funcoes que permitam a aplicacao guardar informacao sobre o tempo com precisao superior a segundos
  e ao mesmo tempo fazer 'sleep'. Como tal, incluimos as header do POSIX e compilamos com linkagem da biblioteca librt.so, incluido por definicao na pseudo-package ubuntu-minimal, incluida em todos os sistemas baseados no ubuntu (pelo menos) desde a versao 10.04(iex: xubuntu)

  Para alem disso, a funcao usleep() foi deprecada com o POSIX-2001 (o nanosleep faz o mesmo e tem maior precisao)

*/
//#define _POSIX_C_SOURCE 199309L
#define FILE_HEADLINE "tempo [s]         x [m]         z [m]        vx [m]        vz [m]   atitude [graus]     fuel [kg]\n"




/*
  Funcoes do preprocessador uteis:
*/
/*Teste de memoria*/
#define TESTMEM(s) if (s == NULL) {\
  fprintf(stderr, "(3x23) Erro detetado: Memory Access Error!");\
  exit(ENOMEM);\
}
/*General math functions*/
#define max(a,b) ((a) >= (b) ? (a) : (b))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define distsq(a,b) (((a[0])-(b[0]))*((a[0])-(b[0]))+((a[1])-(b[1]))*((a[1])-(b[1])))
#define fast_abs(a)  ((a) > 0 ? (a) : -(a))
#define angle(a,b)   atan2(((b[1])-(a[1])),((b[0])-(a[0])))
/*definicao para transformar coisas do preprocessador em strings*/
#define TOSTRING(s)  #s
#define PRETOSTRING(s) TOSTRING(s)

/*Definição para comparar doubles:*/
#define SIGMA 0.0000001


/*Definicoes de fisica e matematica */
/*Maxima coordenada em qualquer eixo*/
#define MAX_COORD 10000000
#define LIGHT_SPEED 300000000
#define AUX_LINES_ZOOM 30
/*Constantes de aterragem */
/*5 graus: */
#define MAXROT 0.0872664626
#define LAND_MAXVZ 0.1
#define LAND_MAXVX 0.05

/*Bitmasks partilhadas por diversos ficheiros*/
  /* Bitmasks para verificar se a spaceship ja foi inicializada*/
#define INIT_SPACESHIP 1
#define INIT_SURFACE   2
#define INIT_LANDING   4

  /* Bitmasks para controlar o modo de jogo*/
#define MODE_COCKPIT   1
#define MODE_GRAPHIC   2


/* FONTS SIZES */
#define PLANNER_FONT_SIZE 12


#endif
