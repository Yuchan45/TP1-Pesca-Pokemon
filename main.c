#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARCHIVO 100
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

bool trasladar_todo_pokemon(pokemon_t* pokemon){
    /*
    Traslada todo pokemon por lo que siempre devuelve true.
    */
    return true;
}

void mostrar_poke(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime todos los pokemones del arrecife en pantalla en forma de tabla.
    */
    printf("|%15s|%10i|%10i|%20s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

void mostrar_poke_color(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime todos los pokemones del arrecife en pantalla pero con color.
    */
    printf("\033[0;34m");
    printf("|%15s|%10i|%10i|%20s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
    printf("\033[0m");
}

void mostrar_solo_especie(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime la especie todos los pokemones del arrecife en pantalla.
    */
    printf("\033[0;32m");
    printf("%32s\n", pokemon->especie);
    printf("\033[0m");
}

void mostrar_lista_especies(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime todos los pokemones del arrecife en forma de lista, uno al lado del otro.
    */
    printf("\033[0;32m");
    printf("%s ", pokemon->especie);
    printf("\033[0m");
}

void mostrar_super_color(pokemon_t* pokemon){
    /*
    Funcion utilizada en conjunto con censar_arrecife. Imprime todos los pokemones del arrecife en forma de tabla con colores random.
    */
    int i = rand() % 7;
    i++;
    printf("\033[0;3%im", (char)i);
    printf("|%15s|%10i|%10i|%20s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
    printf("\033[0m");
}

bool extension_valida(char archivo[MAX_ARCHIVO]){
    /*
    Devuelve true en caso de que la extension sea de tipo ".txt". Caso contrario, retorna false.
    */
    char tipo_extension[10] = "";
    strcpy(tipo_extension, archivo + (strlen(archivo)-4));
    if ((strcmp(tipo_extension, ".txt") == 0) && (strlen(archivo) > 4)){
        //printf("archivo valido\n");
        return true;
    }else{
        //printf("archivo invalido\n");
        return false;
    }
}

int main(int argc, char *argv[]){
    if (extension_valida(argv[argc-1]) == false){
        return -1;
    }

    arrecife_t* p_arrecife = crear_arrecife(argv[argc-1]);
    if (p_arrecife == NULL) return -1;
    
    acuario_t* p_acuario = crear_acuario();
    if (p_acuario == NULL){
        liberar_arrecife(p_arrecife);
        return -1;
    }

    printf("\n --------------- POKEMONES EN EL ARRECIFE ----------------- ");
    censar_arrecife(p_arrecife, &mostrar_poke); // Aunque bien podria directamente pasar &mostrar_poke.

    printf("Funcion de seleccion: empieza con R o B.\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &empieza_con_r_o_b, 3);
    censar_arrecife(p_arrecife, &mostrar_poke); 
    
    printf("Funcion de seleccion: es liviano (< 20kg).\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_liviano, 3);
    censar_arrecife(p_arrecife, &mostrar_solo_especie); 
    
    printf("Funcion de seleccion: es liviano (< 20kg) Pero ahora le pido menos.\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_liviano, 2);
    censar_arrecife(p_arrecife, &mostrar_lista_especies); 
    
    printf("Funcion de seleccion: es rojo y pesado (> 50kg).\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_rojo_y_pesado, 2);
    censar_arrecife(p_arrecife, &mostrar_poke);

    printf("Funcion de seleccion: es rapido (velocidad > 45) Pero ahora le pido menos.\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &es_rapido, 2);
    censar_arrecife(p_arrecife, &mostrar_poke_color);

    printf("Funcion de seleccion: tiene nombre corto.\n\n");
    trasladar_pokemon(p_arrecife, p_acuario, &tiene_nombre_corto, 2);
    censar_arrecife(p_arrecife, &mostrar_super_color);
    
    //mostrar_acuario(p_acuario);   
    guardar_datos_acuario(p_acuario, RUTA_ACUARIO);

    liberar_arrecife(p_arrecife);
    liberar_acuario(p_acuario);
    
    return 0;
}
