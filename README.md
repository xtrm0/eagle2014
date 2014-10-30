eagle2014
=========

A 2d lunar landing simulator made for our programming class.

=========
Projeto realizado por:

Numero:_________80816; Nome:Diogo_Gonçalves; Mestrado:_MEAer;

Numero:_________81861; Nome:__Afonso_Tinoco; Mestrado:_MEAer;


Como compilar o programa:
==========
É possível compilar o programa de duas formas, consoante as configurações da máquina de teste:
+ Forma recomendada - usando o utilitário make:
```
  make clean
  make all
```

+ Forma tradicional - usando apenas o gcc:
```
  gcc -O2 -Wall -pedantic -ansi code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/cockpit.c code/button.c code/grafico.c code/surface.c code/gtimer.c -lg2 -lm -lrt -o eagle2014
```



Aspectos a ter em conta:
================
+Ao criarmos o trabalho, verificamos que estavamos com memory leaks gigantescas. Utilizamos a ferramenta valgrind e constatamos que a função g2_set_font_size() não liberta a memória que consome, pelo que a utilizamos apenas quando estritamente necessário e comentámos todos os locais onde tinhamos usado esta função inicialmente
+O mesmo acontece com a função g2_open_X11 e g2_open_X11X
+Os erros acima constatados são um bom motivo para não se utilizar o g2 e utilizar-se o X11 diretamente.
