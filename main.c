#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RUTA_ACUARIO "acuario.txt"
#define VELOCIDAD 45
#define PESADO 50
#define LIVIANO 20
#define ROJO "rojo"
#define NOMBRE_CORTO 6


void mostrar_acuario(acuario_t* p_acuario){
    /*
    Imprime todos los pokemones del acuario en pantalla.
    */
    printf("\n\n**************************ACUARIO***************************\n");
    printf("|%15s|%10s|%10s|%20s|\n", "POKEMON", "VELOCIDAD", "PESO", "COLOR");
    for (int i = 0; i < p_acuario->cantidad_pokemon; i++){
        printf("|%15s|%10i|%10i|%20s|\n", p_acuario->pokemon[i].especie, p_acuario->pokemon[i].velocidad, p_acuario->pokemon[i].peso, p_acuario->pokemon[i].color);
    }
    printf("************************************************************\n");
}
void mostrar_poke(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime el pokemon del arrecife en pantalla.
    */
    printf("|%15s|%10i|%10i|%20s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}
bool es_liviano(pokemon_t* pokemon){
    /*
    Devuelve true en caso de que el pokemon pese menos que 20kg. Sino devuelve false.
    */
    return pokemon->peso < LIVIANO;
}
bool es_rojo_y_pesado(pokemon_t* pokemon){
    /*
    Devuelve true en caso de que el pokemon sea rojo y pese mas de 50kg. Sino devuelve false.
    */
    return (strcmp(pokemon->color, ROJO) == 0) && (pokemon->peso > PESADO);
}
bool empieza_con_r_o_b(pokemon_t* pokemon){
    /*
    Devuelve true en caso de que el nombre del pokemon empiece con "R" o "B". Sino devuelve false.
    */
    return pokemon->especie[0] == 'R' || pokemon->especie[0] == 'B';
}
bool es_rapido(pokemon_t* pokemon){
    /*
    Devuelve true en caso de que el pokemon tenga velocidad mayor a 45. Sino devuelve false.
    */
    return pokemon->velocidad > VELOCIDAD;
}
bool tiene_nombre_corto(pokemon_t* pokemon){
    /*
    Devuelve true en caso de que el nombre del pokemon tenga menos de 6 caracteres. Sino devuelve false.
    */
    return strlen(pokemon->especie) < NOMBRE_CORTO;
}

int main(int argc, char *argv[]){
    arrecife_t* p_arrecife = crear_arrecife(argv[argc-1]);
    if (p_arrecife == NULL) return -1;
    acuario_t* p_acuario = crear_acuario();
    if (p_acuario == NULL) return -1;

    void (*mostrar_pokemon)(pokemon_t*) = &mostrar_poke; // Declaro el puntero a la funcion "mostrar_pokemon".
    censar_arrecife(p_arrecife, mostrar_pokemon);

    //bool (*seleccionar_pokemon)(pokemon_t*) = &empieza_con_r_o_b; // Esto es equivalente.
    printf("Funcion de seleccion: empieza con R o B.\n");
    trasladar_pokemon(p_arrecife, p_acuario, &empieza_con_r_o_b, 3);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    printf("Funcion de seleccion: es liviano (< 20kg).\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_liviano, 3);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    printf("Funcion de seleccion: es liviano (< 20kg) Pero ahora le pido menos.\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_liviano, 2);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    printf("Funcion de seleccion: es rojo y pesado (> 50kg).\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_rojo_y_pesado, 2);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    printf("Funcion de seleccion: es rapido (velocidad > 45) Pero ahora le pido menos.\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_rapido, 2);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    printf("Funcion de seleccion: tiene nombre corto.\n");
    trasladar_pokemon(p_arrecife, p_acuario, &tiene_nombre_corto, 2);
    censar_arrecife(p_arrecife, mostrar_pokemon);

    //mostrar_acuario(p_acuario);
    guardar_datos_acuario(p_acuario, RUTA_ACUARIO);

    liberar_arrecife(p_arrecife);
    liberar_acuario(p_acuario);
    return 0;
}
