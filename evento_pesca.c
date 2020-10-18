#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TIPO_LECTURA "%100[^;];%i;%i;%100[^\n]\n"
#define TIPO_ESCRITURA "%s; %i; %i; %s\n"

int eliminar_pokemon_arrecife(arrecife_t* p_arrecife, int i){
/*
    Devuelve 0 en caso de eliminar exitosamente el pokemon ubicado en la posicion i pasada por paramtro del arrecife. Retorna -1 de error.
*/
    p_arrecife->pokemon[i] = *(p_arrecife->pokemon + p_arrecife->cantidad_pokemon - 1); // Pongo al ultimo pokemon del array en la posicion del pokemon que quiero sacar.
    p_arrecife->cantidad_pokemon--;
    if (p_arrecife->cantidad_pokemon == 0){
        free(p_arrecife->pokemon);
        return 0;
    }
    pokemon_t* p_aux = realloc(p_arrecife->pokemon, (size_t)p_arrecife->cantidad_pokemon * sizeof(pokemon_t)); 
    if (p_aux == NULL){
            p_arrecife->cantidad_pokemon++;
            return -1;
    }
    p_arrecife->pokemon = p_aux;
    return 0;
}

int agregar_pokemon_acuario(acuario_t* p_acuario, pokemon_t pokemon){
/*
    Agrega el pokemon pasado por parametro al acuario tambien pasado por parametro. Retorna 0 en caso de exito y -1 en caso de error.
*/
    (p_acuario->cantidad_pokemon)++;
    pokemon_t* puntero_aux = realloc(p_acuario->pokemon, (size_t)p_acuario->cantidad_pokemon * sizeof(pokemon_t));
    if (puntero_aux == NULL){
        (p_acuario->cantidad_pokemon)--;
        return -1;
    }
    p_acuario->pokemon = puntero_aux;

    *(p_acuario->pokemon + p_acuario->cantidad_pokemon - 1) = pokemon;
    return 0;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){
    pokemon_t pokemon;

    FILE* archivo_entrada = fopen(ruta_archivo, "r");
    if (!archivo_entrada){
        printf("Error al abrir el archivo arrecife.csv\n");
        return NULL;
    }

    arrecife_t* p_arrecife = malloc(sizeof(arrecife_t)); // Creo el arrecife en el heap y lo inicializo.
    if (p_arrecife == NULL){
        printf("Error al realizar el malloc en crear_arrecife.\n");
        fclose(archivo_entrada);
        return NULL;
    }
    p_arrecife->cantidad_pokemon = 0;
    p_arrecife->pokemon = NULL;
    bool flag = false;

    int linea = fscanf(archivo_entrada, TIPO_LECTURA, pokemon.especie, &pokemon.velocidad, &pokemon.peso, pokemon.color);
    while (linea != EOF && linea == 4 && flag == false){
        (p_arrecife->cantidad_pokemon)++;
        pokemon_t* puntero_poke = realloc(p_arrecife->pokemon, (size_t)p_arrecife->cantidad_pokemon * sizeof(pokemon_t));
        if (puntero_poke == NULL){
            (p_arrecife->cantidad_pokemon)--;
            flag = true;
            return NULL;
        }
        p_arrecife->pokemon = puntero_poke;

        *(p_arrecife->pokemon + p_arrecife->cantidad_pokemon - 1) = pokemon; //Va a la ultima posicion del array de pokemones y agrega el pokemon leido recien.
        //printf("%s\n", p_arrecife->pokemon->especie);
        linea = fscanf(archivo_entrada, TIPO_LECTURA, pokemon.especie, &pokemon.velocidad, &pokemon.peso, pokemon.color);
    }

    fclose(archivo_entrada);
    if (flag || p_arrecife->cantidad_pokemon == 0){
        printf("sali, retorno NULL\n");
        free(p_arrecife); //Aca entra si el archivo ingresado esta vacio, por lo tanto no llegue a crear el vector de pokemones.
        return NULL;
    }
    return p_arrecife;
}

void censar_arrecife(arrecife_t* arrecife , void (*mostrar_pokemon)(pokemon_t*)){
    printf("\n*************************ARRECIFE***************************\n");
    //printf("|%15s|%10s|%10s|%20s|\n", "POKEMON    ", "VELOCIDAD ", "PESO   ", "COLOR        ");
    for (int i = 0; i < arrecife->cantidad_pokemon; i++){
        mostrar_pokemon((arrecife->pokemon) + i); // Le paso el puntero de la primera posicion y le sumo el i para moverse a la posicion correcta.
    }
    printf("\n************************************************************\n");
}

void liberar_acuario(acuario_t* acuario){
    if (acuario->cantidad_pokemon > 0){
        free(acuario->pokemon);
    }
    free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife){
    if (arrecife->cantidad_pokemon > 0){
        free(arrecife->pokemon);
    }
    free(arrecife);
}

acuario_t* crear_acuario(){
    acuario_t* p_acuario = malloc(sizeof(acuario_t));
    if (p_acuario == NULL) return NULL;
    p_acuario->cantidad_pokemon = 0;
    p_acuario->pokemon = NULL;
    return p_acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
    // Primero, tengo que recorrer el arrecife y ver si hay suficientes pokemones que complen con la condicion.
    int pk_encontrados = 0;
    for (int i = 0; i < arrecife->cantidad_pokemon; i++){
        if (seleccionar_pokemon((arrecife->pokemon) + i)){
            //printf("Encontre que cumple condicion. %s\n", ((arrecife->pokemon)+i)->especie);
            pk_encontrados++;
        }
    }
    if (pk_encontrados < cant_seleccion){
        printf("No hay suficientes pokemones que cumplan con la condicion. pokemones solicitados: %i, pokemones encontrados: %i.\nNo se movio nada.\n", cant_seleccion, pk_encontrados);
        return -1;
    }

    pk_encontrados = 0;
    int i = 0;
    bool flag = false;
    printf("Se realizara el traslado de: %i pokemones\n", cant_seleccion);
    while (i < arrecife->cantidad_pokemon && pk_encontrados < cant_seleccion && !flag){
        if (seleccionar_pokemon((arrecife->pokemon) + i)){
            printf("Traslado a %s al acuario\n", ((arrecife->pokemon) + i)->especie);
            pk_encontrados++;
            if (agregar_pokemon_acuario(acuario, arrecife->pokemon[i]) == -1) flag = true;
            if (eliminar_pokemon_arrecife(arrecife, i) == -1) flag = true;
        }else{
            i++;
        }
    }
    if (flag){
        printf("Error al realizar el traslado.\n");
        return -1;
    }else{
        printf("Traslado terminado con exito. El arrecife quedo de la sigueinte forma:\n");
        return 0;
    }
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
    FILE* archivo_salida = fopen(nombre_archivo, "w");
    if (!archivo_salida){
        printf(" - Error al crear el archivo de acuario_salida. - \n");
        return -1;
    } 
    
    for (int i = 0; i < acuario->cantidad_pokemon; i++){
        fprintf(archivo_salida, TIPO_ESCRITURA, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
    }
    fclose(archivo_salida);
    printf("\n\n-Los pokemones del acuario han sido guardados exitosamente.-\n");
    return 0;
}

