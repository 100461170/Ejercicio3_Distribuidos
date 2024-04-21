//
// Created by linux-lex on 29/02/24.
//
#include "funciones.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>

// declaracion de funciones
void tratar_peticion(struct peticion p_local, struct respuesta *resp);
int s_init();
int s_set_value(int key, char *valor1, int valor2_N, double *valor2_value);
int s_get_value(int key, char *valor1, int *valor2_N, double *valor2_value);
int s_modify_value(int key, char *valor1, int valor2_N, double *valor2_value);
int s_delete_key(int key);
int s_exist(int key);
int load();
int write_back();
void close_server();
int server_init();


// mutex para hacer peticiones concurrentes atómicas
pthread_mutex_t almacen_mutex;
// Almacen dinámico de tuplas
struct tupla* almacen = NULL;
// numero de elementos en el array
int n_elementos = 0;
// elmentos maximos del array
int max_tuplas = 50;

void tratar_peticion(struct peticion p_local, struct respuesta *resp){    
    // En funcion de la operacion especificada en la peticion hacemos una u otra operacion

    switch (p_local.op){
    case 0:
        resp->status = s_init();
        break;
    case 1:
        resp->status = s_set_value(p_local.key, p_local.valor1, p_local.valor2_N, p_local.valor2_value);
        break;
    case 2:
        resp->status = s_get_value(p_local.key, resp->valor1, &resp->N_value2, resp->valor2_value);
        break;
    case 3:
        resp->status = s_modify_value(p_local.key, p_local.valor1, p_local.valor2_N, p_local.valor2_value);
        break;
    case 4:
        resp->status = s_delete_key(p_local.key);
        break;
    case 5:
        resp->status = s_exist(p_local.key);
        break;
    }
}

int s_init() {
    // mutex lock
    pthread_mutex_lock(&almacen_mutex);
    free(almacen);
    almacen = NULL;
    almacen = (struct tupla *)malloc(max_tuplas * sizeof(struct tupla));
    // poner a 0 todos los elementos del almacen
    size_t elementos = max_tuplas * sizeof(struct tupla);
    memset(almacen, 0, elementos);
    pthread_mutex_unlock(&almacen_mutex);
    return 0;
}

int s_set_value(int key, char *valor1, int valor2_N, double *valor2_value) {
    // bloquear el mutex
    pthread_mutex_lock(&almacen_mutex);
    // comprobar la existencia de key
    // iterar por el almacen
    for (int i = 0; i < n_elementos; i++){
        if (almacen[i].clave == key){
            fprintf(stderr, "Error: Ya existe la key en el almacen. \n");
            pthread_mutex_unlock(&almacen_mutex);
            return -1;
        }
    }
    // comprobar el tamanio de almacen
    if (n_elementos == max_tuplas){
        // duplicar tamanio de almacen
        almacen = realloc(almacen, 2 * max_tuplas * sizeof(struct tupla));
        max_tuplas = max_tuplas * 2;
    }
    // crear tupla de insercion
    struct tupla insertar;
    insertar.clave = key;
    insertar.valor2_N = valor2_N;
    strcpy(insertar.valor1, valor1);
    // copiar vector
    for (int i = 0; i < valor2_N; i++) {
        insertar.valor2_value[i] = valor2_value[i];
    }
    // agregar a almacen
    
    almacen[n_elementos] = insertar;
    n_elementos++;
    // desbloquear mutex
    pthread_mutex_unlock(&almacen_mutex);
    // devolver valor
    return 0;
}

int s_get_value(int key, char *valor1, int *valor2_N, double *valor2_value){
    // iterar por el almacen
    
    pthread_mutex_lock(&almacen_mutex);
    int existe = -1;
    for (int i = 0; i < n_elementos; i++){
        if (almacen[i].clave == key){
            existe = 0;
            // copiar informacion
            strcpy(valor1, almacen[i].valor1);    
            *valor2_N = almacen[i].valor2_N;
            for (int j = 0; j<almacen[i].valor2_N; j++){
                valor2_value[j] = almacen[i].valor2_value[j];
            }

        }
    }
    

    pthread_mutex_unlock(&almacen_mutex);
    // devolver valor
    return existe;
}

int s_modify_value(int key, char *valor1, int valor2_N, double *valor2_value) {
    pthread_mutex_lock(&almacen_mutex);
    // iterar por almacen
    int existe = -1;
    for (int i = 0; i < n_elementos; i++){
        if (almacen[i].clave == key){
            existe = 0;
            // modificar valores
            strcpy(almacen[i].valor1, valor1);
            almacen[i].valor2_N = valor2_N;
            // igualar el vector a 0
            memset(almacen[i].valor2_value, 0, 32*sizeof(double));
            // copiar parametro a vector
            for (int j = 0; j<valor2_N; j++){
                almacen[i].valor2_value[j] = valor2_value[j];
            }
        }
    }
    pthread_mutex_unlock(&almacen_mutex);
    return existe;
}

int s_delete_key(int key) {
    pthread_mutex_lock(&almacen_mutex);
    int existe = -1;
    // iterar por el almacen
    for (int i = 0; i < n_elementos; i++){
        if (almacen[i].clave == key){
            existe = 0;
            // esto funciona si el orden de las tuplas no importa. Sino hay que cambiarlo
            // copiar ultimo elemento del almacen al indice
            almacen[i] = almacen[n_elementos-1];
            // borrar ultimo elemento del almacen
            struct tupla tupla_vacia;
            memset(&tupla_vacia, 0, sizeof(struct tupla));
            almacen[n_elementos-1] = tupla_vacia;
            // bajar el numero de elementos
            n_elementos--;
        }
    }
    pthread_mutex_unlock(&almacen_mutex);
    return existe;
}

int s_exist(int key) {
    pthread_mutex_lock(&almacen_mutex);
    int existe = 0;
    // iterar por el almacen
    for (int i = 0; i<n_elementos; i++){
        if (almacen[i].clave == key){
            existe = 1;
        }
    }
    pthread_mutex_unlock(&almacen_mutex);
    // devolver existencia
    return existe;
}

void close_server(){
    // hacer el free y salir
    printf("\n Closing server \n");
    write_back();
    free(almacen);
    almacen = NULL;
    exit(0);
}

int load(){
    // obtener directorio
    char cwd[MAX_SIZE];
    getcwd(cwd, sizeof(cwd));
    // crear directorio si no existe
    strcat(cwd, "/data_structure");
    DIR * dir = opendir(cwd);
    // existe el fichero
    if (dir){
        closedir(dir);
    }
    // no existe
    if (ENOENT == errno){
        mkdir(cwd, 0777);
    }
    // path del archivo
    char file[MAX_SIZE];
    strcpy(file, cwd);
    strcat(file, "/almacen.txt");
    // abrir descriptor de fichero
    FILE *f = fopen(file, "a+");
    rewind(f);
    // comprobar error al abrir fichero
    if (f == NULL){
        perror("Error en servidor al abrir el fichero");
        return -1;
    }
    // bucle para ir leyendo elementos
    while(fread(&almacen[n_elementos], sizeof(struct tupla), 1, f) == 1){
        // comprobar el tamanio de almacen
        if (n_elementos == max_tuplas-1){
            // duplicar tamanio de almacen
            almacen = realloc(almacen, 2 * max_tuplas * sizeof(struct tupla));
            max_tuplas = max_tuplas * 2;
        }
        n_elementos++;
    }
    fclose(f);
    // eliminar lo que tenemos en el archivo al haberlo pasado al almacen dinamico
    FILE *f_erase = fopen(file, "w");
    // comprobar reescribiendo el fichero
    if (f_erase == NULL){
        perror("Error en servidor al reescribir el fichero");
        return -1;
    }
    fclose(f_erase);
    return 0;
}
int write_back(){
    // cerrar colas servidor
    char file[MAX_SIZE];
    getcwd(file, sizeof(file));
    strcat(file, "/data_structure/almacen.txt");
    // abrir descriptor de archivo
    FILE *f = fopen(file, "w");
    // comprobar error al abrir archivo
    if (f == NULL){
        perror("Error en servidor al abrir el fichero");
        return -1;
    }
    // bucle para escribir en archivo
    for (int i=0; i<n_elementos; i++){
        fwrite(&almacen[i], sizeof(struct tupla), 1, f);
    }
    fclose(f);
    return 0;
}

int server_init(){
    // Inicializamos el almacén
    almacen = (struct tupla *)malloc(max_tuplas * sizeof(struct tupla));
    // signal para cerrar servidor
    signal(SIGINT, close_server);
    // cargamos los datos del almacen
    if (-1 == load()){
        fprintf(stderr, "Error en servidor al cargar el almacen del archivo binary\n");
        return -1;
    }
    // Inicializamos mutex y variable condicion
    pthread_mutex_init(&almacen_mutex, NULL);

    return 1;
}