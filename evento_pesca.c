#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TIPO_LECTURA "%[^;];%i;%i;%[^\n]\n"
#define TIPO_ESCRITURA "%s; %i; %i; %s\n"



arrecife_t* crear_arrecife(const char* ruta_archivo){
    pokemon_t pokemon;

    FILE* archivo_entrada = fopen(ruta_archivo, "r");
    if (!archivo_entrada){
        printf("Error al abrir el archivo arrecife.csv\n");
        return NULL;
    }

    arrecife_t* p_arrecife = malloc(sizeof(arrecife_t)); // Creo el arrecife en el heap y lo inicializo.
    if (p_arrecife == NULL){
        printf("Error al realizar el malloc en la funcion crear_arrecife.");
        fclose(archivo_entrada);
        return NULL;
    }
    p_arrecife->cantidad_pokemon = 0;
    p_arrecife->pokemon = NULL;

    int linea = fscanf(archivo_entrada, TIPO_LECTURA, pokemon.especie, &pokemon.velocidad, &pokemon.peso, pokemon.color);
    while (linea != EOF && linea == 4){
        (p_arrecife->cantidad_pokemon)++;
        pokemon_t* puntero_poke = realloc(p_arrecife->pokemon, (size_t)p_arrecife->cantidad_pokemon * sizeof(pokemon_t));
        if (puntero_poke == NULL){
            printf("Error al realizar el realloc en la funcion crear_arrecife.");
            return NULL;
        }
        p_arrecife->pokemon = puntero_poke;

        *(p_arrecife->pokemon + p_arrecife->cantidad_pokemon - 1) = pokemon; //Va a la ultima posicion del array de pokemones y agrega el pokemon leido recien.
        //printf("%s\n", p_arrecife->pokemon->especie);
        linea = fscanf(archivo_entrada, TIPO_LECTURA, pokemon.especie, &pokemon.velocidad, &pokemon.peso, pokemon.color);
    }

    fclose(archivo_entrada);
    
    return p_arrecife;
}


void censar_arrecife(arrecife_t* arrecife , void (*mostrar_pokemon)(pokemon_t*)){
    printf("\n\n************************************************************\n");
    printf("|%15s|%10s|%10s|%20s|\n", "POKEMON", "VELOCIDAD", "PESO", "COLOR");
    for (int i = 0; i < arrecife->cantidad_pokemon; i++){
        mostrar_pokemon((arrecife->pokemon) + i); // Le paso el puntero de la primera posicion y le sumo el i para moverse a la posicion correcta.
    }
    printf("************************************************************\n");
}


void liberar_acuario(acuario_t* acuario){
    free(acuario->pokemon);
    free(acuario);
}


void liberar_arrecife(arrecife_t* arrecife){
    free(arrecife->pokemon);
    free(arrecife);
}


acuario_t* crear_acuario(){
    acuario_t* p_acuario = malloc(sizeof(acuario_t));
    if (p_acuario == NULL) return NULL;
    p_acuario->cantidad_pokemon = 0;
    p_acuario->pokemon = NULL;
    return p_acuario;

}


int eliminar_pokemon_arrecife(arrecife_t* p_arrecife, int i){
    //printf("\nELimine al pokemon: %s\n", p_arrecife->pokemon[i].especie);
    p_arrecife->pokemon[i] = *(p_arrecife->pokemon + p_arrecife->cantidad_pokemon - 1); // Pongo al ultimo pokemon del array en la posicion del pokemon que quiero sacar.
    p_arrecife->cantidad_pokemon--;
    pokemon_t* p_aux = realloc(p_arrecife->pokemon, (size_t)p_arrecife->cantidad_pokemon * sizeof(pokemon_t)); //Como hice el -- antes, se achica y se come el ultimo lugar.
    if (p_aux == NULL){
            printf("Error al realizar el realloc en la funcion eliminar_pokemon_arrecife.");
            return -1;
    }
    p_arrecife->pokemon = p_aux;
    return 0;
}


int agregar_pokemon_acuario(acuario_t* p_acuario, pokemon_t pokemon){
    //printf("Entre");
    (p_acuario->cantidad_pokemon)++;
    pokemon_t* puntero_aux = realloc(p_acuario->pokemon, (size_t)p_acuario->cantidad_pokemon * sizeof(pokemon_t));
    if (puntero_aux == NULL){
        printf("Error al realizar el realloc en la funcion agregar_pokemon_acuario.");
        return -1;
    }
    p_acuario->pokemon = puntero_aux;

    *(p_acuario->pokemon + p_acuario->cantidad_pokemon - 1) = pokemon;
    return 0;
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
    //printf("Pokemones encontrados: %i\n", pk_encontrados);
    if (pk_encontrados < cant_seleccion){
        printf("No hay suficientes pokemones que cumplan con la condicion. pokemones solicitados: %i, pokemones encontrados: %i.\nNo se movio nada.\n", cant_seleccion, pk_encontrados);
        return -1;
    }

    pk_encontrados = 0;
    int i = 0;
    bool flag = false;
    printf("Tengo que pasar: %i pokemones\n", cant_seleccion);
    while (i < arrecife->cantidad_pokemon && pk_encontrados < cant_seleccion && flag == false){
        if (seleccionar_pokemon((arrecife->pokemon) + i)){
            printf("Encontre que cumple condicion: %s, lo paso.\n", ((arrecife->pokemon) + i)->especie);
            pk_encontrados++;
            if (agregar_pokemon_acuario(acuario, arrecife->pokemon[i]) == -1) flag = true;
            if (eliminar_pokemon_arrecife(arrecife, i) == -1) flag = true;
        }else{
            i++;
        }
    }
    printf("Ya pase los %i pokemones que me pediste pasar.", cant_seleccion);






    // Vuelvo a recorrer el arrecife y esta vez si agrego los pokemones al acuario y los elimino del arrecife.
    /*
    for (int j = 0; j < arrecife->cantidad_pokemon; j++){
        if (seleccionar_pokemon((arrecife->pokemon) + j)){
            //printf("Encontre que cumple condicion. %s\n", ((arrecife->pokemon) + j)->especie);
            if (agregar_pokemon_acuario(acuario, arrecife->pokemon[j]) == -1) return -1; // Si se produce un error al agregar al pokemon al acuario, el traslado retorna error.
            if (eliminar_pokemon_arrecife(arrecife, j) == -1) return -1; // Si se produce un error al eliminar al pk del arrecife, el traslado retorna error.
        }
    }*/
    return 0;
    
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
    printf("-Los pokemones del acuario han sido guardados exitosamente.-\n");
    return 0;
}

