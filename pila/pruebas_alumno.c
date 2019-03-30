#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 



void pruebas_pila_Vacia(){
	pila_t* p = pila_crear();
	
	int valor13 = 13;
	
	print_test("Una pila recien creada esta vaciada", pila_esta_vacia(p));
	
	print_test("No se puede ver el tope de una pila recien creada", pila_ver_tope(p) == NULL );
	
    print_test("No se puede desapilar sobre una pila recien creada", pila_desapilar(p) == NULL);
	
	print_test("Apilo el valor NULL en la pila recien creada", pila_apilar(p, NULL));
	
	print_test("Apilo el valor 13 en la pila recien creada", pila_apilar(p, &valor13));
	
	print_test("Desapilar el ultimo valor apilado y veo que es NULL", pila_desapilar(p) == &valor13);
	
	print_test("Desapilar el ultimo valor apilado y veo que es NULL", pila_desapilar(p) == NULL);
	
	print_test("Ahora la pila tiene que estar vacia", pila_esta_vacia(p));
	
	print_test("No se puede ver el tope de una pila vacia", pila_ver_tope(p) == NULL );
	
    print_test("No se puede desapilar sobre una pila vacia", pila_desapilar(p) == NULL);
    
    pila_destruir(p);
    print_test("Destruyo la pila", true);
}

void pruebas_pila_MeterValores() {

	pila_t* p = pila_crear();
    
	//Meto valores
	int VALOR_66 = 66;
    int VALOR_78 = 78;
    
	
	print_test("Apilo el valor 66 en la pila recien creada", pila_apilar(p, &VALOR_66));
	print_test("Apilo el valor 78 en la pila recien creada", pila_apilar(p, &VALOR_78));
	
	print_test("Pruebo que el tope NO SEA el valor 66", pila_ver_tope(p) != &VALOR_66);
	print_test("Pruebo que el tope SEA el valor 78", pila_ver_tope(p) == &VALOR_78);
	
	print_test("Desapilo y este tiene que ser el valor 78", pila_desapilar(p) == &VALOR_78);
	print_test("Pruebo que el tope NO SEA el valor 78", pila_ver_tope(p) != &VALOR_78);
	print_test("Pruebo que el tope SEA el valor 66", pila_ver_tope(p) == &VALOR_66);
	
	char Cadena[] = "PRUEBA";
    
    print_test("Apilo la cadena 'PRUEBA' en la pila recien creada", pila_apilar(p, Cadena));
    
	print_test("Pruebo que el tope NO SEA el valor 66", pila_ver_tope(p) != &VALOR_66);
	print_test("Pruebo que el tope SEA el valor 'PRUEBA'", pila_ver_tope(p) == Cadena);
	
    pila_destruir(p);
    print_test("la pila fue destruida", true);
}

void pruebas_pila_CondicionesDeBorde(){
	
	pila_t* p = pila_crear();
	

	int VALOR_45 = 45;
    int VALOR_2 = 2;
    char Cadena[] = "PRUEBA2";
    
    print_test("Apilo el valor 45 en la pila recien creada", pila_apilar(p, &VALOR_45));
	print_test("Apilo el valor 2 en la pila recien creada", pila_apilar(p, &VALOR_2));
    print_test("Apilo la cadena 'PRUEBA2' en la pila recien creada", pila_apilar(p, Cadena));
    
    print_test("Verifico que la pila NO este vacia", !pila_esta_vacia(p));
    
    printf("VACIO LA PILA \n");
    printf("--------------------------------------------- \n");
    //Desapilo
    while(!pila_esta_vacia(p)){
		pila_desapilar(p);
	}
	print_test("Verifico que la pila este vacia", pila_esta_vacia(p));
	
	
	printf("Apilo 1300 veces el valor 2 y el valor 45 \n");
	//Apilo bastante.
	for(int i = 0; i < 1299; i++){
		if (i % 2)
			pila_apilar(p, &VALOR_2);
		else
			pila_apilar(p, &VALOR_45);
	}
	
	print_test("Verifico que la pila NO este vacia", !pila_esta_vacia(p));
	print_test("Verifico que el tope de la pila sea 45", pila_ver_tope(p) == &VALOR_45);
	printf("--------------------------------------------- \n");
	
	
	
	printf("VUELVO A VACIAR LA PILA VIENDO QUE SE CUMPLA LA INTERCALACION \n");
	printf("--------------------------------------------- \n");
	
	int i = 0;
	
	while(!pila_esta_vacia(p)){
		if(i % 2){
			print_test("Desapilo el valor 2", pila_desapilar(p) == &VALOR_2);
		}else{
			print_test("Desapilo el valor 45", pila_desapilar(p) == &VALOR_45);
		}
		i++;
	}
	
	print_test("La pila quedo vaciada", pila_esta_vacia(p));
	print_test("No se puede ver el tope de una pila vacia", pila_ver_tope(p) == NULL );
    print_test("No se puede desapilar sobre una pila vacia", pila_desapilar(p) == NULL);

	printf("--------------------------------------------- \n");
	
    pila_destruir(p);
    print_test("la pila fue destruida", true);
    
}


void pruebas_pila_alumno() {
	pruebas_pila_Vacia();
	pruebas_pila_MeterValores();
	pruebas_pila_CondicionesDeBorde();
}
