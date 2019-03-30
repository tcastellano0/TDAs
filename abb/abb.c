#include "abb.h"
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct abb_nodo abb_nodo_t;


struct abb_nodo{
  abb_nodo_t* izq;
  abb_nodo_t* der;
  char* clave;
  void* dato;
};

struct abb{
  abb_nodo_t* raiz;
  abb_comparar_clave_t cmp;
  abb_destruir_dato_t destruir_dato;
  size_t cant;
};

struct abb_iter{
	pila_t* pila;
};

typedef enum nodo_tipo_t {NODO_BINARIO, NODO_UNITARIO, NODO_HOJA} nodo_tipo_t;

//----
char* get_copy(const char* clave);

abb_nodo_t* abb_nodo_buscarle_padre(const abb_t* abb, const char* clave);
abb_nodo_t* abb_nodo_buscar_reemplazante(const abb_t* abb, abb_nodo_t* nodo);
abb_nodo_t* abb_nodo_buscar_desde_raiz(const abb_t* abb, const char* clave);
abb_nodo_t* abb_nodo_buscar(const abb_t* abb, abb_nodo_t* nodo, const char* clave);

abb_nodo_t* abb_nodo_crear(const abb_t* abb, char* clave, void* dato);
void abb_nodo_editar(const abb_t* abb, abb_nodo_t* nodo, char* clave, void* dato);
bool abb_nodo_insertar(abb_t* abb, char* clave, void* dato);

void* abb_nodo_borrar_hoja(abb_t* abb, abb_nodo_t* nodo);
void* abb_nodo_borrar_unitario(abb_t* abb, abb_nodo_t* nodo);
void* abb_nodo_borrar_binario(abb_t* abb, abb_nodo_t* nodo);

nodo_tipo_t abb_nodo_tipo(abb_nodo_t* nodo);
void* abb_nodo_destruir(abb_nodo_t* nodo);

void abb_nodo_swap(abb_nodo_t* nodo_A, abb_nodo_t* nodo_B);
void abb_nodo_cambiar_hijo(const abb_t* abb, abb_nodo_t* nodo_padre, abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_hijo_nuevo);


/* ****************************************************************
 *                    PRIMITIVAS DEL ABB
 * ***************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if (!abb) 
		return NULL;
		
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cant = 0;
	abb->raiz = NULL;

	return abb;
}

//----
size_t abb_cantidad(abb_t *arbol){
	return arbol->cant;
}

//----
void* abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_nodo_buscar_desde_raiz(arbol, clave);
	
	return nodo ? nodo->dato : NULL;
}

//----
bool abb_pertenece(const abb_t *arbol, const char *clave){
	return abb_nodo_buscar_desde_raiz(arbol, clave) != NULL;
}

//----
void* abb_nodo_destruir(abb_nodo_t* nodo){
	void* dato = nodo->dato;
	free(nodo->clave);
	free(nodo);

	return dato;
}

void _abb_destruir_arbol(abb_t* abb, abb_nodo_t* nodo){
  	if(!nodo) return;
  	_abb_destruir_arbol(abb,nodo->izq);
  	_abb_destruir_arbol(abb,nodo->der);
  	void* dato = abb_nodo_destruir(nodo);
  	if(abb->destruir_dato){
    	abb->destruir_dato(dato);
  	}
}

void abb_destruir(abb_t *arbol){
	_abb_destruir_arbol(arbol,arbol->raiz);
	free(arbol);
}
//----

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	char* _clave = get_copy(clave);
	if(!_clave)
		return false;
	
	abb_nodo_t* nodo = abb_nodo_buscar_desde_raiz(arbol, _clave);
	if(nodo){
		abb_nodo_editar(arbol, nodo, nodo->clave, dato);
		free(_clave);
		return true;
	}
	
	return abb_nodo_insertar(arbol, _clave, dato);
}

void* abb_borrar(abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_nodo_buscar_desde_raiz(arbol, clave);
	if(!nodo)
		return NULL;
	
	arbol->cant--;
	
	nodo_tipo_t nodo_tipo = abb_nodo_tipo(nodo);
	
	if(nodo_tipo == NODO_HOJA)
		return abb_nodo_borrar_hoja(arbol, nodo);
	if(nodo_tipo == NODO_UNITARIO)
		return abb_nodo_borrar_unitario(arbol, nodo);
	
	return abb_nodo_borrar_binario(arbol, nodo);
}


/* ****************************************************************
 *                   IMPLEMENTACIO FUNCIONES AUXILIARES
 * ***************************************************************/

void abb_nodo_editar(const abb_t* abb, abb_nodo_t* nodo, char* clave, void* dato){
	void* dato_nodo = nodo->dato;
	if(abb->destruir_dato)
		abb->destruir_dato(dato_nodo);
	
	nodo->clave = clave;
	nodo->dato = dato;
}

abb_nodo_t* abb_nodo_crear(const abb_t* abb, char* clave, void* dato){
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (!nodo) 
		return NULL;
	
	nodo->clave = NULL;
	nodo->dato = NULL;
	nodo->der = NULL;
	nodo->izq = NULL;
	abb_nodo_editar(abb, nodo, clave, dato);
	
	return nodo;
}

bool abb_nodo_insertar(abb_t* abb, char* clave, void* dato){
	abb_nodo_t* nodo_nuevo = abb_nodo_crear(abb, clave, dato);
	if(!nodo_nuevo)
		return false;

	abb->cant++;
	if(!abb->raiz){
		abb->raiz = nodo_nuevo;
		return true;
	}
	
	abb_nodo_t* nodo_padre = abb_nodo_buscarle_padre(abb, clave);

	abb_nodo_cambiar_hijo(abb, nodo_padre, nodo_nuevo, nodo_nuevo);

	return true;
}

void* abb_nodo_borrar_hoja(abb_t* abb, abb_nodo_t* nodo){
	abb_nodo_t* nodo_padre = abb_nodo_buscarle_padre(abb, nodo->clave);
	
	abb_nodo_cambiar_hijo(abb, nodo_padre, nodo, NULL);
	
	if(abb_cantidad(abb) == 0)
		abb->raiz = NULL;
	
	return abb_nodo_destruir(nodo);
}

void* abb_nodo_borrar_unitario(abb_t* abb, abb_nodo_t* nodo){
	
	abb_nodo_t* nodo_padre = abb_nodo_buscarle_padre(abb, nodo->clave);
	abb_nodo_t* nodo_nieto = nodo->der ? nodo->der : nodo->izq;
	
	if(abb->raiz == nodo)
		abb->raiz = nodo_nieto;

	abb_nodo_cambiar_hijo(abb, nodo_padre, nodo, nodo_nieto);
	
	return abb_nodo_destruir(nodo);
}

void* abb_nodo_borrar_binario(abb_t* abb, abb_nodo_t* nodo){
	abb_nodo_t* nodo_reemplazante = abb_nodo_buscar_reemplazante(abb, nodo);

	char* _clave = get_copy(nodo_reemplazante->clave);
	void* dato_reemplazante;
	void* dato_return = nodo->dato;
	
	nodo_tipo_t nodo_tipo = abb_nodo_tipo(nodo_reemplazante);
	if(nodo_tipo == NODO_HOJA)
		dato_reemplazante = abb_nodo_borrar_hoja(abb, nodo_reemplazante);
	else
		dato_reemplazante = abb_nodo_borrar_unitario(abb, nodo_reemplazante);
	
	free(nodo->clave);
	nodo->clave = _clave;
	nodo->dato = dato_reemplazante;
	
	return dato_return;
}

abb_nodo_t* abb_nodo_buscar_desde_raiz(const abb_t* abb, const char* clave){
	 return abb_nodo_buscar(abb, abb->raiz, clave);
}

abb_nodo_t* _abb_nodo_buscarle_padre(const abb_t* abb, abb_nodo_t* nodo, const char* clave){

	if(abb->cmp(clave, nodo->clave) < 0){
		if(!nodo->izq){
			return nodo;
		}
		if(abb->cmp(clave, nodo->izq->clave) == 0){
			return nodo;
		}
		return _abb_nodo_buscarle_padre(abb, nodo->izq, clave);
	}
	
	if(abb->cmp(clave, nodo->clave) > 0){
		if(!nodo->der){
			return nodo;
		}
		if(abb->cmp(clave, nodo->der->clave) == 0){
			return nodo;
		}
		return _abb_nodo_buscarle_padre(abb, nodo->der, clave);
	}
	
	return nodo;
}

abb_nodo_t* abb_nodo_buscarle_padre(const abb_t* abb, const char* clave){
	return _abb_nodo_buscarle_padre(abb, abb->raiz, clave);
}

void abb_nodo_cambiar_hijo(const abb_t* abb, abb_nodo_t* nodo_padre, abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_hijo_nuevo){
	if (abb->cmp(nodo_hijo->clave, nodo_padre->clave) < 0)
		nodo_padre->izq = nodo_hijo_nuevo;
	else
		nodo_padre->der = nodo_hijo_nuevo;
}

abb_nodo_t* abb_nodo_buscar_reemplazante(const abb_t* abb, abb_nodo_t* nodo){
	nodo = nodo->der;
	while (nodo->izq) {
		nodo = nodo->izq;
	}
	return nodo;
}

abb_nodo_t* abb_nodo_buscar(const abb_t* abb, abb_nodo_t* nodo, const char* clave){
	if (!nodo)
		return NULL;

	if (abb->cmp(clave, nodo->clave) < 0){
		return abb_nodo_buscar(abb, nodo->izq, clave);
	}

	if (abb->cmp(clave, nodo->clave) > 0){
		return abb_nodo_buscar(abb, nodo->der, clave);
	}

	return nodo;
}

void abb_nodo_swap(abb_nodo_t* nodo_A, abb_nodo_t* nodo_B){
	char* auxclave = nodo_A->clave;
	void* auxdato = nodo_A->dato;
	
	nodo_A->clave = nodo_B->clave;
	nodo_A->dato = nodo_B->dato;
	
	nodo_B->clave = auxclave;
	nodo_B->dato = auxdato;
}

nodo_tipo_t abb_nodo_tipo(abb_nodo_t* nodo){
	if(nodo->izq == NULL && nodo->der == NULL){
		return NODO_HOJA;
	}
	if((nodo->izq != NULL && nodo->der == NULL) || (nodo->izq == NULL && nodo->der != NULL)){
		return NODO_UNITARIO;
	}

	return NODO_BINARIO;	
}

char* get_copy(const char* clave){
	char* copia_clave = malloc(sizeof(char) * (strlen(clave) + 1));
	if(!copia_clave) 
		return NULL;
	
	strcpy(copia_clave, clave);
	
	return copia_clave;
}

/* ****************************************************************
 *                 ITERADOR INTERNO
 * ***************************************************************/
bool _abb_in_order(abb_nodo_t* abb_nodo, bool visitar(const char *clave, void *dato, void* extra), void *extra){
	if(!abb_nodo) return true;
	
	if(!_abb_in_order(abb_nodo->izq, visitar, extra))
		return false;
	
	if(!visitar(abb_nodo->clave, abb_nodo->dato, extra)){
		return false;
	}
	
	_abb_in_order(abb_nodo->der, visitar, extra);
	
	return true;
	
}

void abb_in_order(abb_t *arbol, bool visitar(const char *clave, void *dato, void* extra), void *extra){
	_abb_in_order(arbol->raiz, visitar, extra);
}

/* ****************************************************************
 *                 ITERADOR EXTERNO
 * ***************************************************************/

void abb_iter_apilar_nodo_y_rama_izq(pila_t* pila_abb_iter, abb_nodo_t* nodo_desde){
   if(nodo_desde){
     abb_nodo_t* actual = nodo_desde;
     pila_apilar(pila_abb_iter, actual);
     while (actual && actual->izq) {
		 pila_apilar(pila_abb_iter, actual->izq);
		 actual = actual->izq;
     }
   }
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter) 
		return NULL;

	pila_t* pila_abb = pila_crear();
	if(!pila_abb){
		free(iter);
		return NULL;
	}
	iter->pila = pila_abb;
	
	abb_iter_apilar_nodo_y_rama_izq(iter->pila, arbol->raiz);
	return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return false;

	abb_nodo_t* abb_nodo_desapilado = pila_desapilar(iter->pila);
	abb_iter_apilar_nodo_y_rama_izq(iter->pila, abb_nodo_desapilado->der);

	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return abb_iter_in_al_final(iter) ? NULL : ((abb_nodo_t*)pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}
