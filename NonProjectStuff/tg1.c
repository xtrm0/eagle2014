/*
This code was adapted from the g2 examples, i.e, g2_test.c
that is available from the site g2.sourceforge.net
To compile and to link this example, use
gcc -ansi -pedantic -Wall tg1.c -lg2 -o tg1 */
#include <stdio.h>
#include <g2.h> /* To work with functions from g2 library */
#include <g2_X11.h> /* To open the physical device */
int main(void) {
  int i; /* Use for counting, look at the code */
  char str[256]; /* This is a string variable */
  int d, dev; /* To hold information from the virtual
  and physical devices */
  printf("\nG2_VERSION %s\n", G2_VERSION);
  printf("Open ..X11 device");
  dev=g2_open_X11(775, 575);
  d=g2_open_vd(); /* open virtual device */
  g2_clear(d);
  g2_set_font_size(d, 300);
  /* attach the virtual device with the physical device */
  g2_attach(d, dev);
  g2_set_auto_flush(d,0); /* Used to automatic refreshing */
  printf("\n");
  /* This is the code where action is taking place */
  for(i=0;i<27;i++) {
      g2_pen(d, i); /* set color */
      g2_filled_circle(d, i*20+10, 550-i*20, 10); /* circle */
      g2_pen(d, 1);
      g2_circle(d, i*20+10, 550-i*20, 10);
      sprintf(str, "%d", i); /* this is to convert into a string */
      g2_string(d, i*20+7, 21, str);/* and to write it on the device */
    }
  g2_flush(d);
  printf("\nDone.\n[Enter]\n");
  getchar();
  g2_close(d);
  return 0;
}
