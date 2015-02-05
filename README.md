eagle2014
=========

A 2d lunar landing simulator made for our programming class.

=========
This project was brought to you by:

Numero:_________80816; Nome:Diogo_Gonçalves; Mestrado:_MEAer;

Numero:_________81861; Nome:__Afonso_Tinoco; Mestrado:_MEAer;


How to compile:
==========
There are several possible ways to compile the program:
+ By using the tool make [recomended]:
```
  make clean
  make all
```

+ Just by using gcc:
```
  #just run:
  gcc -O2 -Wall code/main.c code/menu.c code/geometry.c code/spaceship.c code/view.c code/button.c code/grafico.c code/surface.c code/gtimer.c code/game_engine.c  code/list.c code/surface_planner.c code/fuioutil.c -lg2 -lm -lrt -lX11 -o eagle2014
```
or
```
  ./compile.sh
```



Warnings:
================
+During the testing phase, we verified we were having huge memory leaks. We used the tool valgrind and concluded that the function g2_set_font_size() does not free the memory it consumes. Therefore, we used it as litle as possible.
+The same happens with the functions g2_open_X11 and g2_open_X11X



================
Project metodology
================
1) Colision detection:
	First we create a small polygon that contains the spaceship (wikipedia:colision shape). Let N be the number of edges of such polygon.
	Then, for each edge of the moon surface(M) we check if it intercepts any of the polygon edges.
	Pseudo-code:
		for i=0..(N-1):
		 		for j=0..(M-1):
		 			if intercept(spaceship.edges[i], moon.edges[j]) {
		 				then the spaceship has colided with the ground
		 			} else {
		 				the spaceship is flying
		 			}
	[Cooler Version:] Another thing to take care for, is that if the game does not update fast enough, the spaceship migth step through the moon floor without coliding. To prevent such a case we need to also check for the colision with the edges formed by the displacement of the colision shape vertexes

	2) zoom: 
        We created the camera utility in our geometry lib, that soothes the process.
		Girst we represent the spaceship and the moon using real coordinates (in meters). Thenm we pick a rectangle in the same referential (camera), that represents the part of the real referential that is going to be draw to the screen
		The camera will have coordinates X,Y on the real ref., and measures C by L. Then, we will have the window, with its own referential, of coordinates (0,0) to (W,H).
		In order to draw an edge to the screen, we calculate the coordinates of its vertexes on the window referential, and then ask g2 to draw the edge.
		The sequence of transformations to calculate the coordinates of point P on the window coordinates, given the real world coordinates are:
			P = P - (X,Y) 
			P = P / (C,L) = (p.x / C, p.y / L)  
			P = P * (W,H) = (p.x * W, p.y * H) 
			P = P + (a,b), beeing (a,b) the point were we want our view to begin 
		
		Further description can be found on the code in game_engine.c/h and geometry.c/h
	3) Physical simulation. Again there are several way to do this. We used verlet integration of order 2:
		http://en.wikipedia.org/wiki/Verlet_integration 
