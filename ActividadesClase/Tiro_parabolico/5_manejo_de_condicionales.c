#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double posicionEnXInicial = 0.0; 
    double posicionEnYInicial = 10.0; 

    double velocidadEnXInicial=1.0; 
    double velocidadEnYInicial=0.0;

    double aceleracionGravedad= 9.8; 

    double tiempoMaximoDeSimulacion= sqrt(2.0*posicionEnYInicial/aceleracionGravedad);
    double tiempo, deltaT=0.1;

    //Variables que van a evolucionar
    double posicionEnX,posicionEnY,velocidadEnY;

    printf("Condiciones inciales: \n\n"); 
    printf("(x_0,y_0)= (%lf, %lf)\n", posicionEnXInicial, posicionEnYInicial);
    printf("(v_0_x,v_0_y)=(%lf, %lf)\n", velocidadEnXInicial, velocidadEnYInicial);
    printf("g= %lf (m/s²)\n",aceleracionGravedad);

    velocidadEnY = velocidadEnYInicial;
    posicionEnX = posicionEnXInicial;
    posicionEnY = posicionEnYInicial;

    printf("%18s %18s %18s %18s\n", "t", "V_y","x","y");
for(tiempo = 0.0; tiempo <= tiempoMaximoDeSimulacion; tiempo = tiempo+deltaT)
{
    velocidadEnY = velocidadEnY - aceleracionGravedad*deltaT;
    posicionEnX = posicionEnX + velocidadEnXInicial*deltaT;
    posicionEnY = posicionEnY + velocidadEnY*deltaT;

    //Condicion para que el delta no haga que la masa continue
    /*if (posicionEnY <= 0.0)
        break;
    */
        //De una forma mas inteligente
    if (posicionEnY >= 0.0)
    {
     printf("%16.8lf\t %16.8lf\t %16.8lf\t %16.8lf\t\n", tiempo, velocidadEnY,posicionEnX,posicionEnY); //para hacer que en la salida hayan 8 digitos decimales y 15 espacio   
    }
    else
    {
        break;
    }
} 

    return 0; 

}