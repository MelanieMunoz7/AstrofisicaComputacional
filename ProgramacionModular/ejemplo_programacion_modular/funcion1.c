#include "allvars.h" 

extern double variable_global; // declarada en el main
//double variable_global; //OJO declarada en el main
extern double variable_global3; // declarada en funcion2

void doble(void)
{

  variable_global = 2.0 * variable_global;
  printf("%lf\n",variable_global); 

}

void triple(void)
{

  inicializa();
  variable_global2 = 3.0 * variable_global2;
  printf("%lf\n",variable_global2); 

}

void inicializa(void)
{

  variable_global2 = 3.0;

}

void llama_imprime(void)
{
  imprime(); // esta en funcion2
  variable_global3 = 5.0;
}

