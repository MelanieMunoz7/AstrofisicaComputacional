#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*Variables locales*/
double aceleracionGravedad= 9.8; 
double velocidadEnXInicial; 

/*Rutina*/
//Esto desarolla unos pasos sin arrojar resultados, solo lo almacena en disco duro 

void imprimirDatosEnArchivo(FILE *archivo, double tiempoLocal, double velocidadEnYLocal, double posicionEnXLocal, double posicionEnYLocal)
{
    fprintf(archivo,"%16.8lf\t %16.8lf\t %16.8lf\t %16.8lf\t\n", 
    tiempoLocal, velocidadEnYLocal,posicionEnXLocal,posicionEnYLocal);
}

double calcularEnergia(double,double, double); //Reserva el espacio de memoria inlcuso sin asignarle nombre al duoble


int main(void) //Esta el void porque la digo a C que no almace espacio en RAM
{
    //Condiciones inciales
    double posicionEnXInicial = 0.0; 
    double posicionEnYInicial = 10.0; 
    double velocidadEnYInicial=0.0;

    double tiempoMaximoDeSimulacion= sqrt(2.0*posicionEnYInicial/aceleracionGravedad);
    double tiempo, deltaT;

    double masa=1.0; //kg

    //Variables que van a evolucionar
    double posicionEnX,posicionEnY,velocidadEnY;

    printf("Condiciones inciales: \n\n"); 
    printf("(x_0,y_0)= (%lf, %lf)\n", posicionEnXInicial, posicionEnYInicial);
    printf("(v_0_x,v_0_y)=(%lf, %lf)\n", velocidadEnXInicial, velocidadEnYInicial);
    printf("g= %lf (m/s²)\n",aceleracionGravedad);

    velocidadEnXInicial=1.0; 

    velocidadEnY = velocidadEnYInicial;
    posicionEnX = posicionEnXInicial;
    posicionEnY = posicionEnYInicial;

    printf("Ingrese el numero de puntos para la simulacion\n->");
    int numeroDePuntos;
    scanf("%d", &numeroDePuntos);

    deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;

    switch (numeroDePuntos) /*Esta estructura esta disenada para comparar enteros y cadenas de caracteres*/
    {
        case 20:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 100:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 10000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 100000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 1000000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        case 10000000:
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
        
        default: //En caso de que el usuario no ingrese algunos de los valores anteriores
            numeroDePuntos=1000;
            deltaT= tiempoMaximoDeSimulacion/ numeroDePuntos;
            printf("Simulacion con %d puntos \n", numeroDePuntos);
            printf("con dt= %lf\n", deltaT);
            break;
  
    }
    
    FILE *archivoSimulacion; //Para crear el archivo de texto
    archivoSimulacion = fopen("parabolico.dat","w");

  imprimirDatosEnArchivo(archivoSimulacion, tiempo, velocidadEnY,posicionEnX,posicionEnY);

  double energia;  

  energia = calcularEnergia(masa, posicionEnYInicial,velocidadEnYInicial);
  printf("Energia inicial = %lf J\n",energia);

for(tiempo =deltaT; tiempo <= tiempoMaximoDeSimulacion; tiempo = tiempo+deltaT)
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
     imprimirDatosEnArchivo(archivoSimulacion, tiempo, velocidadEnY,posicionEnX,posicionEnY); 
    
    else
        break;
} 

fclose(archivoSimulacion);
    return 0; 

}

double calcularEnergia(double masaLocal,double posicionEnYLocal, double velocidadEnYLocal)
{
    double energia, magnitudVelocidadAlCuadrado;

    magnitudVelocidadAlCuadrado = pow(velocidadEnXInicial,2) + velocidadEnYLocal*velocidadEnYLocal;

    energia= masaLocal*aceleracionGravedad*posicionEnYLocal+ 0.5*masaLocal*magnitudVelocidadAlCuadrado;

    return energia;
}