#include "cola.h"
#include "vector_dinamico.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void cola_vector_destruir(void* vector){
	vector_destruir(vector);
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_cola_vacia(){
	
	cola_t* colaP = cola_crear();
	
	print_test("Verifico que una cola recien creada este vacia", cola_esta_vacia(colaP));
	print_test("Verifico que una cola recien creada no tenga datos", cola_ver_primero(colaP) == NULL);
	print_test("Verifico que no se pueda desencolar una cola vacia", cola_desencolar(colaP) == NULL);

	cola_destruir(colaP, NULL);
}

void pruebas_cola_null(){
	
	cola_t* colaP = cola_crear();
	
	print_test("Pruebo encolar el valor NULL", cola_encolar(colaP, NULL));
	print_test("Veo que el primero sea el valor NULL", cola_ver_primero(colaP) == NULL);
	print_test("Desencolo el primero elemento, tiene que tener NULL", cola_desencolar(colaP) == NULL);	
	
	cola_destruir(colaP, NULL);
}

void pruebas_cola_valores() {
	
	cola_t* colaP = cola_crear();
	
	int valor22 = 22, valor33 = 33, valor44 = 44, valor55 = 55;
		
	char cadPrueba[] = "Prueba", cadPrueba2[] = "Prueba2";

	print_test("Pruebo encolar el valor 22", cola_encolar(colaP, &valor22));
	print_test("Pruebo encolar el valor 33", cola_encolar(colaP, &valor33));
	print_test("Pruebo encolar el valor 44", cola_encolar(colaP, &valor44));
	print_test("Pruebo encolar el valor 55", cola_encolar(colaP, &valor55));
	print_test("Veo que el primero sea el valor 22", cola_ver_primero(colaP) == &valor22);
	print_test("Veo que la cola no este vacia ya que tiene datos", !cola_esta_vacia(colaP));
	print_test("Veo el primer dato, este tiene que tener el valor el 22", *((int*)cola_ver_primero(colaP)) == valor22);  
	print_test("Pruebo encolar la cadena 'Prueba'", cola_encolar(colaP, cadPrueba));
	print_test("Pruebo encolar la cadena 'Prueba2'", cola_encolar(colaP, cadPrueba2));
	print_test("Veo el primer dato, este tiene que tener el valor el 22", *((int*)cola_ver_primero(colaP)) == valor22);
	print_test("Desencolo el primero elemento, tiene que tener el valor 22", *((int*)cola_desencolar(colaP)) == valor22);
	print_test("Ahora veo el primer dato, este tiene que tener el valor el 33", *((int*)cola_ver_primero(colaP)) == valor33); 
	print_test("Desencolo el valor 33", *((int*)cola_desencolar(colaP)) == valor33);
	print_test("Desencolo el valor 44", *((int*)cola_desencolar(colaP)) == valor44);
	print_test("Desencolo el valor 55", *((int*)cola_desencolar(colaP)) == valor55);
	print_test("Desencolo el valor 'Prueba'", cola_desencolar(colaP) == cadPrueba);
	print_test("Desencolo el valor	'Prueba2'", cola_desencolar(colaP) == cadPrueba2);
	print_test("Veo que la cola este vacia", cola_esta_vacia(colaP));
	print_test("Pruebo encolar el valor 22", cola_encolar(colaP, &valor22));
	print_test("Pruebo encolar el valor 33", cola_encolar(colaP, &valor33));
	print_test("Pruebo encolar el valor 44", cola_encolar(colaP, &valor44));
	print_test("Pruebo encolar el valor 55", cola_encolar(colaP, &valor55));
	
	cola_destruir(colaP, NULL);
	print_test("Destruyo la cola.", true);
}

void pruebas_cola_condiciones_borde(){
	cola_t* colaP = cola_crear();
	
	int valor_3 = 3, valor_6 = 6,
		valor_9 = 9, valor_12 = 12;
	
	print_test("Pruebo encolar el valor 3", cola_encolar(colaP, &valor_3));
	print_test("Veo que el valor 3 sea el primero", *((int*)cola_ver_primero(colaP)) == valor_3);
	print_test("Pruebo encolar el valor 6", cola_encolar(colaP, &valor_6));
	print_test("Veo que el valor 3 sea el primero", *((int*)cola_ver_primero(colaP)) != valor_6);
	print_test("Pruebo encolar el valor 9", cola_encolar(colaP, &valor_9));
	print_test("Veo que el valor 3 sea el primero", *((int*)cola_ver_primero(colaP)) != valor_9);
	print_test("Pruebo encolar el valor 12", cola_encolar(colaP, &valor_12));
	print_test("Veo que el valor 3 sea el primero", *((int*)cola_ver_primero(colaP)) != valor_12);
	print_test("Veo que salgan en el orden esperado", *((int*)cola_desencolar(colaP)) == valor_3);
	print_test("Veo que salgan en el orden esperado", *((int*)cola_desencolar(colaP)) == valor_6);
	print_test("Veo que salgan en el orden esperado", *((int*)cola_desencolar(colaP)) == valor_9);
	print_test("Veo que salgan en el orden esperado", *((int*)cola_desencolar(colaP)) == valor_12);
	print_test("Veo que la cola este vacia", cola_esta_vacia(colaP));
	
	cola_destruir(colaP, NULL);
	print_test("Destruyo la cola.", true);
}

#define VD_TAMANIO 5

#define VD_POS_0 0
#define VD_POS_1 1
#define VD_POS_2 2
#define VD_POS_3 3
#define VD_POS_4 4

void pruebas_cola_memoria_dinamica_vd(){
	cola_t* colaP = cola_crear();
	
	vector_t* vec1 = vector_crear(VD_TAMANIO);
	vector_t* vec2 = vector_crear(VD_TAMANIO);
	
	int VALOR_5 = 5;
    int VALOR_10 = 10;
    int VALOR_15 = 15;
    int VALOR_20 = 20;
    int VALOR_25 = 25;

    vector_guardar(vec1, VD_POS_0, VALOR_5);
    vector_guardar(vec1, VD_POS_1, VALOR_10);
    vector_guardar(vec1, VD_POS_2, VALOR_15);
    vector_guardar(vec1, VD_POS_3, VALOR_20);
    vector_guardar(vec1, VD_POS_4, VALOR_25);
    
    vector_guardar(vec2, VD_POS_4, VALOR_5);
    vector_guardar(vec2, VD_POS_3, VALOR_10);
    vector_guardar(vec2, VD_POS_2, VALOR_15);
    vector_guardar(vec2, VD_POS_1, VALOR_20);
    vector_guardar(vec2, VD_POS_0, VALOR_25);
    
    int Valor_pos0_VD = 0;
    int Valor_pos1_VD = 0;
    int Valor_pos2_VD = 0;
    int Valor_pos3_VD = 0;
    int Valor_pos4_VD = 0;
    
    print_test("Encolo el Vector Dinamico 1", cola_encolar(colaP, vec1));
	print_test("Verifico que la cola NO este vacia", !cola_esta_vacia(colaP));
    print_test("Pruebo que el primero SEA el Vector Dinamico 1", (vector_t*)cola_ver_primero(colaP) == vec1);
    print_test("Vector Dinamico 1, Encolado -> Tamanio 5", vector_obtener_tamanio((vector_t*)cola_ver_primero(colaP)) == 5);

    if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_0, &Valor_pos0_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[0] = 5", Valor_pos0_VD == VALOR_5);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[0]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_1, &Valor_pos1_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[1] = 10", Valor_pos1_VD == VALOR_10);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[1]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_2, &Valor_pos2_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[2] = 15", Valor_pos2_VD == VALOR_15);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[2]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_3, &Valor_pos3_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[3] = 20", Valor_pos3_VD == VALOR_20);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[3]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_4, &Valor_pos4_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[4] = 25", Valor_pos4_VD == VALOR_25);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[4]", false);
	}

	print_test("Desencolo el Vector Dinamico 1", (vector_t*)cola_desencolar(colaP)  == vec1);
	vector_destruir(vec1);
	
	//---------------------------------------------------------------------------------
    print_test("Encolo el Vector Dinamico 1", cola_encolar(colaP, vec2));
	print_test("Verifico que la cola NO este vacia", !cola_esta_vacia(colaP));
    print_test("Pruebo que el primero SEA el Vector Dinamico 1", (vector_t*)cola_ver_primero(colaP) == vec2);
    print_test("Vector Dinamico 1, Encolado -> Tamanio 5", vector_obtener_tamanio((vector_t*)cola_ver_primero(colaP)) == 5);
    
    
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_0, &Valor_pos0_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[0] = 25", Valor_pos0_VD == VALOR_25);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[0]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_1, &Valor_pos1_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[1] = 20", Valor_pos3_VD == VALOR_20);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[1]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_2, &Valor_pos2_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[2] = 15", Valor_pos2_VD == VALOR_15);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[2]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_3, &Valor_pos3_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[3] = 10", Valor_pos3_VD == VALOR_10);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[3]", false);
	}
	
	if(vector_obtener((vector_t*)cola_ver_primero(colaP), VD_POS_4, &Valor_pos4_VD)){
		print_test("Vector Dinamico 1, Encolado -> Vec[4] = 5", Valor_pos4_VD == VALOR_5);
	}else{
		print_test("Error en el vector dinamico, al buscar Vec[4]", false);
	}
	
    //print_test("Desencolo el Vector Dinamico 2", (vector_t*)cola_desencolar(colaP)  == vec2);
    //print_test("Verifico que este vacia", cola_esta_vacia(colaP));
    
    //vector_destruir(vec2);
    
    cola_destruir(colaP, cola_vector_destruir);
    print_test("la cola fue destruida", true);
}

void pruebas_cola_volumen(size_t volumen){
	
	cola_t* colaP = cola_crear();
	bool resultado = true;
	
	for(int i = 0; i < volumen; i++){
		int* nro = malloc(sizeof(int));
		*nro = i;
		cola_encolar(colaP, nro);
	}
	
	int* dato;
	
	for(int i = 0; i < volumen; i++){
		dato = (int*)cola_desencolar(colaP);
		resultado &= (*dato == i);
		free(dato);
	}
	
	print_test("Pruebas volumen...", resultado == true);
	
	cola_destruir(colaP, NULL);
	
}

void pruebas_cola_destruir_null(){
	cola_t* colaP = cola_crear();
	bool resultado = true;
	int* valor_1 = malloc(sizeof(int));
	int* valor_2 = malloc(sizeof(int));
	int* valor_3 = malloc(sizeof(int));
	
	*valor_1 = 1;
	*valor_2 = 2;
	*valor_3 = 3;
	
	cola_destruir(colaP, NULL);
	
	resultado &= (*valor_1 == 1);
	resultado &= (*valor_2 == 2);
	resultado &= (*valor_3 == 3);
	
	print_test("Pruebas destruir null...", resultado == true);
	
}

void pruebas_cola_alumno() {
	pruebas_cola_vacia();
	pruebas_cola_null();
	pruebas_cola_valores();
	pruebas_cola_volumen(200);
	pruebas_cola_condiciones_borde();
	pruebas_cola_memoria_dinamica_vd();
	pruebas_cola_destruir_null();
}
