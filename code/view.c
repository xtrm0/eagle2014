#include "../include/view.h"

view * view_init(int w, int h, char * name) {
  view * v = (view *)malloc(sizeof(view));
  TESTMEM(v);
  memset(v,0,sizeof(view));
  v->W=w;
  v->H=h;
  v->name = name;
  v->dev = g2_open_X11X(w, h, 0, 0, name, name, NULL, 0, 0);
  v->id = g2_open_vd();
  g2_attach(v->id, v->dev);
  g2_set_auto_flush(v->id, 0);
  g2_clear_palette(v->dev);
  /*cores: */
  /*Usámos o programa gpick para tirar as cores a partir do pdf */
  /*Na fase final, caso o professor concordar, trataremos de usar um design diferenta para a aplicacao */
  g2_ink(v->dev, 0.0, 0.0, 0.0); /*0 #000000 */
  g2_ink(v->dev, 1.0, 1.0, 1.0); /*1 #FFFFFF */
  g2_ink(v->dev, 1.0, 0.8, 0.6); /*2 #FFCC99 */
  g2_ink(v->dev, 1.0, 0.0, 0.0); /*3 #FF0000 */
  g2_ink(v->dev, 0.8, 0.4, 0.2); /*4 #CC6633 */
  g2_ink(v->dev, 1.0, 0.4, 0.2); /*5 #FF6633 */
  g2_ink(v->dev, 0.05, 0.75, 0.91); /*5 diamond blue */
  return v;
}

void view_destroy(view * v) {
  if (v!=NULL) {
    g2_close(v->dev);
    g2_close(v->id);
    free(v);
  }
}

void view_begin(view * v) {
  /*TODO: 
  */
  /*
    Esta funcao vai servir para verificar se a janela para onde vamos desenhar ainda existe, ou se foi fechada pelo utilizador.
    Caso tenha sido fechada, podemos fazer 1 de duas coisas (a definir):
      1) Acabar o programa e mostrar um erro
      2) Voltar a imprimir a janela e imprimir um warning
  */
}
void view_end(view * v) {
  g2_flush(v->id);
}
