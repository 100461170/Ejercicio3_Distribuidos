const MAX_SIZE = 256;
const MAX_VECTOR = 32;

struct peticion {
    int op;
    int key;
    opaque valor1[MAX_SIZE];
    int valor2_N;
    int* valor2_N_p;
    double valor2_value[MAX_VECTOR];
};

struct respuesta {
    int status;
    opaque valor1[MAX_SIZE];
    int N_value2;
    double valor2_value[MAX_VECTOR];
};

struct tupla {
    int clave;
    opaque valor1[MAX_SIZE];
    int valor2_N;
    double valor2_value[MAX_VECTOR];
};

program RPC {
    version RPCVER {
        int INIT() = 1;
        int SET_VALUE(struct peticion) = 2;
        int GET_VALUE(struct peticion, struct respuesta *resp) = 3;
        int MODIFY_VALUE(struct peticion) = 4;
        int DELETE_KEY(int key) = 5;
        int EXIST(int key) = 6;
    } = 1;
} = 99;
