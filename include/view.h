#ifndef VIEW_H
#define VIEW_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include "geometry.h"
#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define COLOR_GUI   2
#define COLOR_RED   3
#define COLOR_MOON  4
#define COLOR_COMB_T 5
#define COLOR_COMB_R 6
#define COLOR_CLICK 7
/*
  Estrutura que representa uma janela que esta a ser mostrada ao utilizador
  Esta janela implementa double buffering atravez dos metodos begin e end
  (W,H): Dimensoes da janela
  id: Id da janela virtual a desenhar, alocada no init pela libg2
  dev: id da janela fisica
  name: titulo da janela
*/
typedef struct view {
  int W, H;
  int id, dev;
  char * name;
} view;

/*
  Inicializa um view:
    Abre a janela e o virtual device e ligaos
    Limpa as cores iniciais do g2
    Aloca as cores base do nosso programa
 */
view * view_init(int,int,char *);

/*
  Destroi uma view:
    Desliga a janela do virtual device
    Fecha o virtual device e a janela
  Nota: Retorna erro caso a janela tenha sido fechada pelo sistema de janelas (O g2 nao capta eventos, pelo que e impossivel saber se a janela foi fechada ou nao)
 */
void view_destroy(view *);

/*
  Inicializa a fase de desenho numa janela
 */
void view_begin(view * v);

/*
  Acaba a fase de desenho de uma janela.
  Pede ao X11 para desenhar a buffer grafica do g2 para o ecrã.
  (em conjunto com o view_begin é uma micro implementação de um double buffer)
 */
void view_end(view * v);



/*
Estes defines foram copiados <X11/X.h> e representam os valores possiveis para bitmasks do mouse_button devolvido pelo g2_query_pointer( que basicamente chama uma funcao do x11)
É possível que noutro pc estes defines tenham valores diferentes, se se estiver a usar uma versão modificada do X11, mas acho que isso é improvável
*/
#define NoEventMask			0L
#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)
#define EnterWindowMask			(1L<<4)
#define LeaveWindowMask			(1L<<5)
#define PointerMotionMask		(1L<<6)
#define PointerMotionHintMask		(1L<<7)
#define Button1MotionMask		(1L<<8)
#define Button2MotionMask		(1L<<9)
#define Button3MotionMask		(1L<<10)
#define Button4MotionMask		(1L<<11)
#define Button5MotionMask		(1L<<12)
#define ButtonMotionMask		(1L<<13)
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15)
#define VisibilityChangeMask		(1L<<16)
#define StructureNotifyMask		(1L<<17)
#define ResizeRedirectMask		(1L<<18)
#define SubstructureNotifyMask		(1L<<19)
#define SubstructureRedirectMask	(1L<<20)
#define FocusChangeMask			(1L<<21)
#define PropertyChangeMask		(1L<<22)
#define ColormapChangeMask		(1L<<23)
#define OwnerGrabButtonMask		(1L<<24)


#endif
