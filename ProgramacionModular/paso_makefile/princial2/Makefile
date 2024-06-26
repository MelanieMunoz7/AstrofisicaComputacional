
Hola_mundo: hola_mundo.c ../funcion2/funcion.c ../funcion2/funcion.h
	gcc -I../funcion2 hola_mundo.c ../funcion2/funcion.c -o hola_mundo.out
	echo "Hola amigos"
	ls

clean:
	rm hola_mundo.out *~

#objetivo: dependencia1 dependencia2 ... : lo que queremos construir y dependencias 
#<tab>comando1 , loq ue hay que ejecutar para construir el objeto
#<tab>comando2 
#<tab>...

# si cambia cualquier archivo, se recompila todo y el make pierde poder
# lo ideal es que solo compile lo que se actualizo
