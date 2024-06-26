#include "allvars.h" //debe estar aca y en todos los modulos

double variable_global;
extern double variable_global3; // funciona, pero es mejor declarar en allvars

int main(void)
{

  variable_global =  2.0;
  printf("%lf\n",variable_global);

  printf("desde el main\n");
  doble(); // esta en funcion1
  triple(); // esta en funcion1

  printf("desde funcion1\n");
  llama_imprime(); // esta en funcion1 pero llama a imprime en funcion2
  
  printf("desde el main\n");
  printf("%lf\n",variable_global3); //declarada en funcion2

  return 0;
}
