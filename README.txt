Introduccion del funionamiento del trabajo.

-El trabajo consiste en un puntero que apunta a una estructura (arrecife_t) la cual esta alojada en memoria. A su vez, esta estructura tambien apunta a un arreglo de pokemones, tambien en el heap, los cuales representarian a aquellos que viven en el arrecife. El programa se encarga de cargar los datos de los pokemones en el arrecife a traves de un archivo.csv ("arrecife.txt"). Asi como existe un arrecife con sus pokemones, tambien hay una esctructura (acuario_t) la cual apunta a la direccion de memoria de un array de pokemones los cuales representarian a los pokemones que viven en el acuario. 
En un principio el acuario se encuentra vacio, y el programa se encarga de trasladar a aquellos pokemones que cumplan ciertas condiciones del arrecife hacia el acuario. Estas condiciones estan dadas por Misty, como por ejemplo: "Que el pokemon sea ligero" para asi cansarse menos al trasladarlo.
Luego de cada traslado, se mostrara por pantalla los pokemones que siguen en el arrecife del modo que Misty desee. Para ello cuenta con 5 modos de mostrar el arrecife. Por ejemplo: modo lista, modo color, etc.
Por ultimo, se guardaran los pokemones que se encuentran en el acuario en un "acuario.txt".


Compilacion y ejecucion.

-Para compilar el trabajo, se debe abrir una terminal en el directorio de trabajo e ingresar la siguiente linea:
gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca

-Y para ejecutarlo:
./evento_pesca arrecife.txt
(Le paso el arrecife.txt como argumento de linea de comando)

Explicacion breve y concisa de conceptos:

1. Punteros
-Los punteros son variables las cuales contienen una direccion de memoria. Estos se declaran de la siguiente forma:
    char a;		/* Variable 'a' de tipo char */
    a ='a';     /* Le asigno 'a */
	char *pchar;	/* Puntero a char 'pchar' */	
	pchar = &a;	/* Le asigno la direccion de memoria de la variable a al puntero */
	printf("la direccion de memoria de 'a' es: %p \n", &a); /* Aca se muestra lo que contiene el puntero */ 
	printf("y su contenido es : %c \n", *pchar);. /* Aca se muestra lo que contiene aquello a lo que el puntero apunta. */

-Tambien se puede acceder al valor contenido en una direccion de memoria. Con el "*" antes del nombre del puntero, le digo que me muestre el VALOR de la direccion de memoria contenida en el puntero 

2. Aritmetica de punteros
Es posible realizar operaciones con los punteros, como sumas o restas, para hacer que este apunte a otra direccion de memoria. Por ejemplo, se puede tener un puntero que apunte a un arreglo, y este almacena la direccion del primer lugar del arreglo. Para acceder a las otras posiciones del arreglo, hay que sumar un valor. Este valor que se le suma depende del tipo de puntero. No es lo mismo si es un puntero de tipo int que un puntero de tipo char. Pero C es inteligente y le suma lo que debe dependiendo del tipo de dato con el que declaraste el puntero.

3. Punteros a funciones
Un puntero a funcion es lo mismo que cualquier otro puntero, solo que este almacena la direccion de memoria donde se aloja una funcion. La siguiente oracion es una equivalencia:
TIPO (*nombre_puntero_a_funcion)(TIPO_DE_DATO_DE_PARAMETRO) = &funcion_a_la_que_refiere;

Para hacer funciones que reciban punteros a otra funcion, tenes que definirla como en el siguiente ejemplo:
TIPO nombre_funcion (void (*nombre_puntero_a_funcion)(TIPO_DE_DATO));

Y si queres usar una funcion que recibe por parametro un puntero a otra funcion, simplemente debes pasarle la direccion de memoria de la funcion:
funcion(&puntero_a_funcion);


4. Malloc y Realloc
Malloc: La funcion malloc() reserva en memoria un valor size_t que recibe por parametro y devuelve un puntero a la memoria reservada. Retorna NULL en caso de fallar. Es de vital importancia realizar un free(puntero) una vez terminado su uso para asi liberar la memoria reservada. De no hacerlo, estas perdiendo memoria.

Realloc: La funcion realloc() recibe por parametro un puntero y un valor size_t. Modificara el tamaño de la memoria segun el espacio que le pidas de la direccion apuntada por el puntero que le pasaste. Realloc devuelve un puntero el cual puede ser el mismo que antes o no, porque en caso de que el nuevo tamaño no entre en la direccion anterior, se le asigna un nuevo lugar en la memoria. Un dato importante es que si el size que se le pasa por parametro es cero y el puntero no es NULL, entonces la llamada es equivalente a free(puntero) asi que no ahce falta volver a liberar.




