/*

Este codigo muestra el uso de punteros en C para
entender y manipular las direcciones de memoria

Última modificación:  

*/

// Librerias de C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// define una estructura de datos, tenga cuidado con el ; al final de la definicion. 
// todas las rutinas conocen esta estructura de datos
typedef struct 
  {
    int identificador;
    double pos[3];
    double vel[3];
    double masa;
} mi_propio_tipo_de_variable; // no hay reserva de memoria para mi_propio_tipo_de_variable 

// Rutinas usadas en el codigo
//======================================
int cuadrado_por_valor(int n);
int cuadrado_por_referencia(int *n);
void cuadrado_con_vector(int n[3]);
int estructuras_manipulacion_por_valor(mi_propio_tipo_de_variable part1,mi_propio_tipo_de_variable part2);
int estructuras_manipulacion_por_referencia(mi_propio_tipo_de_variable *part1,mi_propio_tipo_de_variable *part2);
int Potencia(int x, int Exponent, int option, int (*powerto)(int, int));
int Potencia_con_exponente_impar(const int number,const int exponent);
int Potencia_con_exponente_par(const int number,const int exponent);
//=====================================

// Funcion principal 
int main(int argc, char *argv[])
{

  int i;

  /*
    Define una variable y y un puntero que apunta a la 
    direccion de memoria de y
  */
  //============================================
  int y, *yPtr; // define un entero y e un puntero yPtr 

  printf("y = %d\n",y);
  
  y = 5; // inicializa el valor de y a 5

  printf("y = %d\n",y);


  printf("El valor del puntero yPtr es yPtr = %p\n",yPtr);



  yPtr = NULL; //Apunta a la nada, al inicio al RAM

  printf("El valor del puntero yPtr es yPtr = %p\n",yPtr);

  yPtr = 0;
  
  printf("El valor del puntero yPtr es yPtr = %p\n",yPtr);

  yPtr = &y; //Imprime la direccion de memoria de y 

  printf("\n\n");

 

  printf("La direccion de memoria de y es &y = %p\n",&y); //Imprime la direccion de y
  printf("El apuntador yPtr tiene direccion de memoria  &yPtr = %p\n",&yPtr); //Imprime la direccion del puntero
  printf("El valor de yprt es yPtr = %p\n",yPtr); //Imprime el valor guardado en el puntero, la direccion de y
  printf("El valor de y es y = %d\n",y); //Imprime el valor guardado en y
  printf("El valor de y es *yPtr = %d\n",*yPtr); // operador de indireccion, imprime el valor guardado en y

  //============================================
  /*
    Ejemplos de llamados a funciones por valor y por referencia 
  */
  //=============================================

  printf("\n\n");

  // llama una funcion por valor, la funcion recibe y, hace una copia de este y la modifica
  int z;
  printf("La direccion de memoria de y es &y = %p\n",&y);
  z = cuadrado_por_valor(y); 

  printf("llamado por valor: y = %d\n",y);
  printf("llamado por valor: *yPtr = %d\n",*yPtr); //Este puntero continuara apuntado a y, por la operacion cuadrado crea una nueva variable y eso no se guarda en y
  printf("llamado por valor: z = %d\n",z);

  
  // Llamado a una funcion por referencia, la funcion recibe la direccion de memoria 
  // y modifica el valor de la variable usando el operador de indireccion
  printf("\n\n");


  cuadrado_por_referencia(&y); //Esta yendo directamente a la direccion de memoria, evitando crear una copia
  //No es necesario el paso por otras variables
  printf("llamado por referencia y = %d\n",*yPtr); //No se produce el problema con las copias
   printf("llamado por referencia y = %d\n",y);

  

  printf("\n\n");

  
  //=============================================
  /*
    Un arreglo siempre es una dirrecion de memoria al inicio del arreglo
    Un arreglo siempre se pasa por referencia a una funcion 
  */
  
  //======================================================
 
  int x[3] = {1,2,3}; //Esta forma de inicializarlo con {}, solo se puede en el punto donde se define la variable
  int y1[3] = {0};
  int z1[3];
  
  for(i=0; i<3; i++)
    z1[i] = i*i;

  printf("arreglos :\n");
  for(i=0; i<3; i++)
    printf("x[%d] = %d\ty1[%d] = %d\tz1[%d] = %d\n",i, x[i], i, y1[i], i, z1[i]);
  
  
  // Para llamar a una funcion que modifica al vector x no se necesita especificar 
  // con la notacion de puntero porque un arreglo es un apuntador a la direccion 
  // de memoria del primer elemento del arreglo
  cuadrado_con_vector(x);

  printf("Cuadrado de un vector calculado con una funcion:\n");
  for(i=0; i<3; i++)
    printf("x[%d] = %d\n",i,x[i]);

  //=======================================================

  /*
    Ejemplos de estructuras de datos
  */
  //============================================================================

  // defino un tipo de variable mi_propio_tipo_de_variable 

  
  struct particulas //Es una estructura de datos, definiendo un tipo de variable que se llama particula, no definiendo una varaible
  {
    //Esto en memoraria queda en secuencia como los ciclos de arreglos
    int identificador;
    double pos[3]; //Arreglo de tres componentes para la posicion 
    double masa;
  } part1, part2; //Esto es equivalente a escribir particulas part1,part2;
 
  //Con esto se inicializan los datos de la variable part1 de tipo particulas
  part1.identificador = 1;
  part1.pos[0] = 1.0;
  part1.pos[1] = 2.0;
  part1.pos[2] = 3.0;
  part1.masa = 1.0;
  
  printf("\n\n");
  printf("Estructura de datos part1:\n");
  printf("%d %lf %lf %lf %lf\n",
	 part1.identificador,
	 part1.pos[0],part1.pos[1],part1.pos[2],
	 part1.masa);

  //Como no se ha inicializado part2 imprime lo que el compilador quiere
  printf("Estructura de datos part2:\n");
  printf("%d %lf %lf %lf %lf\n",
	 part2.identificador,
	 part2.pos[0],part2.pos[1],part2.pos[2],
	 part2.masa);
  
  
  // igualando dos estructuras de datos similares
  part2 = part1; //Para inicializarla se igualan, pero solo si son de la misma estructura de datos
  printf("Estructura de datos part2:\n");
  printf("%d %lf %lf %lf %lf\n",
	 part2.identificador,
	 part2.pos[0],part2.pos[1],part2.pos[2],
	 part2.masa);
  

  // definiendo mi propio tipo de variable
  mi_propio_tipo_de_variable particula1, particula2; //Esto por la variable global para definir estructuras
						      
  
  // Inicializando las variables particula1 y particula2
  particula1.identificador = 1;
  particula1.pos[0] = 1.0;
  particula1.pos[1] = 2.0;
  particula1.pos[2] = 3.0;
  particula1.vel[0] = 1.0;
  particula1.vel[1] = 2.0;
  particula1.vel[2] = 3.0;
  particula1.masa = 1.0;
  
  particula2.identificador = 2;
  particula2.pos[0] = 1.0;
  particula2.pos[1] = 1.0;
  particula2.pos[2] = 1.0;
  particula2.vel[0] = 1.0;
  particula2.vel[1] = 1.0;
  particula2.vel[2] = 1.0;
  particula2.masa = 1.0;

  // Imprime el valor actual de particula1 y particula2 
  printf("\n\n");
  printf("Imprime la variable particula1:\n");
  printf("%d\n",particula1.identificador);
  printf("%lf %lf %lf\n",particula1.pos[0],particula1.pos[1],particula1.pos[2]);
  printf("%lf %lf %lf\n",particula1.vel[0],particula1.vel[1],particula1.vel[2]);
  printf("%lf\n",particula1.masa);

  printf("\n\n");
  printf("Imprime la variable particula2:\n");
  printf("%d\n",particula2.identificador);
  printf("%lf %lf %lf\n",particula2.pos[0],particula2.pos[1],particula2.pos[2]);
  printf("%lf %lf %lf\n",particula2.vel[0],particula2.vel[1],particula2.vel[2]);
  printf("%lf\n",particula2.masa);
  
  printf("\n\nIntentando modificar la variable particula2 pasando esta a una funcion por valor\n"); 


  // Pasa las estructuras a la funcion estructuras_manipulacion_por_valor por valor 
  estructuras_manipulacion_por_valor(particula1, particula2); //Esta funcion iguala los datos
  

  //Note que esto crea una copia, no hace un paso por referencia
  // Imprimiendo el valor of particula2  
  printf("\n\n");
  printf("Imprimiendo el valor of particula2:\n");
  printf("%lf %lf %lf\n",particula2.pos[0],particula2.pos[1],particula2.pos[2]);
  printf("%lf %lf %lf\n",particula2.vel[0],particula2.vel[1],particula2.vel[2]);
  printf("%lf\n",particula2.masa);
  
  printf("particle2 no modifica su valor con este metodo\n");
  printf("\n\n");
  printf("\n\nIntentando modificar la variable particula2 pasando esta a una funcion por valor\n");


   // Pasa las estructuras a la funcion estructuras_manipulacion_por_valor por referencia   
  estructuras_manipulacion_por_referencia(&particula1, &particula2); //Evita el crear una copia

 // Imprimiendo el valor of particula2  
  printf("\n\n");
  printf("Imprimiendo el valor of particula2:\n");
  printf("%lf %lf %lf\n",particula2.pos[0],particula2.pos[1],particula2.pos[2]);
  printf("%lf %lf %lf\n",particula2.vel[0],particula2.vel[1],particula2.vel[2]);
  printf("%lf\n",particula2.masa);

  printf("particle2 modifica su valor exitosamente\n");
  //=============================================================================
  /*
    Aqui mostraremos la equivalencia entre la notacion de apuntadores y arreglos
  */
  
  printf("\n\n");
  printf("Los arreglos en C son apuntadores al primer elemento del arreglo:\n");
  printf("Ejemplo:\n");
  printf("El vector x:\n\n");
  
  for(i=0; i<3; i++)
    printf("x[%d] = %d\n",i,x[i]);
  
  printf("un puntero a x xPtr:\n\n");
 
  // pointer to x
  int *xPtr;
  xPtr = x; //Al igualar el puntero a un arreglo, puedo moverme por el puntero como un arreglo
  printf("&x = %p \t xPtr = %p \t &x[0] = %p \n\n",&x,xPtr,&x[0]); //Maxima prueba de que un arreglo es un puntero

  printf("\nDiferentes maneras de acceder a la componentes de x:\n\n");
  
  // Diferentes maneras de acceder a la componentes de x:
  // notacion de subindices del arreglo, notacion apuntador/desplazamiento y notacion de subindice arreglo 
  for(i=0; i<3; i++)
    printf("x[%d] = %d,  *(xPtr + %d) = %d,  xPtr[%d] = %d\n",i,x[i],i,*(xPtr + i),i,xPtr[i]);
  
  printf("\nmiremos las direcciones de memoria:\n\n");
  for(i=0; i<3; i++)
    printf("&x[%d] = %p,  (xPtr + %d) = %p,  &xPtr[%d] = %p\n\n",i,&x[i],i,(xPtr + i),i,&xPtr[i]);
  
  /*********************************************************************
   REGLA DE ORO: si queremos ahorrar en el uso de memoria debemos evitar
   al maximo el llamado de funciones por valor para evitar copias de las variables
  *********************************************************************/
  
  /*
    Aqui ilustramos como construir y usar arreglos de punteros 
  */
  //=============================================================
  
  printf("areglos de apuntadores:\n");
  int x1=1,x2=2,x3=3;
  int *x1Ptr,*x2Ptr,*x3Ptr;

  // Apuntadores a las variables enteras
  x1Ptr = &x1;
  x2Ptr = &x2;
  x3Ptr = &x3;

  // Declaracion de un arreglo de apuntadores
  int *arregloPtr[3]; //Note que esto se puede denotar como int **arregloPtr, puntero de punteros

  // Almaceno las dirreciones de memoria cd x1, x2 y x3 en arregloPtr
  arregloPtr[0] = x1Ptr; 
  arregloPtr[1] = x2Ptr; 
  arregloPtr[2] = x3Ptr; 
  
  // Print the memory direction of x1, x2 and x3 and their values
  printf("\n\n");
  printf("&x1 = %p \t x1 = %d\n",&x1,x1);
  printf("&x2 = %p \t x2 = %d\n",&x2,x2);
  printf("&x3 = %p \t x3 = %d\n",&x3,x3);


  
  // Imprime las direcciones de memoria almanecadas en arregloPtr y los valores almacenados en cada direccion de memoria
  printf("\n\n");
  for(i=0; i<3; i++)
    {
      printf("arregloPtr[%d] = %p \t  *arregloPtr[%d] = %d\n",i,arregloPtr[i],i,*arregloPtr[i]);
    }

  //========================================================================

  /*
    Aqui usaremos apuntadores a funciones en C.
    Al igual que los arreglos, el nombre de una funcion es un apuntador a 
    la direccion de memoria donde se encuentran las instrucciones de la
    definicion de la funcion
  */
  //========================================================================

  // La funcion potencia requiere de un puntero a al funcion Potencia_con_exponente_impar
  // o Potencia_con_exponente_par
  
  printf("\n\nLos nombres de las funciones son apuntadores a la direccion de memoria de la funcion\n");
  printf("por ejemplo:\n");
  printf("la funcion Potencia_con_exponente_impar = %p\n",Potencia_con_exponente_impar);
  printf("la Potencia_con_exponente_par = %p\n",Potencia_con_exponente_par);
   
  printf("\n\n");
  
  printf(" y = %d\n",y);

  printf("\ncalculando y^3 usando apuntadores a funciones\n");
  y =  Potencia(3, 3, 1, Potencia_con_exponente_impar); //Puedo mandarle una funciona otra funcion, porque al fin esa funcion es una direccion de memoria
  printf(" y^3 = %d\n",y);

  printf("\ncalculando y^2 usando apuntadores a funciones\n");
  y =  Potencia(3, 2, 2, Potencia_con_exponente_par);
  printf(" y^2 = %d\n",y);
 /*==========================================================================*/
 /*Arreglo de funciones*/
  // Aqui crearemos un arreglo de apuntadores a funciones llamado funciones,
  // La declaracion de ese arreglo de funciones se puede hacer de la forma:
  // <tipo de dato que retorna la funcion> (*arreglo[nuemro de funciones]) (argumentoa para las funciones);
  // las funciones deben retornar el mismo tipo de dato

  // Declaracion del arreglo de funciones  
  int (*funciones[2]) (const int,const int); //Note el *

  // Inicializa el arreglo con los apuntadores a las funciones
  // Potencia_con_exponente_impar y Potencia_con_exponente_par
  funciones[0] = Potencia_con_exponente_impar;
  funciones[1] = Potencia_con_exponente_par; 

  printf("\n\nArreglo de apuntadores a funciones funciones\n");
  printf("la funcion Potencia_con_exponente_impar = %p\n",Potencia_con_exponente_impar);
  printf("la funcion Potencia_con_exponente_par = %p\n\n",Potencia_con_exponente_par);
  printf("funciones = %p \t &funciones = %p \n",funciones,&funciones);
  printf("funciones[0] = %p *funciones[0] = %p\n",funciones[0],*funciones[0]);
  printf("funciones[1] = %p *funciones[1] = %p\n",funciones[1],*funciones[1]);
  
  // La variable eleccion puede ser usada para seleccionar una funcion del arreglo de funciones.
  // Esto puede ser util para hacer programas con menus que impliquen el uso de funciones
    
  int eleccion = 0;
 
  // Pasa la funcion Potencia_con_exponente_impar to Potencia
  y =  Potencia(4, 3, 1, funciones[0]);

  printf("\n\n");
  printf(" y = %d\n",y);

  // Pasa la funcion Potencia_con_exponente_par to Potencia 
  y =  Potencia(4, 2, 2, funciones[1]); //Solo basta mandarle la componente de arreglo que guarda la funcion

  printf("\n\n");
  printf(" y = %d\n",y);
 
  // Usa la funcion Potencia_con_exponente_impar directly, (3,3)
  y = funciones[0](3,3);

  printf("\n\n");
  printf(" y = %d\n",y);

  printf("\nEl mismo resultado anterior!\n\n");
  printf("\nParece que ya sabemos usar punteros en C...\n\n");
  //=============================================================

 return 0;
}
// fin de la funcion principal


// Eleva al cuadrado una variable con un llamado por valor
int cuadrado_por_valor(int n)
{
  printf("La direccion de memoria de n es &n = %p\n",&n);
  n = n * n;

  return n;
}

// Eleva al cuadrado una variable con un llamado por valor
int cuadrado_por_referencia(int *n)
{

  printf("La direccion de memoria de n es n = %p\n",n);  

  *n = (*n) * (*n); //Reasigna el valor del puntero n, multiplicando los valores guardados en la direccion

  return 0;
}

// Eleva al cuadrado las componentes de un vector
void cuadrado_con_vector(int n[3])
{
  int i;

  for(i=0; i<3; i++)  //Se sobreescribe el codigo, porque los arreglos son punteros
    n[i] = n[i] * n[i];

}

// Esta funcion recibe estructuras de datos por valor
int estructuras_manipulacion_por_valor(mi_propio_tipo_de_variable part1, mi_propio_tipo_de_variable part2)
{
  //Igualando las estructuras y creando una copia
  part2.pos[0] = part1.pos[0];
  part2.pos[1] = part1.pos[1];
  part2.pos[2] = part1.pos[2];
  part2.vel[0] = part1.vel[0];
  part2.vel[1] = part1.vel[1];
  part2.vel[2] = part1.vel[2];
  part2.masa = part1.masa;
  //No es necesario alamacenar, solo guardar la copia
  return 0;
}

// Esta funcion recibe estructuras de datos por valor
int estructuras_manipulacion_por_referencia(mi_propio_tipo_de_variable *part1,mi_propio_tipo_de_variable *part2)
{ //Iguala estructuras en particular el int puede ser un void

  (*part2).pos[0] = (*part1).pos[0];
  (*part2).pos[1] = (*part1).pos[1];
  (*part2).pos[2] = (*part1).pos[2];
  (*part2).vel[0] = (*part1).vel[0];
  (*part2).vel[1] = (*part1).vel[1];
  (*part2).vel[2] = (*part1).vel[2];
  (*part2).masa = (*part1).masa;
  //Paso por referencia 
  //No hay que retornar nada, solo almacenar el cambio en memoria
  return 0;
}

// Esta funcion recibe un puntero a una funcion para realizar una llamado a ella 
int Potencia(int x, int Exponente, int opcion, int (*elevadoA)(int, int))
{

  if(opcion==1)
    {
      return (*elevadoA)(x, Exponente);
    }

  if(opcion==2)
    {
      return (*elevadoA)(x, Exponente);
    }

}

// Eleva un entero a una potencia impar
int Potencia_con_exponente_impar(const int numero,const int exponente)
{ //const deja fija la variable dentro de esta funcion
  return pow(numero, exponente);
}

// Eleva un entero a una potencia par
int Potencia_con_exponente_par(const int numero,const int exponente)
{
  return pow(numero, exponente);
}

