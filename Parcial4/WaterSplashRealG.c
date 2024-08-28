/*Parcial 4: Astrostrofisica computacional
"Water Splash"*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<malloc.h>

#define X 0
#define Y 1

typedef struct
{
    int id;
    double pos[2];
    double vel[2];
    double accel[2];
    double mass;
    double rho;
    double h;
    double p;
    double c;
    double du;
    double u;
    int *nn; //Identificar del vecino
    int nNeighbors; //Esta variable se actuliza en cada momento porque la particula se mueve
    double *dx; //Distancia en x entre vecinos
    double *dy; //Distanica en y entre vecinos
    double *r; //Distancia entre vecinos
    double *W;
    double *dWx;
    double *dWy;
    int type;
    int miCelda; //Para almacenar la celda la que pertenece la particula
}Particles;

Particles *part, *auxPart;

int nFluid, nPart; //Numero de particulas de fluido y numero de particulas de la simulacion 8las de fluido y las de frontera)

//Para las dimensiones de las celdas
double LadoCelda; 
int numeroDeCeldas;

//Estructura de la celda de las particulas

typedef struct
{  
    int indiceCelda;
    double coordenadasCentro[2];
    int *IdentificadorParticula; //Identificar de las particulas que contiene
    int CantidadDeParticulasContenida; //La cantidad de particulas que contiene
    int *IndiceCeldasVecinas; //Guardar el identificador de las celdas vecinas
    int CantidadDeCeldasVecinas; //Guardar la cantidad de celdas. 
}Celda;

//Definiendo un puntero a la estructura celda
Celda *celda;


/*Variables extras para el Water Splash*/
//Definiendo algunos parametros de la circunferencia
double diametroCirculo,radioCirculo,centroCirculoEnX,centroCirculoEnY;

//Definiendo alguos parametros para trasladar las particulas al borde
//superior izquierdo
double TraslacionEnX,TraslacionEnY;

//Definiendo el maximaVelocidadInicial, la gravedad y angulo de lanzamiento
double maximaVelocidadInicial,anguloLanzamiento; 
double gravedad = 9.8;

void ics(int nx, int ny, double dx_fluid, double dy_fluid, double dx_border,double dy_border, double Lx, double Ly);
void mallaConCelda(double Lx, double h); /*Fase 1, linked list*/
double W(double r, double h);
double dW(double r, double dx, double h);
void testKernel(void);
void ubicacionParticulas(); /*Fase 2, linked list*/
void NN(int i); /*Fase 3,linked list*/
void test_NN(void);
void density(void);

void eos(void);
void navierStokes(void);
void viscosity(double dx);
void boundaryInteraction(double dx);
void meanVelocity(void);
void acceleration(double dx);
void drift(double dt); 
void kick(double dt);
void printState(char *outfile, double t);

int main(int argc, char *argv[])
{

  int i, nx, ny, counter; //ny y nx me permiten definir la malla
  
  double Lx, Ly, dx_fluid, dy_fluid,dx_border,dy_border; //separacion entre los elementos de la malla y separacion entre los puntos de la simulacion
  double dt = 5e-5; //Note que este delta pequeno permite que las particulas vayan a altas velocidades, haciendo que las ecuacuiones diferenciales se acerquen mas a la solucion real
  double t, tTotal = atoi(argv[1])*dt; //El tiempo total lo ingresa el usuario, y es la cantidad de veces que se va a usar el dt
  char outfiles[500];
  //double t, tTotal = 4000*dt;

  printf("voy a correr durante %d pasos, un tiempo total de %lf s\n",atoi(argv[1]),tTotal);
    
  nx = 40;
  ny = 40;
  Lx = 1e-3;
  Ly = 1e-3;
  
  //Parametros Circulo
  diametroCirculo = 2e-4;
  radioCirculo = diametroCirculo/2;
  TraslacionEnX= 8e-4; 
  TraslacionEnY = 8e-4;

  //Parametros de lanzamiento
  maximaVelocidadInicial = 10; //m/s
  anguloLanzamiento = M_PI/6; //30°


  //Cambiando los dx para ubicar las particulas en una esquina
  dx_fluid = diametroCirculo/nx;
  dy_fluid = diametroCirculo/ny;

  //Y sin mover las particulas del borde
  dx_border = Lx/nx;
  dy_border = Ly/nx;
  
  nFluid = nx*ny; //
  
  part = (Particles *)malloc((size_t)nFluid*sizeof(Particles)); //Alocacion de memoria para la estructura particulas
  if( part==NULL )
    {
      printf("Error alocando part\n");
      exit(0);
    }
  
  // Create the initial conditions
  ics( nx, ny, dx_fluid, dy_fluid,dx_border,dy_border, Lx, Ly);
 
  mallaConCelda(Lx,dx_fluid);

  // testing kernel function
  testKernel();
 
 
 //El tiempo que avanza la simulacion      
  counter = 0;
  t = 0;
  
  // printting system initial state
  sprintf(outfiles,"./output/state_%.4d",counter);
  printState(outfiles,t);

  // main loop
  while( t<=tTotal )
    {
      ubicacionParticulas();
      // searching near neighbors for all fuid particles
      for( i=0; i<nFluid; i++ )
	      NN(i);

      
      // testing near neighbors searching
      if(counter==0)
	     test_NN();
      

      // computing density

      density();
  
            
      // drift in leap-frog integration
      drift(dt);

      // computing acceleration
      acceleration(dx_fluid);  

      // kick in leap-frog integration
      kick(dt);
      
      // drift in leap-frog integration
      drift(dt);
	
      t = t + dt;
      counter++;

      // printting system state
      sprintf(outfiles,"./output/state_%.4d",counter);
      printState(outfiles,t);

      printf("step = %d \n",counter);
      
    }
  
  free(part);
  
  return 0;
}

//Funcion de condiciones iniciales
void ics(int nx, int ny, double dx_fluid, double dy_fluid, double dx_border,double dy_border, double Lx, double Ly)
{
  int i, j, counter;

  //5 archivos, uno para todas las particulas y 4 para analizar que las condciones de frontera se den bien
  FILE *fFluidIcs, *fbBorder, *frBorder, *ftBorder, *flBorder;
  fFluidIcs = fopen("fluid_ics.output","w");
    
  // ics for fluid particles
  
  counter = 0;
  for( j=0; j<ny; j++)
    {
      for( i=0; i<nx; i++)
	      {
          //El identificador va a ser counter
	        part[counter].id = counter;
          //La particula no puede iniciar su posicion en 0, entonces se desplaza un poco
	        part[counter].pos[X] = i*dx_fluid+dx_fluid/2.0 + TraslacionEnX;
	        part[counter].pos[Y] = j*dy_fluid+dy_fluid/2.0 + TraslacionEnY;

          //Velocidad inicial de las particulas con movimiento parabolico
          //Con menos en la posicion de x, para que la parabola no parta desde el eje y positivo
          part[counter].vel[X] = - maximaVelocidadInicial * cos(anguloLanzamiento); 
          part[counter].vel[Y] = maximaVelocidadInicial * sin(anguloLanzamiento);

          part[counter].accel[X] = 0.0;
          part[counter].accel[Y] = 0.0;

          part[counter].rho = 1000;
          part[counter].h = dx_fluid;
          part[counter].mass = part[counter].rho*dx_fluid*dy_fluid;
          part[counter].p = 0.0;
          part[counter].c = 0.0;
          
          //Cambia de Energia Potencial incial
          part[counter].du = 0.0;
          
          //Energia interna del sistema
          part[counter].u = 357.1; 

          part[counter].nn = NULL;
          part[counter].nNeighbors = 0;
          part[counter].dx = NULL;
          part[counter].dy = NULL;
          part[counter].r = NULL;
          part[counter].W = NULL;
          part[counter].dWx = NULL;
          part[counter].dWy = NULL;
          part[counter].type = 1;
	    counter++;
	    }
    }
  

  // ics for boundary particles

  // speed in boundary
  double vBoundary = 1.5e-2; 
  
  int npVirtI = 320; //Numero de particulas en los bordes
  int npV = npVirtI/4; //El numero de particulas que hay en cada borde. OJO: con las esquinas

  
  // bottom border, 81 points
  //Creando la frontera de abajo y note que se incluyen las esquinas 
  fbBorder = fopen("bottom_border.output","w");

  //Boundary particles are add to estructure particles set
  nPart = nFluid;
  
  auxPart = NULL;
  
  auxPart = (Particles *)realloc(part, (size_t)(nPart+npV+1)*sizeof(Particles));  //Se aloca memoria para todas las particulas y las del borde, mas una de la esquina
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {

      //Part apuntaba a los datos que tenia alamacenado y luego apunta a auxpart en esta linea
      part = auxPart;
      //Elimina copias 
      auxPart = NULL;
    }
  
  counter = nPart;
    
  for( i=0; i<=npV; i++)
    {
      part[counter].id = counter;
      //La unica frontera que varai es x, porque y es 0 todo el tiempo
      part[counter].pos[X] = i*dx_border/2.0;
      part[counter].pos[Y] = 0.0;

      part[counter].vel[X] = 0.0;
      //part[counter].vel[X] = -vBoundary;
      part[counter].vel[Y] = 0.0;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx_border;
      part[counter].mass = part[counter].rho*dx_border*dy_border;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1; //Particuola virtual
      counter++;
    }

   for( i=nPart; i<nPart+npV+1; i++)
    {
      fprintf(fbBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(fbBorder);

  //Archivo con las particulas borde derecho 
  // right border, 79 points, porque tiene que quitar los bordes

  frBorder = fopen("right_border.output","w");

  //Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
    
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV-1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
    
  for( i=0; i<npV-1; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = Lx;
      part[counter].pos[Y] = dy_border/2.0 + i*dy_border/2.0;
      part[counter].vel[X] = 0.0;
      part[counter].vel[Y] = 0.0;
      //part[counter].vel[Y] = -vBoundary;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx_border;
      part[counter].mass = part[counter].rho*dx_border*dy_border;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;
      counter++;
    }
  
    for( i=nPart; i<nPart+npV-1; i++)
    {
      fprintf(frBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(frBorder);

  //Archivo del borde de arriba
  
  // top border, 81 points

  ftBorder = fopen("top_border.output","w");


  //Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
  
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV+1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
      
  for( i=0; i<=npV; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = i*dx_border/2.0;
      part[counter].pos[Y] = Ly;
      part[counter].vel[X] = vBoundary; //Esto genera el giro
      part[counter].vel[Y] = 0.0;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx_border;
      part[counter].mass = part[counter].rho*dx_border*dy_border;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;
      counter++;
    }

  for( i=nPart; i<nPart+npV+1; i++)
    {
      fprintf(ftBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(ftBorder);
  
  // left border, 79 points
  //Archivo del borde izquierdo 

  flBorder = fopen("left_border.output","w");
  

  //Boundary particles are add to estructure particles set
  nPart = counter;
  
  auxPart = NULL;
    
  auxPart = (Particles *)realloc(part,(size_t)(nPart+npV-1)*sizeof(Particles));
  if(auxPart==NULL)
    {
      printf("error en auxPart\n");
      exit(0);
    }
  else
    {
      part = auxPart;
      auxPart = NULL;
    }
  
  for( i=0; i<npV-1; i++)
    {
      part[counter].id = counter;
      part[counter].pos[X] = 0.0;
      part[counter].pos[Y] = dy_border/2.0 + i*dy_border/2.0;
      part[counter].vel[X] = 0.0;
      part[counter].vel[Y] = 0.0;
      // part[counter].vel[Y] = vBoundary;
      part[counter].accel[X] = 0.0;
      part[counter].accel[Y] = 0.0;
      part[counter].rho = 1000;
      part[counter].h = dx_border;
      part[counter].mass = part[counter].rho*dx_border*dy_border;
      part[counter].p = 0.0;
      part[counter].c = 0.0;
      part[counter].du = 0.0;
      part[counter].u = 357.1;
      part[counter].nn = NULL;
      part[counter].nNeighbors = 0;
      part[counter].dx = NULL;
      part[counter].dy = NULL;
      part[counter].r = NULL;
      part[counter].W = NULL;
      part[counter].dWx = NULL;
      part[counter].dWy = NULL;
      part[counter].type = -1;
      counter++;
    }

   for( i=nPart; i<nPart+npV-1; i++)
    {
      fprintf(flBorder,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }
  
  fclose(flBorder);
  
  // print all particles

  nPart = counter;
 
  for( i=0; i<nPart; i++)
    {
      fprintf(fFluidIcs,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
    }

  fclose(fFluidIcs);

  
}

/*FASE 1: CREACION DE LA MALLA*/

void mallaConCelda(double Lx, double h)
{
    double kappa = 2.0;
    LadoCelda = kappa * h;
    numeroDeCeldas = ceil(Lx/LadoCelda); 
    printf("El sistema tiene %d celdas y cada celda tiene de lado %lf\n", numeroDeCeldas*numeroDeCeldas, LadoCelda);

    //Alocando memoria para que quede el puntero de celda con la misma cantidad de elementos que el numero de celdas
    celda = (Celda *)malloc((size_t)(numeroDeCeldas * numeroDeCeldas) * sizeof(Celda));
    if (celda == NULL) {
        perror("Error al alocar memoria");
        exit(0);
    }
    //Con este ciclo se asignaran los indices de las celdas, las coordenas del centro de de las celdas

    int m,k; //Para recorrer filas y columnas (considernado la situacion matricial)
    int IdentificadorCelda;
   
    for (k=0; k<numeroDeCeldas;k++) //Recorre la fila
    {
        for (m=0; m<numeroDeCeldas;m++) //Recorre la columna
        {
            //Definiendo el indice con la formula dada 

            IdentificadorCelda = k * numeroDeCeldas + m; 

            //Ahora considerando la estructura de celda

            celda[IdentificadorCelda].indiceCelda = IdentificadorCelda;
            celda[IdentificadorCelda].coordenadasCentro[X] = (k + 0.5) * LadoCelda;
            celda[IdentificadorCelda].coordenadasCentro[Y] = (m + 0.5) * LadoCelda;
            celda[IdentificadorCelda].IdentificadorParticula = NULL;
            celda[IdentificadorCelda].IndiceCeldasVecinas = NULL;
            celda[IdentificadorCelda].CantidadDeCeldasVecinas = 0;
        }
    }

    //Creando un ciclo para encontrar las celdas vecinas
    int p,s; 
    double disX,disY,disTotal; 
    int numeroDeCeldasVecinas;

    //Ciclo para la celda de interes
    for (p=0;p<numeroDeCeldas*numeroDeCeldas;p++)
    {   
        numeroDeCeldasVecinas = 0;  //Aca para empezar desde cero cada conteo
        //Ciclo para la posible vecina
        for (s=0;s<numeroDeCeldas*numeroDeCeldas;s++)
        { 
           disX = celda[p].coordenadasCentro[X] - celda[s].coordenadasCentro[X];
           disY = celda[p].coordenadasCentro[Y] - celda[s].coordenadasCentro[Y];
           disTotal = sqrt(disX*disX + disY*disY);

           //Criterio para que sea vecina
           if (disTotal < sqrt(2)*h*kappa + 1e-10 )
           {
            numeroDeCeldasVecinas = numeroDeCeldasVecinas + 1; 
            //Alocando memoria para guardar cada indice de las celdas vecinas
            int *temp = (int *) realloc(celda[p].IndiceCeldasVecinas, (size_t)(numeroDeCeldasVecinas) * sizeof(int));
                if (temp == NULL) {
                    perror("Error al alocar memoria");
                    exit(0);
                }
            celda[p].IndiceCeldasVecinas = temp;
            celda[p].IndiceCeldasVecinas[numeroDeCeldasVecinas - 1] = s;
           }
        }

        celda[p].CantidadDeCeldasVecinas = numeroDeCeldasVecinas;
    }
}


double W(double r, double h)
{
  
  double R = r/h;
  
  double alpha = 15.0/(7.0*M_PI*h*h);
  
  if( (R >= 0.0) && (R < 1.0) )
    return alpha*((2.0/3.0) - R*R + 0.5*R*R*R);
  
  if( (R >= 1.0) && (R <= 2.0) )
    return alpha*((1.0/6.0)*(2.0-R)*(2.0-R)*(2.0-R));

  if( R>2.0)
    return 0.0;
  
  return 0.0;
}

double dW(double r, double dx, double h)
{
  
  double R = r/h;
  
  double alpha = 15.0/(7.0*M_PI*h*h);
  
  if( (R >= 0.0) && (R < 1.0) )
    return alpha*(-2.0 + 1.5*R)*dx/(h*h);
  
  if( (R >= 1.0) && (R <= 2.0) )
    return alpha*(-0.5*(2.0-R)*(2.0-R))*dx/(h*h*R);

  if( R>2.0)
    return 0.0;
  
  return 0.0;
}


//Sirve para testear la funcion de Kernel
void testKernel(void)
{
  double r, w, dw;

  FILE *fKernelTest;
  fKernelTest = fopen("kernel_test.output","w");
  
  for( r=-3.0; r<=3.0; r = r + 0.1)
    {
      w = W( fabs(r), 1.0);
      dw = dW( fabs(r), r/sqrt(3.0), 1.0);

      fprintf(fKernelTest,"%16.10lf %16.10lf %16.10lf\n",r,w,dw);
      
    }

  fclose(fKernelTest);
  
}

/*FASE 2: UBICACION DE LAS PARTICULAS EN LAS CELDAS*/

void ubicacionParticulas()
{
    // Liberando la memoria de las celdas para almacenar datos de particulas
    int q;
    for (q = 0; q < numeroDeCeldas * numeroDeCeldas; q++)
    {
        free(celda[q].IdentificadorParticula);

        celda[q].CantidadDeParticulasContenida = 0;
        celda[q].IdentificadorParticula = NULL;
    }

    // Calculando la distancia de cada una de las particulas a los centros de coordenadas de cada una de las celdas
    // para asa conocer que celda contiene cada una de las particulas
    int l, z;
    double distanciaEnXCentro, distanciaEnYCentro, distanciaCelda;
    double distanciaEnXCentro0, distanciaEnYCentro0, distanciaCelda0;
    
    for (l = 0; l < nPart; l++)
    { 
        // Suponiendo que la particula esta en la celda 0 y calculando la distancia a su centro

        part[l].miCelda = 0;
        distanciaEnXCentro0 = celda[0].coordenadasCentro[X] - part[l].pos[X];
        distanciaEnYCentro0 = celda[0].coordenadasCentro[Y] - part[l].pos[Y];
        distanciaCelda0 = sqrt(distanciaEnXCentro0 * distanciaEnXCentro0 + distanciaEnYCentro0 * distanciaEnYCentro0);

        // Recorriendo las celdas para encontrar la celda a la que pertenece la partícula l
        for (z = 1; z < numeroDeCeldas * numeroDeCeldas; z++)
        {
            distanciaEnXCentro = celda[z].coordenadasCentro[X] - part[l].pos[X];
            distanciaEnYCentro = celda[z].coordenadasCentro[Y] - part[l].pos[Y];
            distanciaCelda = sqrt(distanciaEnXCentro * distanciaEnXCentro + distanciaEnYCentro * distanciaEnYCentro);

            if (distanciaCelda < distanciaCelda0)
            { 
                // Actualizando a la celda mas cercana a la particula
                distanciaCelda0 = distanciaCelda;
                part[l].miCelda = z;
            }
        }

        // Incrementar la cantidad de particulas contenidas en la celda mas cercana
        int CeldaParticulal = part[l].miCelda; //No hay que definirla dentro de este ciclo
        
        //Aumentando la cantidade de celdas contenidas
        celda[CeldaParticulal].CantidadDeParticulasContenida++;
        
        // Alocando memoria para almacenar los identificadores de las particulas
        int *temp2 = (int*)realloc(celda[CeldaParticulal].IdentificadorParticula, (size_t)(celda[CeldaParticulal].CantidadDeParticulasContenida) * sizeof(int));
        if (temp2 == NULL)
        {
            printf("Error al alocar memoria");
            exit(0);
        }
        celda[CeldaParticulal].IdentificadorParticula = temp2;
        celda[CeldaParticulal].IdentificadorParticula[celda[CeldaParticulal].CantidadDeParticulasContenida - 1] = l;
    }
}

/*FASE 3: BUSQUEDA DE VECINOS*/

// Searching the near neighbors 
void NN(int i)
{
  //Encontrando las particulas vecinas a i
  int nNeighbors = 0;
  double kappa = 2.0;
  int n,b;
  double yij,xij,rij,hij;
  int *auxInt;
  double *auxDouble;
  int Vecino,CeldaVecina;
  
  //Elimina la memoria asignada para cada paso
  free(part[i].nn);
  free(part[i].dx);
  free(part[i].dy);
  free(part[i].r);
  free(part[i].W);
  free(part[i].dWx);
  free(part[i].dWy);

  //Apunta a Null
  part[i].nn = NULL;
  part[i].dx = NULL;
  part[i].dy = NULL;
  part[i].r = NULL;
  part[i].W = NULL;
  part[i].dWx = NULL;
  part[i].dWy = NULL;
  
//Este ciclo para recorrer las celdas vecinas
  for(b=0;b<celda[part[i].miCelda].CantidadDeCeldasVecinas;b++)
  {
    //Recorrer con los indices almacedso en la celda de part i, las celdas
    CeldaVecina = celda[part[i].miCelda].IndiceCeldasVecinas[b];

    //Este ciclo para recorrer las particulas contenidas en estas celdas vecinas
    for (n=0;n<celda[CeldaVecina].CantidadDeParticulasContenida;n++)
    { 
      //Guardando el posible vecino en una variable 
      Vecino = celda[CeldaVecina].IdentificadorParticula[n];

      if(i != Vecino)
      {
        xij = part[i].pos[X] - part[Vecino].pos[X];
        yij = part[i].pos[Y] - part[Vecino].pos[Y];
        //Distancia
        rij = sqrt( xij*xij + yij*yij );
        hij = 0.5*(part[i].h+part[Vecino].h);

	      if( rij <= kappa*hij + 1e-10  )
	      {
	        nNeighbors++;

	        // add neighbor id
	        auxInt = NULL; //Inicializa
	        auxInt = (int *)realloc(part[i].nn,(size_t)(nNeighbors)*sizeof(int));
	        part[i].nn = auxInt;
	        auxInt = NULL;
	      	      
	        // add neighbor dx
	        auxDouble = NULL;
	        auxDouble = (double *)realloc(part[i].dx,(size_t)(nNeighbors)*sizeof(double));
	        part[i].dx = auxDouble;
	        auxDouble = NULL;

	        // add neighbor dy
	        auxDouble = NULL;
	        auxDouble = (double *)realloc(part[i].dy,(size_t)(nNeighbors)*sizeof(double));
	        part[i].dy = auxDouble;
	        auxDouble = NULL;

	        // add neighbor r
	        auxDouble = NULL;
	        auxDouble = (double *)realloc(part[i].r,(size_t)(nNeighbors)*sizeof(double));
	        part[i].r = auxDouble;
	        auxDouble = NULL;
	      
	        // add neighbor W
	        auxDouble = NULL;
	        auxDouble = (double *)realloc(part[i].W,(size_t)(nNeighbors)*sizeof(double));
	        part[i].W = auxDouble;
	        auxDouble = NULL;

          // add neighbor dWx
          auxDouble = NULL;
          auxDouble = (double *)realloc(part[i].dWx,(size_t)(nNeighbors)*sizeof(double));
          part[i].dWx = auxDouble;
          auxDouble = NULL;
	      
          // add neighbor dWy
          auxDouble = NULL;
          auxDouble = (double *)realloc(part[i].dWy,(size_t)(nNeighbors)*sizeof(double));
          part[i].dWy = auxDouble;
          auxDouble = NULL;
	      
          part[i].nn[nNeighbors-1] = Vecino;
          part[i].dx[nNeighbors-1] = xij;
          part[i].dy[nNeighbors-1] = yij;
          part[i].r[nNeighbors-1] = rij;
          part[i].W[nNeighbors-1] = W( rij, hij ); 
          part[i].dWx[nNeighbors-1] = dW( rij, xij, hij);
          part[i].dWy[nNeighbors-1] = dW( rij, yij, hij);
      }
    }
  }
  }
  part[i].nNeighbors = nNeighbors;
}

void test_NN(void)
{
  int i,j,k;

   FILE *fTestNN;
   fTestNN = fopen("NN_test.output","w");
   srand(time(NULL));
   
   for( k=0; k<20; k++)
    {

      i = rand() % nFluid;
      
      printf("testing for particle %d\n",i);
      printf("with %d neighbors\n",part[i].nNeighbors);
       
      fprintf(fTestNN,"%16d %16.10lf %16.10lf\n",
	      part[i].id,
	      part[i].pos[X],
	      part[i].pos[Y]);
      
      for( j=0; j<part[i].nNeighbors; j++ )
	      fprintf(fTestNN,"%16d %16.10lf %16.10lf\n",
		    part[i].nn[j],
		    part[part[i].nn[j]].pos[X],
		    part[part[i].nn[j]].pos[Y]);
      fprintf(fTestNN,"\n");
    }
  fclose(fTestNN);
    
}

void density(void)
{
  int i, j;
  double wii, norm;
  
  for( i=0; i<nFluid; i++ )
    {
      // self density
      wii = W( 0.0, part[i].h );
      
      // computing density
      part[i].rho = part[i].mass*wii;
      for( j=0; j<part[i].nNeighbors; j++ )
	      part[i].rho = part[i].rho + part[part[i].nn[j]].mass*part[i].W[j];

      // normalizing the density
      norm = (part[i].mass/part[i].rho)*wii;
      for( j=0; j<part[i].nNeighbors; j++ )
	      norm = norm + (part[part[i].nn[j]].mass/part[part[i].nn[j]].rho)*part[i].W[j];
      
      part[i].rho = part[i].rho/norm;
    }
  
  printf("density computed\n");

}

void eos(void)
{
  int i;
  
  for( i=0; i<nPart; i++ )
    {
      part[i].c = 0.01;
      part[i].p = part[i].c*part[i].c*part[i].rho; 
    }
}

//Note que son de Euler, porque no tienen el caracter tensorial
void navierStokes(void)
{

  int i, j, k; //contadores
  double pij, vdw; 
  // computing sound speed and pression
  eos(); //Ecuacion de estado, se incializa densidad y presion 

  // computing acceleration
  for( i=0; i<nFluid; i++ )
    {
      //Incializando en 0
      part[i].accel[X] = 0.0;
      part[i].accel[Y] = -9.8;
      part[i].du = 0.0;

    //Sumatoria de Einstein implicita
      for( k=0; k<part[i].nNeighbors; k++ )
	      {
	        j = part[i].nn[k]; //Guarda el identificar los vecino
	  
	        pij = ( part[i].p/(part[i].rho*part[i].rho) )
	          + ( part[j].p/(part[j].rho*part[j].rho) );
	        part[i].accel[X] = part[i].accel[X] - part[j].mass*pij*part[i].dWx[k];
	        part[i].accel[Y] = part[i].accel[Y] - part[j].mass*pij*part[i].dWy[k];
	  
	        vdw = (part[i].vel[X]-part[j].vel[X])*part[i].dWx[k]
	            + (part[i].vel[Y]-part[j].vel[Y])*part[i].dWy[k];
	        part[i].du = part[i].du + 0.5*part[j].mass*pij*vdw;
	  
	      } //W = integral( f*dr ) = integral( f*dr*(dt/dt) ) = integral( f*v*dt )

    }
  
  printf("acceleration computed\n");
}

void viscosity(double dx)
{
  
  int i, j, k;

  double xij, yij, vxij, vyij, vijrij, vdw;
  double hij, cij, phiij, rhoij, Piij;
  double alphapi = 1.0;
  double betapi = 1.0;
  double eps = dx; //Longitud de suavizado para evitar el cero
  double eps2 = 0.01*eps*eps;

  for( i=0; i<nFluid; i++ )
    {
      for( k=0; k<part[i].nNeighbors ; k++ )
	      {
	  
	        j = part[i].nn[k];
	  
	        xij = part[i].pos[X] - part[j].pos[X];
	        yij = part[i].pos[Y] - part[j].pos[Y];
	        vxij = part[i].vel[X] - part[j].vel[X];
	        vyij = part[i].vel[Y] - part[j].vel[Y];
	        vijrij = vxij*xij + vyij*yij;
	  
	        if( vijrij < 0.0 )
	          {
	            hij = 0.5*(part[i].h+part[j].h);
	            phiij = (hij*vijrij)/( xij*xij + yij*yij + eps2);
	            cij = 0.5*(part[i].c+part[j].c);
	            rhoij = 0.5*(part[i].rho+part[j].rho);
	      
	            Piij = ( -alphapi*cij*phiij + betapi*phiij*phiij )/( rhoij );

	            part[i].accel[X] = part[i].accel[X] - part[j].mass*Piij*part[i].dWx[k];
	            part[i].accel[Y] = part[i].accel[Y] - part[j].mass*Piij*part[i].dWy[k];

	            vdw = (part[i].vel[X]-part[j].vel[X])*part[i].dWx[k]
		            + (part[i].vel[Y]-part[j].vel[Y])*part[i].dWy[k];
	            part[i].du = part[i].du + 0.5*part[j].mass*Piij*vdw;
	      
	          }
	  
	      }
    }
  printf("viscosity computed\n");
}

void boundaryInteraction(double dx)
{

  int i, j;
  int n1 = 12, n2 = 4;
  double r0 = dx/2.0, D = 0.01;
  double xij, yij, rij, PBxij, PByij;

  for( i=0; i<nFluid; i++ )
    {
      for( j=0; j<part[i].nNeighbors; j++ )
	      { 
          //Este modelo se activa si se presenta el vecino
	        if( part[part[i].nn[j]].type==-1 )
	          {
	            xij = part[i].pos[X] - part[part[i].nn[j]].pos[X];
	            yij = part[i].pos[Y] - part[part[i].nn[j]].pos[Y];
	            rij = sqrt( xij*xij + yij*yij );
	      
	            if( rij<r0 )
		            {
		              PBxij = D*( pow((r0/rij),n1) - pow((r0/rij),n2) )*(xij/(rij*rij));
		              PByij = D*( pow((r0/rij),n1) - pow((r0/rij),n2) )*(yij/(rij*rij));
		  
		              part[i].accel[X] = part[i].accel[X] + PBxij;
		              part[i].accel[Y] = part[i].accel[Y] + PByij;
		  
		            }
	           }
	        }
      }
  printf("interaction with boundary computed\n");
}

//Por eso, este sistema se llama X-SPH
void meanVelocity(void)
{

  int i, j;
  double epsilon = 0.3; //Este permite que no se presenta sobreamortiguacion
  double vxMean, vyMean;
  double vxij, vyij, rhoij;

  for( i=0; i<nFluid; i++ )
    {
      
      vxMean = 0.0;
      vyMean = 0.0;
      
      for( j=0; j<part[i].nNeighbors; j++ )
	    {
	      vxij = part[i].vel[X] - part[part[i].nn[j]].vel[X];
	      vyij = part[i].vel[Y] - part[part[i].nn[j]].vel[Y];
	      rhoij = 0.5*(part[i].rho+part[part[i].nn[j]].rho);
	      vxMean = vxMean + (part[part[i].nn[j]].mass/rhoij)*vxij*part[i].W[j];
	      vyMean = vyMean + (part[part[i].nn[j]].mass/rhoij)*vyij*part[i].W[j];
	    }

      part[i].vel[X] = part[i].vel[X] - epsilon*vxMean;
      part[i].vel[Y] = part[i].vel[Y] - epsilon*vyMean;
   
    }
}

void acceleration(double dx)
{

  // computing acceleration and change of energy
  navierStokes();
  
  // computing viscosity contribution
  viscosity(dx); //Disipa la energia interna
  
  // computing interaction with boundary
  boundaryInteraction(dx);

  // correction to mean velocity
  meanVelocity();

  printf("acceleration computed\n");
  
}

void drift(double dt)
{

  int i;
  
  for( i=0; i<nFluid; i++ )
    {
      part[i].pos[X] = part[i].pos[X] + 0.5*dt*part[i].vel[X];
      part[i].pos[Y] = part[i].pos[Y] + 0.5*dt*part[i].vel[Y];
      part[i].u = part[i].u + 0.5*dt*part[i].du;
    }
}

void kick(double dt)
{
  
  int i;
  
  for( i=0; i<nFluid; i++ )
    {
      part[i].vel[X] = part[i].vel[X] + dt*part[i].accel[X];
      part[i].vel[Y] = part[i].vel[Y] + dt*part[i].accel[Y];
    }
}

void printState(char *outfile, double t)
{


  int i,j;

  //Variables para que se produzca el circulo 
  double CentroCirculoInicialX,CentroCirculoInicialY,distanciaEnXCentro,distanciaEnYCentro,distanciaCentroTotal;

  CentroCirculoInicialX = 9e-4;
  CentroCirculoInicialY = 9e-4;
  
  //Siguiendo la formula de movimiento parabolico para calcular el centro
  // en cada instante
  //Se coloca un menos en la velocidad incial de la ecuacion de posicion en x, porque
  //sino la parabola partira desde el eje y positivo
  centroCirculoEnX = CentroCirculoInicialX - maximaVelocidadInicial * cos(anguloLanzamiento) * t;
  centroCirculoEnY = CentroCirculoInicialY + maximaVelocidadInicial * sin(anguloLanzamiento) * t - 4.9 * t * t;

  
  FILE *fState;
  fState = fopen(outfile,"w");
 
  for( i=0; i<nFluid; i++)
    { 
      //Calculando la distancia al centro
      distanciaEnXCentro = part[i].pos[X] - centroCirculoEnX;
      distanciaEnYCentro = part[i].pos[Y] - centroCirculoEnY; 

      distanciaCentroTotal = distanciaEnXCentro * distanciaEnXCentro + distanciaEnYCentro * distanciaEnYCentro;

      if (distanciaCentroTotal <= radioCirculo*radioCirculo)
      {
        fprintf(fState,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      part[i].pos[X],part[i].pos[Y],
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
      }

      else
      {
        fprintf(fState,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[i].id,
	      2.0009925000,2.0009925000,
	      part[i].vel[X],part[i].vel[Y],
	      part[i].accel[X],part[i].accel[Y],
	      part[i].rho,part[i].mass,
	      part[i].p,part[i].c,part[i].u);
      }
    }
  
  for (j=nFluid; j<nPart; j++)
  {
        fprintf(fState,"%d %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",
	      part[j].id,
	      part[j].pos[X],part[j].pos[Y],
	      part[j].vel[X],part[j].vel[Y],
	      part[j].accel[X],part[j].accel[Y],
	      part[j].rho,part[j].mass,
	      part[j].p,part[j].c,part[j].u);
  }
  
  fclose(fState);

}