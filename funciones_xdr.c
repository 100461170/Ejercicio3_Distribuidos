/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "funciones.h"

bool_t
xdr_peticion (XDR *xdrs, peticion *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->op))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->key))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->valor1, MAX_SIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->valor2_N))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->valor2_N_p, sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->valor2_value, MAX_VECTOR,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_respuesta (XDR *xdrs, respuesta *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->status))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->valor1, MAX_SIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->N_value2))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->valor2_value, MAX_VECTOR,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_tupla (XDR *xdrs, tupla *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->clave))
		 return FALSE;
	 if (!xdr_opaque (xdrs, objp->valor1, MAX_SIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->valor2_N))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->valor2_value, MAX_VECTOR,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_get_value_1_argument (XDR *xdrs, get_value_1_argument *objp)
{
	 if (!xdr_peticion (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->resp, sizeof (respuesta), (xdrproc_t) xdr_respuesta))
		 return FALSE;
	return TRUE;
}
