#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void prueba_lista_vacia(){
	 
	 lista_t* _lista = lista_crear();
	 
	 print_test("Verifico que una lista recien creada este vacia", lista_esta_vacia(_lista));
	 print_test("Verifico que una lista recien creada no tenga primer valor", lista_ver_primero(_lista) == NULL);
	 print_test("Verifico que una lista recien creada no tenga ultimo valor", lista_ver_ultimo(_lista) == NULL);
	 print_test("Verifico que no se pudan eliminar valores en una nueva lista", !lista_borrar_primero(_lista));
	 print_test("Verifico que una lista este vacia", lista_esta_vacia(_lista));
	 print_test("Verifico que una lista vacia no tenga primer valor", lista_ver_primero(_lista) == NULL);
	 print_test("Verifico que una lista vacia no tenga ultimo valor", lista_ver_ultimo(_lista) == NULL);
	 print_test("Verifico que no se pudan eliminar valores en una lista vacia", !lista_borrar_primero(_lista));
	 
	 lista_destruir(_lista, NULL);
	 print_test("La lista fue destruida", true);
	 
}

void prueba_lista_null(){
	lista_t* _lista = lista_crear();
	
	 print_test("Inserto el valor NULL en el principio", lista_insertar_primero(_lista, NULL));
	 print_test("Verifico que la lista no este vacia", !lista_esta_vacia(_lista));
	 print_test("Veo el ultimo valor de la lista, este tiene que ser NULL", lista_ver_ultimo(_lista) == NULL);
	 print_test("Veo el primer valor de la lista, este tiene que ser NULL", lista_ver_primero(_lista) == NULL);
	 print_test("Elimino el primer valor, tiene que darme el valor NULL", lista_borrar_primero(_lista) == NULL);
	 
	 lista_destruir(_lista, NULL);
	 print_test("La lista fue destruida", true);
}

void prueba_lista_ingreso_valores(){
	
	lista_t* _lista = lista_crear();
	 
	print_test("Verifico que una lista recien creada este vacia", lista_esta_vacia(_lista));
	print_test("Verifico que una lista recien creada no tenga primer valor", lista_ver_primero(_lista) == NULL);
	print_test("Verifico que una lista recien creada no tenga ultimo valor", lista_ver_ultimo(_lista) == NULL);
	print_test("Verifico que no se pudan eliminar valores en una nueva lista", !lista_borrar_primero(_lista));
	
	int valor22 = 22,
		valor33 = 33,
		valor44 = 44,
		valor55 = 55;
		
	char cadPrueba[] = "Prueba";
	
	print_test("Inserto en el primero el valor 22", lista_insertar_primero(_lista, &valor22));
	print_test("Inserto en el ultimo el valor 33", lista_insertar_ultimo(_lista, &valor33));
	print_test("Inserto en el primero el valor 44", lista_insertar_primero(_lista, &valor44));
	print_test("Inserto en el ultimo el valor 55", lista_insertar_ultimo(_lista, &valor55));
	print_test("Verifico que la lista no este vacia", !lista_esta_vacia(_lista));
	print_test("Veo el primer valor de la lista, este tiene que ser 44", *(int*)lista_ver_primero(_lista) == valor44);
	print_test("Veo el primer valor de la lista, este no tiene que ser 33", *(int*)lista_ver_primero(_lista) != valor33);
	print_test("Veo el primer valor de la lista, este no tiene que ser 22", *(int*)lista_ver_primero(_lista) != valor22);
	print_test("Veo el ultimo valor de la lista, este tiene que ser 55", *(int*)lista_ver_ultimo(_lista) == valor55);
	print_test("Veo el ultimo valor de la lista, este no tiene que ser 33", *(int*)lista_ver_ultimo(_lista) != valor33);
	print_test("Veo el ultimo valor de la lista, este no tiene que ser 22", *(int*)lista_ver_ultimo(_lista) != valor22);
	print_test("Elimina el primer elemento, este tenia que ser el 44", *(int*)lista_borrar_primero(_lista) == valor44);
	print_test("Inserto en el primero la cadena 'Prueba'", lista_insertar_primero(_lista, cadPrueba));
	print_test("Veo el primer valor de la lista, ahora tiene que ser la cadena 'Prueba'", lista_ver_primero(_lista) == cadPrueba);
	print_test("Elimina la cadena 'Prueba'", lista_borrar_primero(_lista) == cadPrueba);
	print_test("Veo el primer valor de la lista, este NO tiene que ser 44", *(int*)lista_ver_primero(_lista) != valor44);
	print_test("Veo el primer valor de la lista, este tiene que ser 22", *(int*)lista_ver_primero(_lista) == valor22);
	
	lista_destruir(_lista, NULL);
	print_test("La lista fue destruida", true);
	
}

void prueba_lista_volumen(size_t volumen){
	
	lista_t* _lista = lista_crear();
	bool resultado = true;
	int* dato;
	
	for(int i = 0; i < volumen; i++){
		int* nro = malloc(sizeof(int));
		*nro = i;
		resultado &= lista_insertar_primero(_lista, nro);
	}
	
	for(int i = 0; i < volumen; i++){
		dato = (int*)lista_borrar_primero(_lista);
		resultado &= (*dato == (volumen - i - 1));
		free(dato);
	}
	
	print_test("Pruebas volumen insertando elementos a lo primero...", resultado == true);
	resultado = true;
	
	for(int i = 0; i < volumen; i++){
		int* nro = malloc(sizeof(int));
		*nro = i;
		resultado &= lista_insertar_ultimo(_lista, nro);
	}
	
	for(int i = 0; i < volumen; i++){
		dato = (int*)lista_borrar_primero(_lista);
		resultado &= (*dato == i);
		free(dato);
	}
	
	print_test("Pruebas volumen insertando elementos a lo ultimo...", resultado == true);
	
	lista_destruir(_lista, NULL);
}

void pruebas_lista_destruir_null(){
	lista_t* _lista = lista_crear();
	
	bool resultado = true;
	int* valor_1 = malloc(sizeof(int));
	int* valor_2 = malloc(sizeof(int));
	int* valor_3 = malloc(sizeof(int));
	
	*valor_1 = 1;
	*valor_2 = 2;
	*valor_3 = 3;
	
	resultado &= lista_insertar_primero(_lista, valor_1);
	resultado &= lista_insertar_primero(_lista, valor_2);
	resultado &= lista_insertar_primero(_lista, valor_3);
	
	lista_destruir(_lista, NULL);
	
	resultado &= (*valor_1 == 1);
	resultado &= (*valor_2 == 2);
	resultado &= (*valor_3 == 3);
	
	free(valor_1);
	free(valor_2);
	free(valor_3);
	
	print_test("Pruebas destruir null...", resultado == true);
	
}

void pruebas_lista_destruir_free(){
	lista_t* _lista = lista_crear();
	
	bool resultado = true;
	int* valor_1 = malloc(sizeof(int));
	int* valor_2 = malloc(sizeof(int));
	int* valor_3 = malloc(sizeof(int));
	
	*valor_1 = 1;
	*valor_2 = 2;
	*valor_3 = 3;
	
	resultado &= lista_insertar_primero(_lista, valor_1);
	resultado &= lista_insertar_primero(_lista, valor_2);
	resultado &= lista_insertar_primero(_lista, valor_3);
	
	lista_destruir(_lista, free);
	
	print_test("Pruebas destruir free...", resultado == true);
	
}

void prueba_lista_iterador_externo(){
	
	lista_t* _lista = lista_crear();

	int VALOR_1 = 1;
    int VALOR_2 = 2;
    int VALOR_3 = 3;
    int VALOR_4 = 4;
    int VALOR_5 = 5;
    
    int VALOR_35 = 35;
    int VALOR_8 = 8;
    int VALOR_15 = 15;
    
    print_test("Inserto el valor 1 en la lista", lista_insertar_ultimo(_lista, &VALOR_1));
    print_test("Inserto el valor 2 en la lista", lista_insertar_ultimo(_lista, &VALOR_2));
    print_test("Inserto el valor 3 en la lista", lista_insertar_ultimo(_lista, &VALOR_3));
    print_test("Inserto el valor 4 en la lista", lista_insertar_ultimo(_lista, &VALOR_4));
    print_test("Inserto el valor 5 en la lista", lista_insertar_ultimo(_lista, &VALOR_5));
    
    print_test("Muestro que el primer valor es el valor 1", *(int*)lista_ver_primero(_lista) == VALOR_1);
    print_test("Muestro que el ultimo valor es el valor 5", *(int*)lista_ver_ultimo(_lista) == VALOR_5);
    
    print_test("La cantidad de datos en la lista es de 5", lista_largo(_lista) == 5);
    
	//----------------------------------------------------------------------------------------------
    int i = 0;
    lista_iter_t* _lista_iter = lista_iter_crear(_lista);
    
    print_test("Inserto el valor 35 al principio de la lista con el iterador", lista_iter_insertar(_lista_iter, &VALOR_35));
  
	while (!lista_iter_al_final(_lista_iter))
    {
		if(i == 2){
			print_test("Inserto el valor 15 en la posicion 2 de la lista", lista_iter_insertar(_lista_iter, &VALOR_15));
		}
		i++;
        lista_iter_avanzar(_lista_iter);
    }
    
    print_test("Inserto el valor 8 al final de la lista con el iterador", lista_iter_insertar(_lista_iter, &VALOR_8));
	
	
    print_test("Ahora la cantidad de datos en la lista es de 8", lista_largo(_lista) == 8);
    
    print_test("Muestro que el primer valor es el valor 35", *(int*)lista_ver_primero(_lista) == VALOR_35);
    print_test("Muestro que el ultimo valor es el valor 8", *(int*)lista_ver_ultimo(_lista) == VALOR_8);
    print_test("Muestro que el ultimo valor segun el iterador es el 8", *(int*)lista_iter_ver_actual(_lista_iter) == VALOR_8);
    
    lista_iter_destruir(_lista_iter);
	
	_lista_iter = lista_iter_crear(_lista);
	i = 0;
	
	printf("Verifico que se cumpla que en la Posicion 2 esta el valor 5 \n");
	while (!lista_iter_al_final(_lista_iter))
    {
		if(i == 2){
			print_test("En la posicion 2 esta el valor 15", *(int*)lista_iter_ver_actual(_lista_iter) == VALOR_15);
		}
		i++;
        lista_iter_avanzar(_lista_iter);
    }
    print_test("Muestro que el ultimo valor es el valor 8", *(int*)lista_ver_ultimo(_lista) == VALOR_8);
	lista_iter_destruir(_lista_iter);
	
	
	i = 0;
	printf("Voy a borrar los datos agregados con el iterador y regresar a la lista a su estado anterior \n");
	
	_lista_iter = lista_iter_crear(_lista);
    
	while (!lista_iter_al_final(_lista_iter))
    {
		switch(i){
			case 0:
				print_test("Borro el valor 35 en la posicion 0 de la lista con el iterador", *(int*)lista_iter_borrar(_lista_iter) == VALOR_35);
				break;
			
			case 2:
				print_test("Borro el valor 15 en la posicion 2 de la lista  con el iterador", *(int*)lista_iter_borrar(_lista_iter) == VALOR_15);
				break;
			
			case 7:
				print_test("Borro el valor 8 en la posicion 7 de la lista  con el iterador", *(int*)lista_iter_borrar(_lista_iter) == VALOR_8);
				break;
				
			default:
				lista_iter_avanzar(_lista_iter);
		};
		
		i++;
    };
    
	lista_iter_destruir(_lista_iter);	
	
	
	print_test("La cantidad de datos en la lista es de 5", lista_largo(_lista) == 5);

	lista_destruir(_lista, NULL);
    print_test("la lista fue destruida", true);

}

bool iter_sumar_numeros(void* dato, void* extra){
	
	int* int_dato = dato;
	int* int_extra = extra;
	
	if(*int_dato > 30){
		printf("El valor es > a 30, por lo tanto no se imprime \n");
		return false;
	}
	*int_extra += *int_dato;
	
	printf("Valor - %d \n", *int_dato);
	
	return true;
	
}

void prueba_lista_iterador_interno(){
	
	lista_t* _lista = lista_crear();
	
	int VALOR_2 = 2;
    int VALOR_4 = 4;
    int VALOR_6 = 6;
    int VALOR_8 = 8;
    int VALOR_10 = 10;
    int VALOR_12 = 12;
    int VALOR_14 = 14;
    int VALOR_16 = 16;
    int VALOR_18 = 18;
    int VALOR_20 = 20;
    int VALOR_22 = 22;
    int VALOR_24 = 24;
    int VALOR_26 = 26;
    int VALOR_28 = 28;
    int VALOR_30 = 30;
    int VALOR_32 = 32;
    int VALOR_34 = 34;
    int VALOR_36 = 36;
    int VALOR_38 = 38;
    int VALOR_40 = 40;
    
    int tot_suma = 0;
    
    printf("PRUEBAS CON ITERADOR INTERNO -> LISTA DE INTS\n");
	printf("---------------------------------------------------- \n");
    
    print_test("Inserto el valor 2 en la lista", lista_insertar_ultimo(_lista, &VALOR_2));
    print_test("Inserto el valor 4 en la lista", lista_insertar_ultimo(_lista, &VALOR_4));
    print_test("Inserto el valor 6 en la lista", lista_insertar_ultimo(_lista, &VALOR_6));
    print_test("Inserto el valor 8 en la lista", lista_insertar_ultimo(_lista, &VALOR_8));
    print_test("Inserto el valor 10 en la lista", lista_insertar_ultimo(_lista, &VALOR_10));
    print_test("Inserto el valor 12 en la lista", lista_insertar_ultimo(_lista, &VALOR_12));
    print_test("Inserto el valor 14 en la lista", lista_insertar_ultimo(_lista, &VALOR_14));
    print_test("Inserto el valor 16 en la lista", lista_insertar_ultimo(_lista, &VALOR_16));
    print_test("Inserto el valor 18 en la lista", lista_insertar_ultimo(_lista, &VALOR_18));
    print_test("Inserto el valor 20 en la lista", lista_insertar_ultimo(_lista, &VALOR_20));
    print_test("Inserto el valor 22 en la lista", lista_insertar_ultimo(_lista, &VALOR_22));
    print_test("Inserto el valor 24 en la lista", lista_insertar_ultimo(_lista, &VALOR_24));
    print_test("Inserto el valor 26 en la lista", lista_insertar_ultimo(_lista, &VALOR_26));
    print_test("Inserto el valor 28 en la lista", lista_insertar_ultimo(_lista, &VALOR_28));
    print_test("Inserto el valor 30 en la lista", lista_insertar_ultimo(_lista, &VALOR_30));
    print_test("Inserto el valor 32 en la lista", lista_insertar_ultimo(_lista, &VALOR_32));
    print_test("Inserto el valor 34 en la lista", lista_insertar_ultimo(_lista, &VALOR_34));
    print_test("Inserto el valor 36 en la lista", lista_insertar_ultimo(_lista, &VALOR_36));
    print_test("Inserto el valor 38 en la lista", lista_insertar_ultimo(_lista, &VALOR_38));
    print_test("Inserto el valor 40 en la lista", lista_insertar_ultimo(_lista, &VALOR_40));
	
	lista_iterar(_lista, iter_sumar_numeros, &tot_suma);
	
	
	printf("---------------------------------------------------- \n");
	lista_destruir(_lista, NULL);
	print_test("La suma total debe ser 240..", tot_suma == 240);
	print_test("la lista fue destruida", true);
	
	
}

void pruebas_lista_alumno() {
	prueba_lista_vacia();
	prueba_lista_null();
	prueba_lista_ingreso_valores();
	prueba_lista_volumen(200);
	prueba_lista_volumen(400);
	pruebas_lista_destruir_null();
	pruebas_lista_destruir_free();
	prueba_lista_iterador_externo();
	prueba_lista_iterador_interno();
}
