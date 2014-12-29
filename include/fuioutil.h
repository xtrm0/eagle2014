#ifndef _FU_IO_UTIL_HPP
#define _FU_IO_UTIL_HPP
#include "../include/defines.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define COND_COORD     (1<<0)
#define COND_ALTITUDE  (1<<1)
#define COND_VELOC     (1<<2)
#define COND_MASS_S    (1<<3)
#define COND_MASS_C    (1<<4)
#define COND_ANGLE     (1<<5)

/*
  Le um double do teclado

  Nao desiste enquando nao tiver um double na forma valida
  O ultimo argumento e recebido como bitmask
*/
void read_double(char *, double *, unsigned int);

/*
  Le um inteiro do teclado

  Nao desiste enquando nao tiver um inteiro na forma valida
*/
void read_int(char * prompt, int * target, int mini, int maxi);



#define COND_NOSPACE (1<<0)
/*
Le uma string
Nao desiste enquanto nao a receber de forma correta
*/
void read_string(char * prompt, char * target, size_t min_len, size_t max_len, unsigned int conditions);

/*
  void clearbuffer(void)
  Limpa o buffer ate ao proximo '\n'
*/
void clearbuffer();

int ask_yes_no();
#endif