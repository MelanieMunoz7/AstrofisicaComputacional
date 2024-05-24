/*Parcial 2 - Astrofisica Computacional
Punto 3: lista ligada para implementacion de estructuras
de datos autoreferencias                                                                                     
Melanie A. Munoz Chavarria*/

/*Nota: este codigo esta basado en el ejemplo del capitulo 12.4
del libro de Deitel*/

//Librerias
#include <stdio.h>
#include <stdlib.h>

//Creando la estructura del Nodo 
//Note que es una estructura de datos autocontenida
struct Nodo 
{   
    //Espacio para ingrasar las notas
    float Nota; 
    struct Nodo *siguienteNodo;
};

//Definiendo un nombre de tipo para estructura mas breve 
typedef struct Nodo NODO; 
//Luego un puntero a la estructura Nodo
//Note que se evita crear un puntero a otro puntero
typedef NODO *NODOPTR;

//Inicializando las funciones 
void inserta_en_lista(NODOPTR *cabeza, float valor);
char borrar_Elemento(NODOPTR *cabeza, float valor);
int lista_vacia(NODOPTR cabeza);
void imprimir_lista(NODOPTR NodoActual);


//Inicio funcion principal
int main()
{   
    //El puntero que apunta al incio de la cabeza, en principio apunta a NULL
    NODOPTR cabeza = NULL;
    char eleccion; 
    float valor; 

    //Condiciones para que usario ingrese 
    printf("Ingrese Y, para ingresar la Nota\n");
    printf("Ingrese C, ingrese para eliminar un elmento\n");
    printf("Ingrese N, para concluir la lista de Notas\n");

    printf("Ingrese el caracter para continuar, eliminar o parar: ");
    scanf("%c",&eleccion);

    while (eleccion != 'N')
    {
        switch(eleccion)
        {
            case 'Y':
                printf("Ingrese la nota:\n");
                scanf("\n%f",&valor);
                inserta_en_lista(&cabeza,valor);
                imprimir_lista(cabeza);
                break;

            case 'C':
                if(!lista_vacia(cabeza))  
                {  
                    printf("Ingrese la nota que quiere eliminar:\n");
                    scanf("\n%f",&valor);

                    if (borrar_Elemento(&cabeza, valor))
                    {
                        printf("\n%f eliminada\n", valor);
                        imprimir_lista(cabeza);
                    }

                    else
                    {
                        printf("\n%f -> este elemento no se encontro\n",valor);
                    }
                }   
            
                else
                {
                    printf("No se puede, la lista esta vacia\n");
                }

                break;
            
            default: 

                printf("No se esta ingresando un caracter correcto\n");
                break;

        }
    
    printf("Ingrese el caracter para continuar, eliminar o parar: ");
    //Se agrega un espacio para que el scanf leea cualquier espacio antes del valor ingresado
    scanf(" %c",&eleccion);
    }
    
    return 0;
}
//Fin funcion principal

//Rutina para insertar un elmento de los que ingrese el usario.

void inserta_en_lista(NODOPTR *cabeza, float valor)
{   
    //Para considerar los nodos antes, despues y el actual, entonces se crean los punteros a ellos
    NODOPTR nuevoNodoPtr, NodoPrevioPtr, NodoActualPtr;

    //Alocacion de memoria para el nuveo nodo
    //Esto es util porque la lista enlazada puede creceer, pero tambien reducirse. Entonces asi se ahorra memoria
    nuevoNodoPtr = malloc(sizeof(NODO));

    //Para analizar la disponibilidad de espacio
    //Y mirar si la asignacion de memoria va correcta
    if (nuevoNodoPtr != NULL)
    {   
        //Si la asinacion fue correcta se alamacena la Nota ingresada
        nuevoNodoPtr->Nota = valor;
        //Y se apunta al siguiente nodo
        //NULL porque es apunta a un nodo que se creara, pero aun no se ha creado
        nuevoNodoPtr->siguienteNodo = NULL;

        //Este puntero apunta al nodo previo al nuevo nodo
        //y como apenas se agrego el elemento a la lista, debe ir a NULL el puntero al nodo previo
        NodoPrevioPtr = NULL;
        //Esto indica la cabeza y punto de partida de la lista
        NodoActualPtr = *cabeza;

        //Se recorre la lista para ubicar el nuevo nodo, mientras que nodo actual no sea NULL y tenga un valor mayor que el ingresado

        while (NodoActualPtr != NULL && valor > NodoActualPtr->Nota)
        {
            //El puntero del NodoPrevio sigue al puntero del Nodo Actual, para ubicar al nuevo nodo
            NodoPrevioPtr = NodoActualPtr;
            NodoActualPtr = NodoActualPtr->siguienteNodo;  
        }

        if (NodoPrevioPtr ==NULL)
        {   
            //El nuevo nodo pasa a ser la cabeza de la Lista
            nuevoNodoPtr->siguienteNodo = *cabeza;
            *cabeza = nuevoNodoPtr;
        }

        //El nuevo nodo debe ingresarse en medio de la lista enlazada
        else
        {   //El puntero del Nodo previo apunta al nuevo nodo
            NodoPrevioPtr->siguienteNodo = nuevoNodoPtr;
            //Y el nuevo nodo apunta al actual
            nuevoNodoPtr->siguienteNodo = NodoActualPtr;
        }
    }

    else
    {
        //Si no se presenta memoria disponible
        printf("%f no se puede insertar. No hay memoria disponible.\n ",valor);
    }
}

//Esta funcion eliminara un elemento de la lista 

char borrar_Elemento(NODOPTR *cabeza, float valor)
{   
    //Se usaran para recorrer la lista y eliminar el elemento desado
    NODOPTR NodoTemporalPtr, NodoPrevioPtr, NodoActualPtr;

    //Para comprobar si se quiere eliminar el primer elemento de la lista
    if (valor == (*cabeza)->Nota)
    {   
        //Se crea un puntero temporal para la cabeza
        NodoTemporalPtr = *cabeza; 
        //Se dirige cabeza a puntar el siguinete Nodo
        *cabeza = (*cabeza)->siguienteNodo;
        //Se elimimna el elemento, liberando memoria
        free(NodoTemporalPtr);

        return valor;
    }

    else
    { //Se recorre la lista hasta encontrar la Nota que se quiere quitar 

        //Se apunta el nodo previo a la cabeza
        NodoPrevioPtr = *cabeza;
        //Y el nodo actual se apunta al elemento despues del primero, ie, despues de la cabeza
        NodoActualPtr = (*cabeza)->siguienteNodo;

        //Recorriendo hasta encontrar el elemento
        while (NodoActualPtr != NULL && NodoActualPtr->Nota != valor)
        {   
            //El nodo previo apunta al nodo actual
            NodoPrevioPtr = NodoActualPtr;
            //Y el nodo acutual se apunta al siguiente
            NodoActualPtr = NodoActualPtr->siguienteNodo;
        }

        
        if (NodoActualPtr != NULL)
        {   
            //Si se encuentra el nodo actual

            //El nodo temporal apunta al Nodo actual con el valor que se quiere eliminar
            NodoTemporalPtr = NodoActualPtr;

            //El nodo al que apunta el previo sera al que apunta el nodo que se desea eliminar
            NodoPrevioPtr->siguienteNodo = NodoActualPtr->siguienteNodo;

            //Se libera memoria
            free(NodoTemporalPtr);
            return valor;
        }
    }
    return '\0';
}

//Esta fucnion servira para evaluar el caso en que se desee eliminar un elemento
//Se eleiminara el elemento si la cabeza el diferente de NULL

int lista_vacia(NODOPTR cabeza)
{
    return cabeza == NULL;
}

//Esta funcion imprime la lista

void imprimir_lista(NODOPTR NodoActualPtr)
{   
    //Para garantizar que la lista no este vacia
    if (NodoActualPtr == NULL)
        printf("La lista se encuentra vacia\n");

    else
    {
        printf("La lista es:\n");
        //Para evitar que la lista este vacia
        while(NodoActualPtr != NULL)
        {
            printf("%f ",NodoActualPtr->Nota);
            //Recorre la lista en cada iteracion
            //Usando el entrelazamiento, para recorrer los valores almacenados
            NodoActualPtr = NodoActualPtr->siguienteNodo;
        }
    printf("\n===================\n");
    }
}


