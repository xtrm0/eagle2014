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
/*
  Estrutura que representa uma janela que esta a ser mostrada ao utilizador
  Esta janela implementa double buffering atravez dos metodos begin e end
  (W,H): Dimensoes da janela
  id: Id da janela a desenhar, alocada no init pela libg2
*/
typedef struct view {
  int W, H;
  int id, dev;
  char * name;
} view;


view * view_init(int,int,char *);
void view_destroy(view *);
void view_begin(view * v);
void view_end(view * v);
//TODO: void map2d(view * c, camera * p, double p[4], double r[4]);



//ESTES DEFINES FORAM COPIADOS DE X11/X.h
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
