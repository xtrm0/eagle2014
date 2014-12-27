#ifndef _LIST_HPP
#define _LIST_HPP
#include <stdlib.h>
#include <string.h>
#include "defines.h"
typedef struct LIST_NO {
  void * val;
  struct LIST_NO * next;
} list_no;
/*
Inicializa uma lista
*/
list_no * l_init(size_t bytes);
/*
Adiciona um valor a lista, a seguir ao valor base
*/
void l_push_next(list_no * base, void * val, size_t bytes);
/*
Adiciona um valor ao fim da lista
*/
void l_push_back(list_no * base, void * val, size_t bytes);
/*
Apaga todos os elementos da lista (excepto a base);
*/
void l_destroy(list_no * base);
/*
Encontra um elemento da lista usando a funcao f, (devolve o parent do elemento encontrado)
*/
list_no * l_find(list_no * base, int (*f)(void *,void *), void * arg);
/*
Cria uma copia da lista base na lista novabase
*/
void l_copy(list_no * base, list_no * novabase, size_t bytes);
/*
Devolve um ponteiro para o ultimo elemento da lista
*/
list_no * l_back(list_no *base);
#endif