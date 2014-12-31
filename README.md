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
  #Correr:
  gcc -O2 -Wall code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/button.c code/grafico.c code/surface.c code/gtimer.c code/game_engine.c  code/list.c code/surface_planner.c code/fuioutil.c -lg2 -lm -lrt -o eagle2014

```
ou
```
  ./compile.sh
```



Aspectos a ter em conta:
================
+Ao criarmos o trabalho, verificamos que estavamos com memory leaks gigantescas. Utilizamos a ferramenta valgrind e constatamos que a função g2_set_font_size() não liberta a memória que consome, pelo que a utilizamos apenas quando estritamente necessário e comentámos todos os locais onde tinhamos usado esta função inicialmente
+O mesmo acontece com a função g2_open_X11 e g2_open_X11X
+Os erros acima constatados são um bom motivo para não se utilizar o g2 e utilizar-se o X11 diretamente.




================
Metodologia do projeto
================
1) Verificar colisoes da nave:
	Arranja-se um poligono que contenha a nave (wikipedia:colision shape). Esse poligono vai ser constituido por N arestas.
	Depois, para cada aresta da superficie lunar (M) verifica se colide com alguma das arestas do poligono.
	Pseudo-codigo:
		De i=0 ate (N-1):
		 		De j=0 ate (M-1):
		 			Se interceptam(nave.arestas[i], lua.arestas(j)) {
		 				entao a nave esta a tocar no chao
		 			} else {
		 				nao esta a tocar no chao
		 			}
	[Mais fixe:] Outra coisa que teem de ter em conta e que se a aplicacao nao atualizar suficientemente rapido, e possivel que a nave ultrapasse a superficie lunar sem colidir. Para isso, para cada arestas antes e depois de uma atualizacao da posicao cria-se um retangulo (formado pelo espaco que os vertices dessa aresta percorreram e pela antiga e nova posicao da aresta), e aplica-se o algoritmo descrito acima.

	2) Fazer o zoom/desenhar a nave e a superficie lunar a escala. 
       Criamos a biblioteca geometry que utilizando algebra linear nos facilida as coisas.
		Em primeiro lugar, representamos a nave e a lua em coordenadas reais (em metros). De seguida, escolhemos um retangulo nas mesmas coordenadas (que vamos passar a chamar de camara), que representa a area que vai ser desenhada para o ecra. A camara tera coordenadas X,Y no ref. real, e comprimento e largura C, L. Depois, vamos ter a janela, com o seu proprio referencial, de coordenas (0,0) ate (W,H).
		Para desenhar-mos uma aresta na janela, calculamos as coordenadas dos seus vertices no referencial da janela e pedimos ao g2 para desenhar a aresta.
		A sequencia de transformacao para calcularem as coordenadas de um ponto P na janela, vao ser:
			P = P - (X,Y) 
			P = P / (C,L) = (p.x / C, p.y / L)  
			P = P * (W,H) = (p.x * W, p.y * H) 
			P = P + (a,b), sendo (a,b) o local no ecra onde esta a view 
		
		O metodo descrito para calcular o retangulo da camara encontra-se no game_engine e no geometry

	3) Calcular a variacao das posicoes da nave, again, existem muitas maneiras de fazer isto, a mais simples e a seguinte:
		http://en.wikipedia.org/wiki/Verlet_integration 
