const MAX = 256;
const MAX_VECTOR = 32;

typedef double array_double[MAX_VECTOR];
typedef int array_int[MAX_VECTOR];

struct peticion {
    int op;
    int key;
    string valor1<MAX>;
    int valor2_N;
    int* valor2_N_p;
    double valor2_value[MAX_VECTOR];
    string q_name<MAX>;
};

struct respuesta {
    int status;
    string valor1<MAX>;
    int N_value2;
    double valor2_value[MAX_VECTOR];
};

struct tupla {
    int clave;
    string valor1<MAX>;
    int valor2_N;
    double valor2_value[MAX_VECTOR];
};

program RPC {
    version RPCVER {
        int INIT() = 1;
        int SET_VALUE(int key, string value1<MAX>, int N_value2, array_double V_value2) = 2;
        int GET_VALUE(int key, string value1<MAX>, array_int N_value2, array_double V_value2) = 3;
        int MODIFY_VALUE(int key, string value1<MAX>, int N_value2, array_double V_value2) = 4;
        int DELETE_KEY(int key) = 5;
        int EXIST(int key) = 6;
    } = 1;
} = 99;