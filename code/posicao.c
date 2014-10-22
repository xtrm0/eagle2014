#include<stdio.h>
#include<math.h>


/* nq é a constante de normalização ?de queda?

   nr é a constante de normalização ?de rotação? 

   Fz é a componente vertical de F
  
   Fx é a componente horizontal de F

   Fr é a força ?rotacional?

   g é a aceleração gravítica na lua 

   R é o raio do bicho

   a é o ângulo - positivo no sentido anti-horário*/	
	
/* para o caso de depois sempre fazermos as separações de massa fica a fórmula do momento de inércia aqui*/

	I = 2/5 * m * R * R;

	Fx = 
	Fz = 
	Fr = 
	
	vz_i = vz;
	vx_i = vx;

	a = a + [nr * Fr * R / I]*dt
	
	vz = vz_i + [-nq * Fz * sin(a) / m] * dt;
	vx = vx_i + [-nq * Fx * cos(a)/m - g] * dt;

	posz = posz + [(vz - vz_i)/2] * dt  	
	posx = posx + [(vx - vx_i)/2] * dt   	
	

/* O bertinho diz no ficheiro : "Numa primeira fase obtêm-se 
as forças que são aplicadas e calculam-se as derivadas, que ao serem utilizadas com as velocidades 
lineares e angular no instante t, permite obter as velocidades lineares e angular no instante t+h, 
próximo instante de tempo. Depois com base nas velocidades obtêm-se as deslocações em x(t+h) e 
z(t+h) assim como o ângulo de orientação (atitude) do módulo lunar no instante t+h." como é que a partir das velocidades tiramos o ângulo de orientação? eles não são independentes?*/
