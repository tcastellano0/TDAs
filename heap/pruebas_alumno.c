#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* ******************************************************************
 *                        PRUEBAS ALUMNO
 * *****************************************************************/

int _strcmp(const void *a, const void *b){
	char* s_1 = (char*)a;
	char* s_2 = (char*)b;
	
	return strcmp(s_1, s_2);
}

int intcmp(const void *a, const void *b){
	int* int_1 = (int*)a;
	int* int_2 = (int*)b;
	
	if(*int_1 != *int_2)
		return (*int_1 > *int_2) ? 1 : -1;
	
	return 0;
}

void pruebas_heap_vacio(){
	heap_t* heap = heap_crear(_strcmp);
	
	print_test("El heap recien creado debe estar vacio", heap_esta_vacio(heap));
	print_test("La cantidad de elementos debe ser 0", heap_cantidad(heap) == 0);
	print_test("Ver max debe ser NULL", heap_ver_max(heap) == NULL);
	print_test("Ver desencolar debe ser NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);
}

void pruebas_heap_encolar(){
	heap_t* heap = heap_crear(_strcmp);
	
	char *claves[] = {"C", "B", "A", "E"};
	
	print_test("Encolo en el heap el valor C", heap_encolar(heap, claves[0]));
	print_test("La cantidad de elementos debe ser 1", heap_cantidad(heap) == 1);
	print_test("Encolo en el heap el valor B", heap_encolar(heap, claves[1]));
	print_test("La cantidad de elementos debe ser 2", heap_cantidad(heap) == 2);
	print_test("Veo que el valor maximo sea C", (char*)heap_ver_max(heap) == claves[0]);
	print_test("La cantidad de elementos debe seguir siendo 2", heap_cantidad(heap) == 2);
	print_test("Encolo en el heap el valor A", heap_encolar(heap, claves[2]));
	print_test("La cantidad de elementos debe ser 3", heap_cantidad(heap) == 3);
	print_test("Veo que el valor maximo sea C", (char*)heap_ver_max(heap) == claves[0]);
	print_test("Encolo en el heap el valor E", heap_encolar(heap, claves[3]));
	print_test("La cantidad de elementos debe ser 4", heap_cantidad(heap) == 4);
	print_test("Veo que el valor maximo sea E", (char*)heap_ver_max(heap) == claves[3]);
	print_test("Veo que el valor maximo no sea C", (char*)heap_ver_max(heap) != claves[0]);
	print_test("El heap no debe estar vacio", !heap_esta_vacio(heap));
	
	heap_destruir(heap, NULL);
}

void pruebas_heap_desencolar(){
	heap_t* heap = heap_crear(_strcmp);
	char *claves[] = {"C", "B", "A", "E", "H", "W", "D"};
	
	print_test("Encolo en el heap el valor C", heap_encolar(heap, claves[0]));
	print_test("Encolo en el heap el valor B", heap_encolar(heap, claves[1]));
	print_test("Encolo en el heap el valor A", heap_encolar(heap, claves[2]));
	print_test("Encolo en el heap el valor E", heap_encolar(heap, claves[3]));
	print_test("Encolo en el heap el valor W", heap_encolar(heap, claves[5]));
	print_test("Encolo en el heap el valor H", heap_encolar(heap, claves[4]));
	print_test("Encolo en el heap el valor D", heap_encolar(heap, claves[6]));
	
	print_test("Veo que el valor maximo sea W", (char*)heap_ver_max(heap) == claves[5]);
	print_test("La cantidad de elementos debe ser 7", heap_cantidad(heap) == 7);
	
	print_test("Desencolo, el valor debe ser W", (char*)heap_desencolar(heap) == claves[5]);
	print_test("Veo que el valor maximo sea H", (char*)heap_ver_max(heap) == claves[4]);
	print_test("La cantidad de elementos debe ser 6", heap_cantidad(heap) == 6);
	
	print_test("Desencolo, el valor debe ser H", (char*)heap_desencolar(heap) == claves[4]);
	print_test("Veo que el valor maximo sea E", (char*)heap_ver_max(heap) == claves[3]);
	print_test("La cantidad de elementos debe ser 5", heap_cantidad(heap) == 5);
	print_test("El heap no debe estar vacio", !heap_esta_vacio(heap));
	
	print_test("Desencolo, el valor debe ser E", (char*)heap_desencolar(heap) == claves[3]);
	print_test("Veo que el valor maximo sea D", (char*)heap_ver_max(heap) == claves[6]);
	print_test("La cantidad de elementos debe ser 4", heap_cantidad(heap) == 4);
	
	print_test("Desencolo, el valor debe ser D", (char*)heap_desencolar(heap) == claves[6]);
	print_test("Desencolo, el valor debe ser C", (char*)heap_desencolar(heap) == claves[0]);
	print_test("Desencolo, el valor debe ser B", (char*)heap_desencolar(heap) == claves[1]);
	print_test("Desencolo, el valor debe ser A", (char*)heap_desencolar(heap) == claves[2]);
	print_test("El heap debe estar vacio", heap_esta_vacio(heap));
	print_test("La cantidad de elementos debe ser 0", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
}

void pruebas_heap_memoria_dinamica(){
	heap_t* heap = heap_crear(_strcmp);
	
	char* valor1 = malloc(10 * sizeof(char));
    char* valor2 = malloc(5 * sizeof(char));
    char* valor3 = malloc(10 * sizeof(char));
    char* valor4 = malloc(5 * sizeof(char));
    char* valor5 = malloc(10 * sizeof(char));
    char* valor6 = malloc(5 * sizeof(char));
	char* valor7 = malloc(10 * sizeof(char));
	
	*valor1 = '1'; *valor2 = '2'; *valor3 = '3';
    *valor4 = '4'; *valor5 = '5'; *valor6 = '6';
	*valor7 = '7';
	
	print_test("Encolo en el heap el valor 1", heap_encolar(heap, valor1));
	print_test("Encolo en el heap el valor 2", heap_encolar(heap, valor2));
	print_test("Encolo en el heap el valor 3", heap_encolar(heap, valor3));
	print_test("Encolo en el heap el valor 4", heap_encolar(heap, valor4));
	print_test("Encolo en el heap el valor 5", heap_encolar(heap, valor5));
	print_test("Encolo en el heap el valor 6", heap_encolar(heap, valor6));
	print_test("Encolo en el heap el valor 7", heap_encolar(heap, valor7));
	
	print_test("Tiene que liberar toda la memoria", true);
	heap_destruir(heap, free);
}



void pruebas_heap_volumen(size_t volumen){
	heap_t* heap = heap_crear(intcmp);
	bool result = true;
	
	for(size_t i = 0; i < volumen; i++){
		size_t* nro = malloc(sizeof(size_t));
		*nro = i;
		result &= heap_encolar(heap, nro);
	}
	
	size_t* dato;
	
	for(size_t i = 0; i < volumen; i++){
		dato = (size_t*)heap_desencolar(heap);
		result &= (*dato == volumen - i- 1);
		free(dato);
	}
	
	printf("Pruebas de voluemn para %zu elementos \n", volumen);
	print_test("Resultado ", result);
	heap_destruir(heap, NULL);
}

void pruebas_heap_arr_sort(){

	printf("Pruebas de Heap Sort para letras \n");
	
	size_t n = 7;
	void *letras_desordenadas[] = {"C", "B", "A", "E", "H", "W", "D"};
	char *letras_ordenadas_asc[] = {"A", "B", "C", "D", "E", "H", "W"};
	
	heap_sort(letras_desordenadas, n, _strcmp);
	
	bool result = true;
	for(size_t i = 0; i < n; i++){
		result &= (*(char*)letras_desordenadas[i] == *(char*)letras_ordenadas_asc[i]);
	}
	
	print_test("Resultado ", result);
	
	printf("Pruebas de Heap Sort para numeros \n");
	
	n = 6;
	int numero1 = 1; int numero2 = 2; int numero3 = 3;
	int numero4 = 4; int numero5 = 5; int numero6 = 6;
	void* numeros_desc[] = { &numero6 , &numero5 , &numero4, 
							 &numero3, &numero2, &numero1 };
	
	int numeros_asc[] = {1, 2, 3, 4, 5, 6};
	 
	heap_sort(numeros_desc, n, intcmp);
	
	result = true;
	for(size_t i = 0; i < n; i++){
		result &= (*(int*)numeros_desc[i] == numeros_asc[i]);
	}
	
	print_test("Resultado ", result);
}

void pruebas_heap_crear_desde_arr(){
	
	printf("Prueba crear Heap desde array de letras, debe cumplir la invariante \n");
	
	size_t arr_letras_n = 7;
	void *arr_letras[] = {"C", "B", "A", "E", "H", "W", "D"};
	char *letras_ordenadas_desc[] = {"W", "H", "E", "D", "C", "B", "A"};
	
	heap_t* heap = heap_crear_arr(arr_letras, arr_letras_n, _strcmp);
	
	bool result = true;
	int i = 0;
	while(!heap_esta_vacio(heap) && i < arr_letras_n){
		result &= (*(char*)heap_desencolar(heap) == *letras_ordenadas_desc[i]);
		i++;
	}
	
	heap_destruir(heap, NULL);
	print_test("Resultado ", result);
}

void pruebas_heap_alumno(void){
	pruebas_heap_vacio();
	pruebas_heap_encolar();
	pruebas_heap_desencolar();
	pruebas_heap_memoria_dinamica();
	pruebas_heap_volumen(200);
	pruebas_heap_volumen(300);
	pruebas_heap_volumen(400);
	pruebas_heap_volumen(500);
	pruebas_heap_volumen(1000);
	pruebas_heap_volumen(4000);
	pruebas_heap_volumen(8000);
	pruebas_heap_arr_sort();
	pruebas_heap_crear_desde_arr();
}
