/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FUNCIONES_H_RPCGEN
#define _FUNCIONES_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SIZE 256
#define MAX_VECTOR 32

struct peticion {
	int op;
	int key;
	char valor1[MAX_SIZE];
	int valor2_N;
	int *valor2_N_p;
	double valor2_value[MAX_VECTOR];
};
typedef struct peticion peticion;

struct respuesta {
	int status;
	char valor1[MAX_SIZE];
	int N_value2;
	double valor2_value[MAX_VECTOR];
};
typedef struct respuesta respuesta;

struct tupla {
	int clave;
	char valor1[MAX_SIZE];
	int valor2_N;
	double valor2_value[MAX_VECTOR];
};
typedef struct tupla tupla;

struct get_value_1_argument {
	struct peticion arg1;
	struct respuesta *resp;
};
typedef struct get_value_1_argument get_value_1_argument;

#define RPC 99
#define RPCVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define INIT 1
extern  enum clnt_stat init_1(int *, CLIENT *);
extern  bool_t init_1_svc(int *, struct svc_req *);
#define SET_VALUE 2
extern  enum clnt_stat set_value_1(struct peticion , int *, CLIENT *);
extern  bool_t set_value_1_svc(struct peticion , int *, struct svc_req *);
#define GET_VALUE 3
extern  enum clnt_stat get_value_1(struct peticion , struct respuesta *, int *, CLIENT *);
extern  bool_t get_value_1_svc(struct peticion , struct respuesta *, int *, struct svc_req *);
#define MODIFY_VALUE 4
extern  enum clnt_stat modify_value_1(struct peticion , int *, CLIENT *);
extern  bool_t modify_value_1_svc(struct peticion , int *, struct svc_req *);
#define DELETE_KEY 5
extern  enum clnt_stat delete_key_1(int , int *, CLIENT *);
extern  bool_t delete_key_1_svc(int , int *, struct svc_req *);
#define EXIST 6
extern  enum clnt_stat exist_1(int , int *, CLIENT *);
extern  bool_t exist_1_svc(int , int *, struct svc_req *);
extern int rpc_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define INIT 1
extern  enum clnt_stat init_1();
extern  bool_t init_1_svc();
#define SET_VALUE 2
extern  enum clnt_stat set_value_1();
extern  bool_t set_value_1_svc();
#define GET_VALUE 3
extern  enum clnt_stat get_value_1();
extern  bool_t get_value_1_svc();
#define MODIFY_VALUE 4
extern  enum clnt_stat modify_value_1();
extern  bool_t modify_value_1_svc();
#define DELETE_KEY 5
extern  enum clnt_stat delete_key_1();
extern  bool_t delete_key_1_svc();
#define EXIST 6
extern  enum clnt_stat exist_1();
extern  bool_t exist_1_svc();
extern int rpc_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_peticion (XDR *, peticion*);
extern  bool_t xdr_respuesta (XDR *, respuesta*);
extern  bool_t xdr_tupla (XDR *, tupla*);
extern  bool_t xdr_get_value_1_argument (XDR *, get_value_1_argument*);

#else /* K&R C */
extern bool_t xdr_peticion ();
extern bool_t xdr_respuesta ();
extern bool_t xdr_tupla ();
extern bool_t xdr_get_value_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FUNCIONES_H_RPCGEN */
