#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
 
/* ****************************************************************
 *                  DEFINICION DE ESTRUCTURAS
 * ***************************************************************/
struct heap{
	size_t cant;
	size_t capacidad;
	void** datos;
	cmp_func_t cmp;
};

#define INICIAL_CAPACIDAD 20
#define INICIAL_CANT 0

#define POS_PADRE(A) ((A - 1) / 2)
#define POS_HIJO_IZQUIERDO(A) (2 * A + 1)
#define POS_HIJO_DERECHO(A) (POS_HIJO_IZQUIERDO(A) + 1)

#define TAMANIO_AGRANDADOR_VALOR 2
#define TAMANIO_AGRANDADOR(a) ((a) * TAMANIO_AGRANDADOR_VALOR)

#define TAMANIO_ACHICADOR_VALOR 2
#define TAMANIO_ACHICADOR(a) ((a) / TAMANIO_ACHICADOR_VALOR)

/* ****************************************************************
 *                     FUNCIONES AUXILIARES
 * ***************************************************************/
//-------------------------------------------------------------------------------
bool heap_redimensionar(heap_t* heap, size_t capacidad_nueva);

heap_t* _heap_crear(cmp_func_t cmp, size_t capacidad, size_t cant);

void up_heap(void* arreglo[], size_t pos, cmp_func_t cmp);

void down_heap(void* arreglo[], size_t pos, cmp_func_t cmp, size_t cant);

size_t get_hijo_mayor(void* arreglo[], size_t pos_padre, cmp_func_t cmp, size_t cant);

void swap(void *arreglo[], size_t x, size_t y);

void heapify(void *arreglo[], cmp_func_t cmp, size_t cant);
//-------------------------------------------------------------------------------

/* ****************************************************************
 *                     IMPLEMENTACION PRIMITIVAS
 * ***************************************************************/

heap_t* heap_crear(cmp_func_t cmp){
	return _heap_crear(cmp, INICIAL_CAPACIDAD, INICIAL_CANT); 
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){	
	heap_t* heap = _heap_crear(cmp, n, n);
	heapify(arreglo, cmp, n); //O(n)
	
	for(size_t i = 0; i < n; i++){ //O(n)
		heap->datos[i] = arreglo[i];
	}
	
	return heap;
}

heap_t* _heap_crear(cmp_func_t cmp, size_t capacidad, size_t cant){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap)
		return NULL;
	
	void** datos = malloc(sizeof(void*) * capacidad);
	if(!datos){
		free(heap);
		return NULL;
	}
	heap->datos = datos;
	heap->cant = cant;
	heap->capacidad = capacidad;
	heap->cmp = cmp;
	
	return heap;
}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap->capacidad == heap->cant){
		if(!heap_redimensionar(heap, TAMANIO_AGRANDADOR(heap->capacidad)))
			return false;
	}

	heap->datos[heap->cant] = elem;
	up_heap(heap->datos, heap->cant, heap->cmp);
	heap->cant++;
	
	return true;
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap))
		return NULL;
	
	if(heap->cant == TAMANIO_ACHICADOR(heap->capacidad) && heap->cant > INICIAL_CAPACIDAD){
		if(!heap_redimensionar(heap, TAMANIO_ACHICADOR(heap->capacidad)))
			return false;
	}
	
	void* elemt = heap->datos[0];
	swap(heap->datos, 0, heap->cant - 1);
	heap->datos[heap->cant - 1] = NULL;
	heap->cant--;
	
	down_heap(heap->datos, 0, heap->cmp, heap->cant);
	return elemt;	
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while(!heap_esta_vacio(heap)){
		void* elem = heap_desencolar(heap);
		if(destruir_elemento){
			destruir_elemento(elem);
		}
	}
	free(heap->datos);
	free(heap);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cmp, cant);
	for(size_t i = 0; i < cant; i++){
		size_t ultimo_relativo = cant - i - 1;
		swap(elementos, 0, ultimo_relativo);
		down_heap(elementos, 0, cmp, ultimo_relativo);
	}
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap_cantidad(heap) == 0;
}

void *heap_ver_max(const heap_t *heap){
	return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

//-------------------------------------------------------------------------------

bool heap_redimensionar(heap_t* heap, size_t capacidad_nueva){
	void** datos_nuevos = realloc(heap->datos, (sizeof(void*) * capacidad_nueva));
	
	if (!datos_nuevos) {
		return false;
	};
	
	heap->datos = datos_nuevos;
	heap->capacidad = capacidad_nueva;
	return true;
}


void swap (void *arreglo[], size_t x, size_t y) {
	void* aux = arreglo[x];
	arreglo[x] = arreglo[y];
	arreglo[y] = aux;
}

size_t get_hijo_mayor(void* arreglo[], size_t pos_padre, cmp_func_t cmp, size_t cant){
	size_t pos_hijo_der = POS_HIJO_DERECHO(pos_padre);
	size_t pos_hijo_izq = POS_HIJO_IZQUIERDO(pos_padre);
	
	if(pos_hijo_izq >= cant || pos_hijo_der >= cant){
		if(pos_hijo_izq >= cant)
			return cant;
		return pos_hijo_izq;
	}
	
	if(cmp(arreglo[pos_hijo_der], arreglo[pos_hijo_izq]) > 0)
		return pos_hijo_der;
		
	return pos_hijo_izq;
}

void up_heap(void* arreglo[], size_t pos, cmp_func_t cmp){
	if(pos == 0)
		return;
	
	size_t pos_padre = POS_PADRE(pos);
	
	if(cmp(arreglo[pos_padre], arreglo[pos]) > 0)
		return;
	
	swap(arreglo, pos_padre, pos);
	up_heap(arreglo, pos_padre, cmp);
}

void down_heap(void* arreglo[], size_t pos, cmp_func_t cmp, size_t cant){
	size_t pos_hijo_mayor = get_hijo_mayor(arreglo, pos, cmp, cant);
	if(pos_hijo_mayor == cant) return;
	
	if(cmp(arreglo[pos], arreglo[pos_hijo_mayor]) > 0)
		return;
		
	swap(arreglo, pos, pos_hijo_mayor);
	down_heap(arreglo, pos_hijo_mayor, cmp, cant);
}

void _heapify(void *arreglo[], size_t pos, cmp_func_t cmp, size_t cant){
	if(pos == 0)
		return;
		
	down_heap(arreglo, pos - 1, cmp, cant);
	_heapify(arreglo, pos - 1, cmp, cant);
}

void heapify(void *arreglo[], cmp_func_t cmp, size_t cant){
	size_t pos_ultimo_padre = (cant / 2);
	_heapify(arreglo, pos_ultimo_padre, cmp, cant);
}








