#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

#define CORTE_ITER_INTERNO_CLAVE "G"

void pruebas_abb_vacio(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	print_test("Prueba ABB -> Crear abb vacio", abb);
	print_test("Prueba ABB -> Cantidad de elementos es 0", abb_cantidad(abb) == 0);
	print_test("Prueba ABB -> Borrar clave ABB es NULL, no existe", !abb_borrar(abb, "ABB"));
	print_test("Prueba ABB -> Pertenece clave ABB es NULL, no existe", !abb_pertenece(abb, "ABB"));
	print_test("Prueba ABB -> Obtener clave ABB es NULL, no existe", !abb_obtener(abb, "ABB"));
	
	abb_destruir(abb);
}

void pruebas_abb_iter_vacio(){
	abb_t* abb = abb_crear(strcmp, NULL);
	abb_iter_t* abb_iter = abb_iter_in_crear(abb);
	
	print_test("Prueba ABB ITER -> Crear abb iter vacio", abb_iter);
	print_test("Prueba ABB ITER -> Abb iter esta al final", abb_iter_in_al_final(abb_iter));
	print_test("Prueba ABB ITER -> Abb iter avanzar es false", !abb_iter_in_avanzar(abb_iter));
	print_test("Prueba ABB ITER -> Abb iter actual es NULL, no existe", !abb_iter_in_ver_actual(abb_iter));
	
	abb_iter_in_destruir(abb_iter);
	abb_destruir(abb);	
}

void pruebas_abb_insertar(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char* clave1 = "20"; int valor1 = 10;
	char* clave2 = "30"; int valor2 = 15;
	char* clave3 = "40"; int valor3 = 20;
	
	print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB -> Obtener clave1 es valor1", abb_obtener(abb, clave1) == &valor1);
    print_test("Prueba ABB -> Obtener clave1 es valor1", abb_obtener(abb, clave1) == &valor1);
    print_test("Prueba ABB -> Borrar clave1, es valor1", abb_borrar(abb, clave1) == &valor1);
    print_test("Prueba ABB -> La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    
    print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB -> Obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2);
    print_test("Prueba ABB -> Obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2);
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba ABB -> Insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba ABB -> Obtener clave3 es valor3", abb_obtener(abb, clave3) == &valor3);
    print_test("Prueba ABB -> Obtener clave3 es valor3", abb_obtener(abb, clave3) == &valor3);
    print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    
    print_test("Prueba ABB -> Borrar primero clave3, es valor3", abb_borrar(abb, clave3) == &valor3);
	print_test("Prueba ABB -> Borrar despues clave2, es valor2", abb_borrar(abb, clave2) == &valor2);
	print_test("Prueba ABB -> La cantidad de elementos es 0", abb_cantidad(abb) == 0);
	
	print_test("Prueba ABB -> Pertenece clave1 ya no pertenece", !abb_pertenece(abb, clave1));
	print_test("Prueba ABB -> Pertenece clave2 ya no pertenece", !abb_pertenece(abb, clave2));
	print_test("Prueba ABB -> Pertenece clave3 ya no pertenece", !abb_pertenece(abb, clave3));
	
	print_test("Prueba ABB -> Insertar clave3 y que se destruya con el abb", abb_guardar(abb, clave3, &valor3));
	print_test("Prueba ABB -> Insertar clave2 y que se destruya con el abb", abb_guardar(abb, clave2, &valor2));
	print_test("Prueba ABB -> Insertar clave1 y que se destruya con el abb", abb_guardar(abb, clave1, &valor1));
	
	abb_destruir(abb);	
}

void pruebas_abb_reemplazar(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char* clave1 = "A"; int valor1a = 10; int valor1b = 20;
	char* clave2 = "B"; int valor2a = 15; int valor2b = 30;
	
	print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, clave1, &valor1a));
    print_test("Prueba ABB -> Obtener clave1 es valor1a", abb_obtener(abb, clave1) == &valor1a);
    print_test("Prueba ABB -> Obtener clave1 es valor1a", abb_obtener(abb, clave1) == &valor1a);
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
	print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, clave2, &valor2a));
    print_test("Prueba ABB -> Obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2a);
    print_test("Prueba ABB -> Obtener clave2 es valor2", abb_obtener(abb, clave2) == &valor2a);
    print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    
    print_test("Prueba ABB -> Insertar clave1 con valor1b", abb_guardar(abb, clave1, &valor1b));
    print_test("Prueba ABB -> Obtener clave1 es valor1b", abb_obtener(abb, clave1) == &valor1b);
	print_test("Prueba ABB -> Obtener clave1 NO es valor1a", abb_obtener(abb, clave1) != &valor1a);
	print_test("Prueba ABB -> Insertar clave2 con valor2b", abb_guardar(abb, clave2, &valor2b));
    print_test("Prueba ABB -> Obtener clave2 es valor2b", abb_obtener(abb, clave2) == &valor2b);
	print_test("Prueba ABB -> Obtener clave2 NO es valor2a", abb_obtener(abb, clave2) != &valor2a);
	print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);
	
	abb_destruir(abb);	
}

void pruebas_abb_reemplazar_con_memoria_dinamica(){
	abb_t* abb = abb_crear(strcmp, free);
	
	char* clave1 = "A", *valor1a, *valor1b;
	char* clave2 = "B", *valor2a, *valor2b;
	char* clave3 = "C", *valor3a, *valor3b;
	
	/* Pide memoria para 6 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));
    valor3a = malloc(10 * sizeof(char));
    valor3b = malloc(10 * sizeof(char));

	print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba ABB -> Obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba ABB -> Obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
	print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba ABB -> Obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba ABB -> Obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    
    print_test("Prueba ABB -> Insertar clave3", abb_guardar(abb, clave3, valor3a));
    print_test("Prueba ABB -> Obtener clave3 es valor3a", abb_obtener(abb, clave3) == valor3a);
    print_test("Prueba ABB -> Obtener clave3 es valor3a", abb_obtener(abb, clave3) == valor3a);
    print_test("Prueba ABB -> La cantidad de elementos es 3", abb_cantidad(abb) == 3);
    
    print_test("Prueba ABB -> Insertar clave1 con valor1b", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba ABB -> Obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
	print_test("Prueba ABB -> Obtener clave1 NO es valor1a", abb_obtener(abb, clave1) != valor1a);
	print_test("Prueba ABB -> Insertar clave2 con valor2b", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba ABB -> Obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
	print_test("Prueba ABB -> Obtener clave2 NO es valor2a", abb_obtener(abb, clave2) != valor2a);
	print_test("Prueba ABB -> Insertar clave3 con valor3b", abb_guardar(abb, clave3, valor3b));
    print_test("Prueba ABB -> Obtener clave3 es valor3b", abb_obtener(abb, clave3) == valor3b);
	print_test("Prueba ABB -> Obtener clave3 NO es valor3a", abb_obtener(abb, clave3) != valor3a);
	print_test("Prueba ABB -> La cantidad de elementos es 3", abb_cantidad(abb) == 3);
	
	abb_destruir(abb);

}

void pruebas_abb_borrar(){
	
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba ABB -> insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB -> insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba ABB -> insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba ABB -> Pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba ABB -> Borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba ABB -> Borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB -> Pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba ABB -> Obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba ABB -> La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba ABB -> Pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba ABB -> Borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba ABB -> Borrar clave1, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB -> Pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba ABB -> Obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba ABB -> Pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba ABB -> Borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba ABB -> Borrar clave2, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB -> Pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba ABB -> Obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba ABB -> La cantidad de elementos es 0", abb_cantidad(abb) == 0);

	abb_destruir(abb);	
}

void pruebas_abb_borrar_un_hijo(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "1", *valor1 = "1";
    char *clave2 = "2", *valor2 = "2";
    char *clave3 = "3", *valor3 = "3";
    char *clave4 = "4", *valor4 = "4";

    print_test("Prueba ABB -> insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB -> insertar clave2", abb_guardar(abb, clave2, valor2));
    
    print_test("Prueba ABB -> Borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba ABB -> Borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba ABB -> Cantidad de elementos es 0", abb_cantidad(abb) == 0);
    
    print_test("Prueba ABB -> insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB -> insertar clave2", abb_guardar(abb, clave2, valor2));
    
    print_test("Prueba ABB -> Borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba ABB -> Borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba ABB -> Cantidad de elementos es 0", abb_cantidad(abb) == 0);
    
    print_test("Prueba ABB -> insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB -> insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba ABB -> insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba ABB -> insertar clave4", abb_guardar(abb, clave4, valor4));
    
    print_test("Prueba ABB -> Borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba ABB -> Borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba ABB -> Borrar clave4, es valor4", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba ABB -> Borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    
    print_test("Prueba ABB -> Cantidad de elementos es 0", abb_cantidad(abb) == 0);
    
    abb_destruir(abb);
}

void pruebas_abb_borrar_dos_hijos(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *clave1 = "1", *valor1 = "1";
    char *clave2 = "2", *valor2 = "2";
    char *clave3 = "3", *valor3 = "3";
    char *clave4 = "4", *valor4 = "4";
    char *clave5 = "5", *valor5 = "5";
    
	print_test("Prueba ABB -> insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba ABB -> insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba ABB -> insertar clave4", abb_guardar(abb, clave4, valor4));

	print_test("Prueba ABB -> Borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
	print_test("Prueba ABB -> Cantidad de elementos es 2", abb_cantidad(abb) == 2);
   
    print_test("Prueba ABB -> insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba ABB -> Cantidad de elementos es 3", abb_cantidad(abb) == 3);
    
    print_test("Prueba ABB -> Borrar clave4, es valor4", abb_borrar(abb, clave4) == valor4);
    
    print_test("Prueba ABB -> insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB -> insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba ABB -> Cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba ABB -> Borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    
    print_test("Prueba ABB -> insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba ABB -> Cantidad de elementos es 4", abb_cantidad(abb) == 4);
    
    print_test("Prueba ABB -> Borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba ABB -> Cantidad de elementos es 3", abb_cantidad(abb) == 3);
    
    
    abb_destruir(abb);
}

void pruebas_abb_clave_vacia()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba ABB -> Insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB -> Obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba ABB -> Pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba ABB -> Borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba ABB -> La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void pruebas_abb_valor_null()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    print_test("Prueba ABB -> Insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba ABB -> La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB -> Obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba ABB -> Pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba ABB -> Borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba ABB -> La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void pruebas_abb_volumen(size_t largo, bool debug)
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba ABB -> almacenar muchos elementos", ok);
    if (debug) print_test("Prueba ABB -> la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba ABB -> pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba ABB -> la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba ABB -> borrar muchos elementos", ok);
    if (debug) print_test("Prueba ABB -> la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);
    abb_destruir(abb);

}


void pruebas_abb_iter_iterar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"C", "B", "A", "D", "E"};
    char *valores[] = {"20", "25", "67", "34", "90"};

    print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba ABB -> Insertar clave3", abb_guardar(abb, claves[2], valores[2]));
    print_test("Prueba ABB -> Insertar clave4", abb_guardar(abb, claves[3], valores[3]));
    print_test("Prueba ABB -> Insertar clave5", abb_guardar(abb, claves[4], valores[4]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    
    print_test("Prueba ABB -> iterador esta al final, es false", !abb_iter_in_al_final(iter));

	print_test("Prueba ABB -> iterador ver actual, es una clave valida", abb_iter_in_ver_actual(iter));
	print_test("Prueba ABB -> iterador ver actual, es la clave mas chica", strcmp((char*)abb_iter_in_ver_actual(iter), claves[2]) == 0);
	print_test("Prueba ABB -> iterador avanzar, es true", abb_iter_in_avanzar(iter));
	print_test("Prueba ABB -> iterador ver actual, es la clave mas chica", strcmp((char*)abb_iter_in_ver_actual(iter), claves[1])  == 0);
    print_test("Prueba ABB -> iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba ABB -> iterador avanzar, es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB -> iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba ABB -> iterador avanzar, es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB -> iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba ABB -> iterador avanzar, es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB -> iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba ABB -> iterador avanzar, es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB -> iterador esta al final, es true", abb_iter_in_al_final(iter));
    print_test("Prueba ABB -> iterador avanzar, es false", !abb_iter_in_avanzar(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    
    
}

void pruebas_abb_iter_in_order(){

	abb_t* abb = abb_crear(strcmp, NULL);
	char *claves[] = {"C", "B", "A", "D", "F", "J", "E", "X", "W"};
    char *valores[] = {"CV", "BV", "AV", "DV", "FV", "JV", "EV", "XV", "WV"};
	
	char *claves_ordenadas[] = {"A", "B", "C", "D", "E", "F", "J", "W", "X"};
	
	print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba ABB -> Insertar clave3", abb_guardar(abb, claves[2], valores[2]));
    print_test("Prueba ABB -> Insertar clave4", abb_guardar(abb, claves[3], valores[3]));
    print_test("Prueba ABB -> Insertar clave5", abb_guardar(abb, claves[4], valores[4]));
    print_test("Prueba ABB -> Insertar clave6", abb_guardar(abb, claves[5], valores[5]));
    print_test("Prueba ABB -> Insertar clave7", abb_guardar(abb, claves[6], valores[6]));
    print_test("Prueba ABB -> Insertar clave8", abb_guardar(abb, claves[7], valores[7]));
    print_test("Prueba ABB -> Insertar clave9", abb_guardar(abb, claves[8], valores[8]));
    
    abb_iter_t* iter = abb_iter_in_crear(abb);
    
    bool resultado = true;
    size_t index = 0;
    
    while(!abb_iter_in_al_final(iter)){
		resultado &= (strcmp(claves_ordenadas[index], (char*)abb_iter_in_ver_actual(iter)) == 0);
		abb_iter_in_avanzar(iter);
		index++;
	}
    
    print_test("Prueba ABB -> Ordeno las claves bien", resultado);
    
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
	
}

//Cambiar CORTE_ITER_INTERNO_CLAVE para distintos resultados.

bool iter_interno_imprimir_valores(const char *clave, void *dato, void* extra){
	if(strcmp(clave, CORTE_ITER_INTERNO_CLAVE) > 0){
		return false;
	}
	
	char* copia_clave = malloc(sizeof(char) * (strlen(clave) + 1));
	if(!copia_clave) 
		return NULL;
	
	strcpy(copia_clave, clave);
	extra = copia_clave;
	
	printf("VISITADO: %s - DATO: %s \n", (char*)extra, (char*)dato);
	
	free(copia_clave);
	
	return true;
}

void pruebas_abb_iter_interno(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char *claves[] = {"C", "B", "A", "D", "F", "J", "E", "X", "W"};
    char *valores[] = {"5", "6", "10", "2", "4", "20", "1", "7", "9"};
	
	print_test("Prueba ABB -> Insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba ABB -> Insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba ABB -> Insertar clave3", abb_guardar(abb, claves[2], valores[2]));
    print_test("Prueba ABB -> Insertar clave4", abb_guardar(abb, claves[3], valores[3]));
    print_test("Prueba ABB -> Insertar clave5", abb_guardar(abb, claves[4], valores[4]));
    print_test("Prueba ABB -> Insertar clave6", abb_guardar(abb, claves[5], valores[5]));
    print_test("Prueba ABB -> Insertar clave7", abb_guardar(abb, claves[6], valores[6]));
    print_test("Prueba ABB -> Insertar clave8", abb_guardar(abb, claves[7], valores[7]));
    print_test("Prueba ABB -> Insertar clave9", abb_guardar(abb, claves[8], valores[8]));
	
	char* ultimo_visitado = "";
	
	abb_in_order(abb, iter_interno_imprimir_valores, ultimo_visitado);
	
	print_test("El ultimo visitado, debe ser menor al corte", strcmp(ultimo_visitado, CORTE_ITER_INTERNO_CLAVE) <= 0);
	
	abb_destruir(abb);
}

void pruebas_abb_alumno() {
	pruebas_abb_vacio();
	pruebas_abb_iter_vacio();
	pruebas_abb_insertar();
	pruebas_abb_reemplazar();
	pruebas_abb_reemplazar_con_memoria_dinamica();
	pruebas_abb_borrar();
	pruebas_abb_borrar_un_hijo();
	pruebas_abb_borrar_dos_hijos();
	pruebas_abb_clave_vacia();
	pruebas_abb_valor_null();
	pruebas_abb_volumen(100, true);
	pruebas_abb_iter_iterar();
	pruebas_abb_iter_in_order();
	pruebas_abb_iter_interno();
}



