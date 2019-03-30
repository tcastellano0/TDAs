#include "cola.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct nodo{
	void* dato;
	struct nodo* nodoSiguiente;
} nodo_cola_t;

struct cola{
	nodo_cola_t* primerNodo;
	nodo_cola_t* ultimoNodo;
};

nodo_cola_t* cola_nodo_crear(void* valor){
	nodo_cola_t* nuevoNodo = malloc(sizeof(nodo_cola_t));

	if (nuevoNodo == NULL) {
        return NULL;
    }
    
	nuevoNodo->dato = valor;
	nuevoNodo->nodoSiguiente = NULL;
	
	return nuevoNodo;
}

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));

    if (cola == NULL) {
        return NULL;
    }
    
    cola->primerNodo = NULL;
    cola->ultimoNodo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->primerNodo == NULL;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	
	return cola->primerNodo->dato;
}

void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	
	nodo_cola_t* primerNodo = cola->primerNodo;
	void* datoReturn = primerNodo->dato;
	
	if(cola->primerNodo == cola->ultimoNodo){
		cola->primerNodo = NULL;
		cola->ultimoNodo = NULL;
	}else{
		cola->primerNodo = cola->primerNodo->nodoSiguiente;
	}

	free(primerNodo);

	return datoReturn;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(!cola_esta_vacia(cola)){
		void* dato = cola_desencolar(cola);
		
		if (destruir_dato != NULL){
			destruir_dato(dato);
		}
	};
	
	free(cola);
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_cola_t* nuevoNodo = cola_nodo_crear(valor);
	
	if(nuevoNodo == NULL){
		return false;
	}
	
	if(cola_esta_vacia(cola)){
		cola->primerNodo = nuevoNodo;
	}else{
		cola->ultimoNodo->nodoSiguiente = nuevoNodo;
	}
	
	cola->ultimoNodo = nuevoNodo;

	return true;
}






