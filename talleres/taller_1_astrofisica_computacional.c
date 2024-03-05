//**Taller 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
/*Elabore un programa que determine si un numero es positivo, negativo o cero.*/
 int primerNumero; 
 printf("Elabore un programa que determine si un numero es positivo, negativo o cero.\n");
 printf("Ingrese el numero: \n");
 scanf("%d",&primerNumero);

 if (primerNumero>0){
    printf("El numero es positivo\n");
 }
 else if (primerNumero<0){
    printf("El numero es negativo\n");
}

 else{   
 printf("El numero es cero\n");
 }

/*Elabore un programa que determine si un numero es par o impar*/
 int segundoNumero;
  printf("\nElabore un programa que determine si un numero es par o impar\n");
  printf("Ingrese el numero: ");
  scanf("%d",&segundoNumero);

  if (segundoNumero%2==0) {
    printf("El numero es par\n");
  }
  
  else{
    printf("El numero es impar\n");
  }

/*Elabore un programa que dado un numero n y m haga las operaciones 
suma, resta,multiplicacion y division.*/
 double n;
 double m;
 printf("\nElabore un programa que dado un numero n y m haga las operaciones suma, resta,multiplicacion y division.\n");
 printf("\nIngrese los numero: \n");
 scanf("%lf %lf",&n, &m);

 double suma;
 suma = m+n;
 printf("La suma de m y n es: %lf\n",suma);

 double resta;
 resta= n-m;
 printf("La resta de n y m es: %lf\n",resta);

 double multiplicacion;
 multiplicacion= m*n;
 printf("La multplicacion de m y n es: %lf\n",multiplicacion);

 double division;
 division=n/m;
 printf("La division de n entre m es: %lf\n", division);

/*Elabore un programa que dado el radio r de una circunferencia calcule el diametro y el area.*/

 double radio;
 printf("\nElabore un programa que dado el radio r de una circunferencia calcule el diametro y el area.\n");
 printf("Ingrese el radio de la circunferencia: ");
 scanf("%lf", &radio);

 double diametro;
 diametro= 2*radio; 
 printf("El diametro de la circunferencia es: %lf\n", diametro);

 double area;
 area= pow(radio, 2)*M_PI;
 printf("El area de la circunferenica es: %lf\n", area);

/*Elabore un programa que calcule el Indice de Masa Corporal (Body Mass Index [BMI]) 
y entregue el valor y en que categoria se encuentra: Peso bajo, peso normal, sobrepeso, obesidad.*/

double peso; 
double estatura; 
printf("\nElabore un programa que calcule el Indice de Masa Corporal (Body Mass Index [BMI]) y entregue el valor y en que categoria se encuentra: Peso bajo, peso normal, sobrepeso, obesidad.\n");
printf("Ingrese el peso (kg) y la estatura (m): ");
scanf("%lf %lf",&peso,&estatura);

double indiceDeMasaCorporal; 

indiceDeMasaCorporal= peso/ pow(estatura, 2); 

if (indiceDeMasaCorporal<18.5){
    printf("Bajo peso\n");
}

else if (indiceDeMasaCorporal >= 18.5 && indiceDeMasaCorporal <= 24.9){
    printf("Normal\n");
}

else if (indiceDeMasaCorporal >= 25 && indiceDeMasaCorporal <= 29.9){
    printf("Sobrepeso\n");
}
else if (indiceDeMasaCorporal>=30){
    printf("Obesidad\n");
}

/*Elabore un programa que permita saber si un numero N es multiplo o divisor de un
numero M.*/

int numeroN;
int numeroM; 
printf("\nElabore un programa que permita saber si un numero N es multiplo o divisor de un numero M.\n");

printf("Ingrese el numero N y el numero M: \n"); 
scanf("%d %d",&numeroN,&numeroM);

if (numeroM!=0)
{
  if ((numeroN%numeroM)==0)
{
  printf("El numero %d es multiplo y divisor del numero %d\n", numeroM,numeroN); 
}
else
{
  printf("El numero %d no es multiplo y tampoco divisor de de %d\n", numeroM, numeroN);
}
}else
{
  printf("El numero %d debe ser diferente de cero", numeroM);
}

/*Elabore un programa que pida al usuario 2 numeros y devuelva el mayor de estos.*/
  double numeroUno; 
  double numeroDos;

  printf("\nElabore un programa que pida al usuario 2 numeros y devuelva el mayor de estos.\n");  
  printf("Ingrese dos numeros: \n");
  scanf("%lf %lf", &numeroUno,&numeroDos);

  if (numeroUno>numeroDos)
  {
    printf("El mayor es %lf\n", numeroUno);
  }
  else if(numeroDos>numeroUno)
  {
    printf("El mayor es %lf\n", numeroDos);
  }
  else
  {
    printf("Ambos numeros son iguales");
  }

/*Elabore un programa que calcule el promedio de 5 valores ingresados por el usuario.*/

 double primeraEntrada;
 double segundaEntrada;
 double terceraEntrada;
 double cuartaEntrada;
 double quintaEntrada; 
 double promedio; 


 printf("\nElabore un programa que calcule el promedio de 5 valores ingresados por el usuario.\n");
 printf("Ingrese los cinco valores a los cuales desea calcularles el promedio:\n");
 scanf("%lf %lf %lf %lf %lf", &primeraEntrada, &segundaEntrada, &terceraEntrada, &cuartaEntrada, &quintaEntrada); 
 
 promedio=(primeraEntrada + segundaEntrada + terceraEntrada + cuartaEntrada + quintaEntrada)/2.0;
 printf("El promedio de los numeros ingresados es: %lf\n", promedio);

 /*Elabore un programa que calcula la suma de 1 hasta un numero N dado.*/

 int maximoSuma;
 int i;
 int suma1;

 printf("\nElabore un programa que calcula la suma de 1 hasta un numero N dado.\n");
 printf("Ingrese el valor hasta el que desea calcular la suma (note que debe ser un numero entero positivo): \n");
 scanf("%d",&maximoSuma);

 suma1=0;

 for(i=1;i<=maximoSuma;i=i+1)
 {
  suma1= i+ suma1;
 }

 printf("Total sumatoria hasta valor ingresado: %d\n", suma1);

 /*Elabore un programa que calcule la suma de los primeros N numeros impares.*/

 int maxSuma; 
 int j; 
 int sumaImpares; 

 printf("\nElabore un programa que calcule la suma de los primeros N numeros impares.\n");
 printf("Ingrese el numero hasta el que desea que vaya la sumatoria (recuerde que debe ser natural): \n");
 scanf("%d", &maxSuma);

 sumaImpares=0;

 for (j=1; j<=maxSuma; j=j+2)
 {
  sumaImpares= j+ sumaImpares;
 }

 printf("La sumatoria es: %d\n", sumaImpares);

 /*Elabore un programa que calcule a pi*/

  double sumatoriaPi; 
  int k;
  int valorMaximo;

  printf("\nElabore un programa que calcule Pi apatir de la forma dada\n");
  printf("Ingrese el valor hasta el que se desea calcular el valor de pi:\n ");
  scanf("%d", &valorMaximo);

  sumatoriaPi = 0;

  for (k=0; k<=valorMaximo; k=k+1)
  {
    sumatoriaPi = sumatoriaPi + pow(-1,k)/(2.0*k+1);
  }
  printf("El resultado de la sumatoria es %lf\n", sumatoriaPi*4);

  /*Elabore un programa que calcule los primeros N terminos de la sucesion de Fibonacci.*/
  int terminosFibonacci;
  int Fibonacci1;
  int Fibonacci2; 
  int l;
  int FibonacciTotal;

  printf("\nElabore un programa que calcule los primeros N terminos de la sucesion de Fibonacci.\n");
  printf("Ingrese el numero de terminos de Fibonnacci que desea calcular:");
  scanf("%d",&terminosFibonacci); 

  Fibonacci1 = 1;
  Fibonacci2 = 1;
  if ( terminosFibonacci>0 && terminosFibonacci<=2)
  {
    for (l=1;l<=terminosFibonacci; l=l+1)
    {
        printf("%d\n", Fibonacci1);
    }
  }
  else if (terminosFibonacci>2)
    {printf("%d\n%d\n", Fibonacci1, Fibonacci2);
    for (l=1; l<=terminosFibonacci-2; l=l+1)
    {
    FibonacciTotal=Fibonacci1 + Fibonacci2;
    Fibonacci1=Fibonacci2;
    Fibonacci2=FibonacciTotal;
    printf("%d\n", FibonacciTotal);
    }}

/*Elabore un programa que lea dos enteros positivos n y m , y que calcule e imprima el
resultado de multiplicar m por n utilizando  unicamente la operacion de suma.*/

double multiplicando; 
double multiplicador;
double producto1;
int d;

printf("\nElabore un programa que lea dos enteros positivos n y m , y que calcule e imprima el resultado de multiplicar m por n utilizando  unicamente la operacion de suma.\n");

printf("Ingrese el multiplicando y el multiplicandor: \n");
scanf("%lf %lf", &multiplicando,&multiplicador);

producto1=0;
for (d=1; d<=multiplicador; d=d+1)
{
    producto1=producto1+multiplicando;
}
printf("La multiplicacion es: %lf\n", producto1);


/*Elabore un programa que determine si un numero n es primo.*/
int posibleNumeroPrimo;
int divisor; 
int contadorDivisor; 

printf("\nElabore un programa que determine si un numero n es primo.\n");
printf("Ingrese el numero entero positivo para veluar si es primo: \n"); 
scanf("%d", &posibleNumeroPrimo);

contadorDivisor=0;

for (divisor = 1; divisor<=posibleNumeroPrimo; divisor = divisor +1)
{   if (posibleNumeroPrimo%divisor==0)
    {contadorDivisor = contadorDivisor + 1;
    }
}

if (contadorDivisor==2)
{printf("El numero es primo\n");}
else
{printf("El numero no es primo\n");}

/*Elabore un programa que lea un entero n y que determine e imprima si es un numero
perfecto. Un numero perfecto es aquel cuya suma de sus divisores desde 1 hasta n − 1
es n, por ejemplo, 6 es un numero perfecto ya que 1 + 2 + 3 = 6.*/

int posibleNumeroPerfecto;
int divisorPerfecto;
int sumaIgualAlPerfecto;

printf("\n Numero perfecto\n");
printf("Ingrese el numero para evaluar si es perfecto:\n");
scanf("%d",&posibleNumeroPerfecto);


sumaIgualAlPerfecto=0;

for (divisorPerfecto=1; divisorPerfecto<posibleNumeroPerfecto; divisorPerfecto=divisorPerfecto+1)
{ 
    if (posibleNumeroPerfecto%divisorPerfecto==0)
        {sumaIgualAlPerfecto = divisorPerfecto + sumaIgualAlPerfecto;}
}
if (sumaIgualAlPerfecto==posibleNumeroPerfecto)
    {printf("El numero es perfecto\n");}

else 
{printf("El numero no es perfecto\n");}

return 0;

}