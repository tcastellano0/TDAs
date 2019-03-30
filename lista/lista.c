#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* nodoSiguiente;
} nodo_t;

struct lista{
	nodo_t* primerNodo;
	nodo_t* ultimoNodo;
	size_t cantDatos;
};

struct lista_iter{
	lista_t* lista;
	nodo_t* nodoAnterior;
	nodo_t* nodoActual;
};

lista_iter_t* lista_iter_crear(lista_t* lista){
	lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));

    if (lista_iter == NULL) {
        return NULL;
    }
    
    lista_iter->lista = lista;
    
    lista_iter->nodoActual = lista->primerNodo;
	lista_iter->nodoAnterior = NULL;

    return lista_iter;
}

void* lista_iter_ver_actual(const lista_iter_t* lista_iter){
	return !lista_iter->nodoActual ? NULL : lista_iter->nodoActual->dato;
}

bool lista_iter_avanzar(lista_iter_t* lista_iter){
	if(lista_iter_al_final(lista_iter)){
		return false;
	}
	
	lista_iter->nodoAnterior = lista_iter->nodoActual;
	lista_iter->nodoActual = lista_iter->nodoActual->nodoSiguiente;
	
	return true;
}

bool lista_iter_insertar(lista_iter_t* lista_iter, void* dato){
	nodo_t* nuevoNodo = malloc(sizeof(nodo_t));

	if(nuevoNodo == NULL){
		return false;
	}
	
	nuevoNodo->nodoSiguiente = lista_iter->nodoActual;
	nuevoNodo->dato = dato;
	
	lista_iter->lista->cantDatos++;
	
	if (lista_iter->nodoAnterior == NULL) {
		
		lista_iter->lista->primerNodo = nuevoNodo;
		
		if(lista_iter->nodoActual == NULL){
		  lista_iter->lista->ultimoNodo = nuevoNodo;
		}
		
		lista_iter->nodoActual = nuevoNodo;
		return true;
	}
	
	lista_iter->nodoAnterior->nodoSiguiente = nuevoNodo;
	if(lista_iter->nodoActual == NULL){
		lista_iter->lista->ultimoNodo = nuevoNodo;
	}
	  
	lista_iter->nodoActual = nuevoNodo;
	return true;
	
}

bool lista_iter_al_final(const lista_iter_t* lista_iter){
	return lista_iter->nodoActual == NULL;
}

void lista_iter_destruir(lista_iter_t* lista_iter){
	free(lista_iter);
}

void* lista_iter_borrar(lista_iter_t *lista_iter){
	
	if(lista_iter_al_final(lista_iter) || lista_esta_vacia(lista_iter->lista)){
		return NULL;
	}
	
	if(lista_iter->nodoAnterior == NULL){
		lista_iter->nodoActual = lista_iter->nodoActual->nodoSiguiente;
		return lista_borrar_primero(lista_iter->lista);
	}
	
	nodo_t* aux = lista_iter->nodoActual;
	void* dato = aux->dato;
	lista_iter->lista->cantDatos--;
	
	lista_iter->nodoAnterior->nodoSiguiente = lista_iter->nodoActual->nodoSiguiente;
	if(lista_iter->nodoActual->nodoSiguiente == NULL){
		lista_iter->lista->ultimoNodo = lista_iter->nodoAnterior;
	}
	
	lista_iter->nodoActual = lista_iter->nodoAnterior->nodoSiguiente;
	free(aux);
	
	return dato;
}


lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));

    if (lista == NULL) {
        return NULL;
    }
    
    lista->primerNodo = NULL;
    lista->ultimoNodo = NULL;
    lista->cantDatos = 0;
    
    return lista;	
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
	while(!lista_esta_vacia(lista)){
		void* dato = lista_ver_primero(lista);
		
		if (destruir_dato != NULL){
			destruir_dato(dato);
		}
		
		lista_borrar_primero(lista);
	};
	
	free(lista);
}

bool lista_insertar_primero(lista_t* lista, void* dato){
	nodo_t* nuevoNodo = malloc(sizeof(nodo_t));
	
	if(nuevoNodo == NULL){
		return false;
	}
	
	if(lista_esta_vacia(lista)){
		nuevoNodo->nodoSiguiente = NULL;
		nuevoNodo->dato = dato;
		
		lista->ultimoNodo = nuevoNodo;
	}else{
		nodo_t* nodoAux = lista->primerNodo;
		nuevoNodo->nodoSiguiente = nodoAux;
		nuevoNodo->dato = dato;
	}
	
	lista->primerNodo = nuevoNodo;
	lista->cantDatos++;
	
	return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
	nodo_t* nuevoNodo = malloc(sizeof(nodo_t));
	
	if(nuevoNodo == NULL){
		return false;
	}
	
	nuevoNodo->nodoSiguiente = NULL;
	nuevoNodo->dato = dato;
	
	if(lista_esta_vacia(lista)){
		lista->primerNodo = nuevoNodo;
		lista->ultimoNodo = nuevoNodo;
	}else{
		
		nodo_t* nodoAux = lista->ultimoNodo;
		nodoAux->nodoSiguiente = nuevoNodo;
		lista->ultimoNodo = nuevoNodo;
		
	}
	
	lista->cantDatos++;
	
	return true;

}

void* lista_borrar_primero(lista_t* lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	
	nodo_t* primerNodo = lista->primerNodo;
	void* datoReturn = primerNodo->dato;
	
	if(lista->primerNodo == lista->ultimoNodo){
		lista->primerNodo = NULL;
		lista->ultimoNodo = NULL;
	}else{
		lista->primerNodo = lista->primerNodo->nodoSiguiente;
	}

	free(primerNodo);
	
	lista->cantDatos--;
	return datoReturn;
}

size_t lista_largo(const lista_t* lista){
	return lista->cantDatos;
}

void* lista_ver_primero(const lista_t* lista){
	return lista_esta_vacia(lista) ? NULL : lista->primerNodo->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
	return lista_esta_vacia(lista) ? NULL : lista->ultimoNodo->dato;
}

bool lista_esta_vacia(const lista_t* lista){
	return lista->primerNodo == NULL;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	if(!visitar)
		return;
		
	nodo_t *actual = lista->primerNodo;
	while(actual){
		if(visitar(actual->dato, extra) == false){
			return;
		}
		actual = actual->nodoSiguiente;
	}
}


