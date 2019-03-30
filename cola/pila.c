#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define CAPACIDAD_I 10
#define CAPACIDAD_DUPLICAR 2

#define CAPACIDAD_ACHICADA 4
#define CAPACIDAD_ACHICAR 2 

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
bool pila_Redimensionar(pila_t *pila, size_t nuevaCapacidad){
	void** datosNuevos = realloc(pila->datos, (sizeof(void*) * nuevaCapacidad));
	
	if (datosNuevos == NULL) {
		return false;
	};
	
	pila->datos = datosNuevos;
	pila->capacidad = nuevaCapacidad;
	return true;
}


pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->datos = malloc(sizeof(void*) * CAPACIDAD_I);

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_I;
    
    return pila;
}

void pila_destruir(pila_t* pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila->capacidad == pila->cantidad){
		if(!pila_Redimensionar(pila, (pila->capacidad * CAPACIDAD_DUPLICAR))){
			return false;
		}
	}
	
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	
	return pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	
	if(pila->capacidad / CAPACIDAD_ACHICADA == pila->cantidad && pila->cantidad > CAPACIDAD_I){
		if(!pila_Redimensionar(pila, pila->capacidad / CAPACIDAD_ACHICAR)){
			return false;
		}
	}
	
	pila->cantidad--;
	return pila->datos[pila->cantidad];
}




