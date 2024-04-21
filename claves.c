//
// Created by linux-lex on 29/02/24.
//

#include "claves.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int init(){
    // variable de entorno
    char *host; 
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        return -1;
    }
    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_1;
    int result_1;
    // iniciar RPC
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }
    // funcion RPC
    retval_1 = init_1(&result_1, clnt);
    if (retval_1 != RPC_SUCCESS) {
    	clnt_perror (clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
    }
    clnt_destroy(clnt);
    return result_1;
}

int set_value(int key, char *value1, int N_value2, double *V_value2){
    // comprobar errores
    if (N_value2 < 1 || N_value2 > 32)
    {
        fprintf(stderr, "Error: N_value2 no esta en el rango [1,32].\n");
        return -1;
    }
    if (strlen(value1) > MAX_SIZE){
        fprintf(stderr, "Error: la cadena valor1 tiene mas de 256 caracteres.\n");
        return -1;
    }
    // variable de entorno
    char *host;
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        return -1;
    }

    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_2;
    int result_2;
    struct peticion set_value_1_arg1;
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }

    // copiar valores
    memset(&set_value_1_arg1, 0, sizeof(struct peticion));
    set_value_1_arg1.key = key;
    strcpy(set_value_1_arg1.valor1, value1);
    set_value_1_arg1.valor2_N = N_value2;
    for (int i = 0; i < set_value_1_arg1.valor2_N; i++){
		set_value_1_arg1.valor2_value[i] = V_value2[i];
	}
    // funcion RPC
    result_2 = 0;
    retval_2 = set_value_1(set_value_1_arg1, &result_2, clnt);
    if (retval_2 != RPC_SUCCESS){
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
    }
    clnt_destroy(clnt);
    return result_2;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2){
    // variable de entorno
    char *host; 
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        return -1;
    }
    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_3;
    struct respuesta result_3;
    struct peticion get_value_1_arg1;
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }
    // copiar valores
    memset(&get_value_1_arg1, 0, sizeof(struct peticion));
    get_value_1_arg1.key = key;
    // funcion RPC
    retval_3 = get_value_1(get_value_1_arg1, &result_3, clnt);
    if (retval_3 != RPC_SUCCESS){
		clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
	}
    // copiar valores
    strcpy(value1, result_3.valor1);
    *N_value2 = result_3.N_value2;
    for (int i = 0; i < *N_value2; i++){
        V_value2[i] = result_3.valor2_value[i];
    }
    clnt_destroy(clnt);
    return result_3.status;

}

int modify_value(int key, char *value1, int N_value2, double *V_value2){
    // comprobar errores
    if (N_value2 < 1 || N_value2 > 32){
        fprintf(stderr, "Error: N_value2 no esta en el rango [1,32].\n");
        return -1;
    }
    if (strlen(value1)>MAX_SIZE){
        fprintf(stderr, "Error: la cadena valor1 tiene mas de 256 caracteres.\n");
        return -1;
    }
    // variable de entorno
    char *host;
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        return -1;
    }
    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_4;
    int result_4;
    struct peticion modify_value_1_arg1;
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }
    // copiar valores
    memset(&modify_value_1_arg1, 0, sizeof(struct peticion));
    modify_value_1_arg1.key = key;
    strcpy(modify_value_1_arg1.valor1, value1);
    modify_value_1_arg1.valor2_N = N_value2;
    for (int i = 0; i < modify_value_1_arg1.valor2_N; i++){
        modify_value_1_arg1.valor2_value[i] = V_value2[i];
    }
    // funcion RPC
    retval_4 = modify_value_1(modify_value_1_arg1, &result_4, clnt);
    if (retval_4 != RPC_SUCCESS) {
    	clnt_perror (clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
    }
    clnt_destroy(clnt);
    return result_4;
}
int delete_key(int key){
    // variable de entorno
    char *host;
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        
        return -1;
    }
    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_5;
    int result_5;
    int delete_key_1_key;
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }
    // funcion RPC
    delete_key_1_key = key;
    retval_5 = delete_key_1(delete_key_1_key, &result_5, clnt);
    if (retval_5 != RPC_SUCCESS) {
    	clnt_perror (clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
    }
    clnt_destroy(clnt);
    return result_5;
}

int exist(int key){
    // variable de entorno
    char *host; 
    host = getenv("IP_TUPLAS");
    if (host == NULL){
        fprintf(stderr, "Variable de entorno IP_TUPLA no definida.\n");
        return -1;
    }
    // declaracion variables RPC
    CLIENT *clnt;
    enum clnt_stat retval_6;
    int result_6;
    int exist_1_key;
    clnt = clnt_create(host, RPC, RPCVER, "tcp");
    if (clnt == NULL){
        clnt_pcreateerror(host);
        return -1;
    }
    // funcion RPC
    exist_1_key = key;
    retval_6 = exist_1(exist_1_key, &result_6, clnt);
    if (retval_6 != RPC_SUCCESS) {
    	clnt_perror (clnt, "call failed");
        clnt_destroy(clnt);
        return -1;
    }
    clnt_destroy(clnt);
    return result_6;
}




