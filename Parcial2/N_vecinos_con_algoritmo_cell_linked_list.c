/*Parcial 2 - Astrofisica Computacional
Punto 2: N vecionos usando el algorimo linked list
Melanie A. Munoz Chavarria*/


//Librerias
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Variables globales
double limDistancia = 100.0; //Esto genera el cuadrado 100x100 que se quiere
const int NumeroPuntos = 1000; //Cantidad de puntos en la distribucion
int LadoCelda; //El tamano de la Celda es LadoCelda * LadoCelda

//Inicializando las funciones adicionales
int inicializa_posiciones(double x[], double y[]);
double distancia_particulas(double xDeReferencia,double yDeReferencia,double xSiguiente, double ySiguiente);
void vecinosParticulaConCeldas(double distanciaMinima, int IndiceParticula,double x[], double y[], double coordenadasEnXCelda[][NumeroPuntos], double coordenadasEnYCelda[][NumeroPuntos]);

//Inicio funcion principal

int main()
{   
    //Definiendo los vectores que alacenaran los puntos
    double x[NumeroPuntos];
    double y[NumeroPuntos];

    //Inicialiazando de forma aleatoria esos puntos
    inicializa_posiciones(x,y);

    //Se le pediran al usuario la distanica minima a la que quiere que esten esos vecinos
    //y el punto del que quier obtener los vecinos
    int IndiceParticula;
    printf("Ingrese el valor del indice de la particula de la cual desea conocer los vecinos:\n");
    scanf("%d",&IndiceParticula);

    //La distanica que ingrese el usuario es (2)**(1/2)*kappa*h
    double distanciaMinima; 
    printf("Ingrese la distancia minima a la que desea encontrar los vecinos:\n");
    scanf("%lf",&distanciaMinima);

    //int kappa = 2;

    //Como el celda esta dada por k*h asi, despejando de la formula de la distancia
    LadoCelda = (distanciaMinima) / (sqrt(2));

    //Definiendo las matrices con las coordenadas en la celda de los puntos 
    double coordenadasEnXCelda[LadoCelda][NumeroPuntos]; 
    double coordenadasEnYCelda[LadoCelda][NumeroPuntos]; 

    //Ahora encontrando los vecinos del punto ingresado
    vecinosParticulaConCeldas(distanciaMinima, IndiceParticula,x,y,coordenadasEnXCelda,coordenadasEnYCelda);

    return 0;
}

//Fin de la funcion principal

/*Funciones adicionales*/

//Esta funcion generando los puntos al azar con la funcion creada en el codigo:
//12_algoritmo de_burbuja_para_primeros_vecinos.c

int inicializa_posiciones(double x[], double y[])
{
    //Variable para guardar en los vectores los valores que se generen
    int i;
    
    //Archivo donde se guardan las posciones de cada uno de los puntos y los puntos
    FILE *fPuntos = fopen("posiciones_puntos.dat","w");

    //Los vectores con las posciones alatorias entre 0 y 1000
    for( i=0; i<NumeroPuntos; i++)
        {
            x[i] = drand48()*limDistancia;
            y[i] = drand48()*limDistancia;

            // Guardando el numero del punto y sus posicion 
            fprintf(fPuntos,"%d %lf %lf\n",i,x[i],y[i]);
        }
  
    
    //Cerrando el archivo que se creo
    fclose(fPuntos);

    return 0;
}

//Esta funcion calculara la distancia entre los puntos 
double distancia_particulas(double xDeReferencia,double yDeReferencia,double xSiguiente,double ySiguiente)
{   
    //Variable para almacenar la distancia
    double distancia;

    //Calculando la distancia entre dos particulas
    //Con este condicional se intenta evitar que se presente un error en el codigo

    if (xDeReferencia != xSiguiente && yDeReferencia != ySiguiente)

    {
      distancia  = sqrt(((xDeReferencia - xSiguiente)*(xDeReferencia - xSiguiente)) + ((yDeReferencia - ySiguiente)*(yDeReferencia - ySiguiente)));  
    }

    else
    {
        distancia = 0.0;
    }
    return distancia;
}

//Esta rutina se encargara de encontrar los vecinos y agregara los vecinos correspondientes

void vecinosParticulaConCeldas(double distanciaMinima, int IndiceParticula,double x[], double y[], double coordenadasEnXCelda[][NumeroPuntos], double coordenadasEnYCelda[][NumeroPuntos] )
{
    //Creando el archivo para los vecinos 
    FILE *fvecinos = fopen("puntos_vecinos.dat","w");

    //Variable de iteracion para recorrer todas las particulas
    int i,j;

    // Inicializando las matrices de coordenadas en la celda con valores NAN
    //Para evitar que que los ceros de la matriz cuenten como vecinos
    for (i = 0; i < LadoCelda; i++) 
    {
        for (j = 0; j < NumeroPuntos; j++) 
        {
            coordenadasEnXCelda[i][j] = NAN;
            coordenadasEnYCelda[i][j] = NAN;
        }
    }

    //Los indices de las de las celdas para recorrerlas 
    //Se define como entera para redondear la divsion de la posicion de la particula con respecto al lado de la celda
    int indCeldaEnx;
    int indCeldaEnY;

    //Posicionando las particulas en sus celdas y entrando sus coordenadas a las matrices
    for (i = 0; i<NumeroPuntos-1 ;i++)
    {   
        {
            //Calculando los indices de las celdas
            indCeldaEnx = x[i] / LadoCelda;
            indCeldaEnY = y[i] / LadoCelda;

            //Asignando los valores a las matrices de coordenadas

            coordenadasEnXCelda[indCeldaEnx][i] = x[i];
            coordenadasEnYCelda[indCeldaEnY][i] = y[i];
        }
    }

    //Calculando la celda de la particula de interes
    //Nuevamente es entero para solo tomar la parte entera del resultado de la division 
    int CeldaParticulaInteresX;
    int CeldaParticulaInteresY;

    CeldaParticulaInteresX = x[IndiceParticula] / LadoCelda;
    CeldaParticulaInteresY = y[IndiceParticula] / LadoCelda;

    /*Calculando los vecionos de la particula*/

    //Estas variables representan el espacio que se recorrera de una celda a otra tanto en x, como en y
    int dCeldaX;
    int dCeldaY;

    //Vector para alamacenar las distanicas
    double distancia[NumeroPuntos];

    //*Se haran los conticionares para los bordes del cuadrado y luego para las particulas del centro
    
    //Si esta cerca del origente
    if (CeldaParticulaInteresX == 0 && CeldaParticulaInteresY == 0)
    {
    //Note que este extremo no puede haber un -1 
    for (dCeldaX = 0; dCeldaX<2; dCeldaX++) 
    {
    for (dCeldaY = 0 ; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
    
    }
        
    }

    }

    //Si esta en el extremo superior derecho
    if (CeldaParticulaInteresX==LadoCelda-1 && CeldaParticulaInteresY==LadoCelda-1)
    {
   
    for (dCeldaX = -1; dCeldaX<1; dCeldaX++) 
    {
    for (dCeldaY = -1 ; dCeldaY<1; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    }
        
    }

    //Si esta en el extremo superior izquierdo
    if (CeldaParticulaInteresX == 0 && CeldaParticulaInteresY ==LadoCelda-1)
    {
 
    for (dCeldaX = 0; dCeldaX<2; dCeldaX++) 
    {
    for (dCeldaY = -1; dCeldaY<1; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
    }
    
    }
        
    }

    //Si esta en el extremo inferior derecho
    if (CeldaParticulaInteresX==LadoCelda-1 && CeldaParticulaInteresY==0)
    {

    for (dCeldaX = -1; dCeldaX<1; dCeldaX++) 
    {
    for (dCeldaY = 0; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    }
        
    }

    /*Para los bordes*/

    //Para el borde superior
    if ((CeldaParticulaInteresX>0 && CeldaParticulaInteresX< LadoCelda -1) && CeldaParticulaInteresY == LadoCelda -1)
    {
   //Note que este extremo no se puede pasar en x debe avanzar a las celdas de ambos lados, pero en y no
    for (dCeldaX = -1; dCeldaX<2; dCeldaX++) 
    {
    for (dCeldaY = -1; dCeldaY<1; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    } 

    }

    //Para el borde inferior

    if ((CeldaParticulaInteresX>0 && CeldaParticulaInteresX< LadoCelda -1) && CeldaParticulaInteresY == 0)
    {
   //Note que este extremo en x debe avanzar a las celdas de ambos lados, pero en y no
    for (dCeldaX = -1; dCeldaX<2; dCeldaX++) 
    {
    for (dCeldaY = 0; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    } 

    }

    //Para el borde izquierdo

    if ((CeldaParticulaInteresY>0 && CeldaParticulaInteresY< LadoCelda -1) && CeldaParticulaInteresX == 0)
    {
   //Note que este extremo no se y puede desplazarce con normalidad, pero x no
    for (dCeldaX = 0; dCeldaX<2; dCeldaX++) 
    {
    for (dCeldaY = -1; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    } 

    }

    //Borde derecho

    if ((CeldaParticulaInteresY>0 && CeldaParticulaInteresY< LadoCelda -1) && CeldaParticulaInteresX == LadoCelda - 1)
    {
    //y puede recorrer las celdas vecinas, pero x no en su totalidad
    for (dCeldaX = -1; dCeldaX<1; dCeldaX++) 
    {
    for (dCeldaY = -1; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    } 

    }

    //Finalmente si se encuentra en las celdas de la mitad
    if ((CeldaParticulaInteresX>0 && CeldaParticulaInteresX< LadoCelda -1) && (CeldaParticulaInteresY>0 && CeldaParticulaInteresY< LadoCelda -1))
    {
   //Se puede desplazar con libertad en ambas direcciones
    for (int dCeldaX = -1; dCeldaX<2; dCeldaX++) 
    {
    for (int dCeldaY = -1; dCeldaY<2; dCeldaY++) 
    {   //Note que se avanza y se retrocede en las celdas tanto en x, como en y
        int celdaVecinaX = CeldaParticulaInteresX + dCeldaX;
        int celdaVecinaY = CeldaParticulaInteresY + dCeldaY;
        
        //Ahora calculando la distanica
        for (i = 0; i<NumeroPuntos ;i++)
        {   
            //Verificando que la particula sea diferente de NAN
            if (!isnan(coordenadasEnXCelda[celdaVecinaX][i]) && !isnan(coordenadasEnYCelda[celdaVecinaY][i]))
            {
                distancia[i] = distancia_particulas(x[IndiceParticula],y[IndiceParticula],coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
                

            //Si la distancia es menor a un valor que ingrese el usuario entonces el punto es vecino
            if (distancia[i] < distanciaMinima)
            {
            //Agregando el valor al archivo
            fprintf(fvecinos,"%d %lf %lf\n",i,coordenadasEnXCelda[celdaVecinaX][i],coordenadasEnYCelda[celdaVecinaY][i]);
            }
            }
        
        }
        
    }
    
    } 

    }

    //Cerrando el archivo 
    fclose(fvecinos);
}




