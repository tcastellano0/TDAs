#include "hash.h"

#include <stdlib.h>
#include <string.h>

#include "GeneralHashFunctions.h"

/* ****************************************************************
 *          HASH - TOMAS MARTIN - MATIAS CASTILLO
 * ***************************************************************/
/* ****************************************************************
 *                  DEFINICION DE ESTRUCTURAS
 * ***************************************************************/
#define TAM_INICIAL 503

#define POS_NO_DEFINIDA -1

#define DISTORSION(a) ((a) + 2387)

#define AGRANDADOR_VALOR 2
#define AGRANDADOR(a) ((a) * AGRANDADOR_VALOR)

#define DIVISOR_VALOR 2
#define DIVISOR(a) ((a) / DIVISOR_VALOR)

#define VALOR_REDIMENSION 0.70

typedef enum estado {LIBRE, OCUPADO, BORRADO} estado_t;

typedef struct hash_campo{
	char* clave;
	void* valor;
	estado_t estado;
}hash_campo_t;

struct hash{
	hash_campo_t* tabla;
	size_t tam;
	size_t cant;
	hash_destruir_dato_t destruir_dato;
};

struct hash_iter{
	int actual;
	const hash_t* hash;
};

/* ****************************************************************
 *                     FUNCIONES AUXILIARES
 * ***************************************************************/

// Busca una posicion para la clave y guarda el dato en esa posicion.
bool hash_campo_guardar(hash_t *hash, const char* clave, void *dato);

// Borra el dato de la pos y lo devuelve.
void* hash_campo_borrar(hash_t *hash, size_t pos);

// Modifica un campo especifico.
void hash_campo_modificar(hash_campo_t *hash_campo, size_t pos, estado_t estado, const char* clave, void *dato);

// Busca el siguiente campo ocupado a pos. si pos es -1 busca el primero,
// devuelve la posicion o -1 si esta al final.
int hash_campo_siguiente(const hash_t* hash, int pos);

// Busca la posicion de clave y la devuelve, o devuelve -1 si no esta.
int hash_campo_buscar(const hash_t *hash, const char* clave);

// Crea un hash de un tamanio especifico
hash_t *_hash_crear(hash_destruir_dato_t destruir_dato, size_t tam);

// Redimensiona el hash a nuevo_tam.
bool hash_redimensionar(hash_t* hash, size_t nuevo_tam);

// Calcula el porcentaje ocupado, para el redimensionamiento.
float hash_porcentaje_ocupado(hash_t* hash);

/* ****************************************************************
 *                    PRIMITIVAS DEL HASH
 * ***************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	return _hash_crear(destruir_dato, TAM_INICIAL);
}

hash_t *_hash_crear(hash_destruir_dato_t destruir_dato, size_t tam){
	hash_t* hash = calloc(1, sizeof(hash_t));
	if(!hash) return NULL;
	
	hash->tabla = calloc(tam, sizeof(hash_campo_t));
	if(!hash->tabla) {
		free(hash);
		return NULL;
	}
	
	hash->tam = tam;
	hash->destruir_dato = destruir_dato;
	
	return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	int pos = hash_campo_buscar(hash, clave);
	
	if(pos != POS_NO_DEFINIDA){
		if(hash->destruir_dato) 
			hash->destruir_dato(hash->tabla[pos].valor);
		
		hash->tabla[pos].valor = dato;
		return true;
	}
	
	if(!hash_campo_guardar(hash, clave, dato))
			return false;
	
	if((hash_porcentaje_ocupado(hash)) > VALOR_REDIMENSION){
		if(!hash_redimensionar(hash, AGRANDADOR(hash->tam)))
			return false;
	}
	
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
	int pos = hash_campo_buscar(hash, clave);
	if(pos == POS_NO_DEFINIDA)
		return NULL;
	
	void* dato = hash_campo_borrar(hash, (size_t)pos);
	
	if(DIVISOR(hash->tam) >= TAM_INICIAL && hash_porcentaje_ocupado(hash) < DIVISOR(VALOR_REDIMENSION)){
		if(!hash_redimensionar(hash, DIVISOR(hash->tam)))
			return NULL;
	}
	
	return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	int pos = hash_campo_buscar(hash, clave);

	return pos == POS_NO_DEFINIDA ? NULL : hash->tabla[pos].valor;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	return hash_campo_buscar(hash, clave) != POS_NO_DEFINIDA;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

void hash_destruir(hash_t *hash){
	int pos = hash_campo_siguiente(hash, POS_NO_DEFINIDA);
	
	while(pos != POS_NO_DEFINIDA){
		void* dato = hash_campo_borrar(hash, (size_t)pos);
		
		if(hash->destruir_dato)
			hash->destruir_dato(dato);
		pos = hash_campo_siguiente(hash, pos);
	}
	
	free(hash->tabla);
	free(hash);
}


/* ****************************************************************
 *                 PRIMITIVAS DEL ITERADOR
 * ***************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if(!iter) return NULL;
	iter->actual = hash_campo_siguiente(hash, POS_NO_DEFINIDA);
	iter->hash = hash;
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
	if(iter->actual == POS_NO_DEFINIDA) 
		return false;
	iter->actual = hash_campo_siguiente(iter->hash, (int)(iter->actual));
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(iter->actual == POS_NO_DEFINIDA)
		return NULL;
	return iter->hash->tabla[iter->actual].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	return iter->actual == POS_NO_DEFINIDA;
}

void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}


/* ****************************************************************
 *         DEFINICION DE FUNCIONES AUXILIARES HASH CAMPO
 * ***************************************************************/

void hash_campo_modificar(hash_campo_t *hash_campo, size_t pos, estado_t estado, const char* clave, void *dato){
	hash_campo[pos].valor = dato;
	hash_campo[pos].estado = estado;
	
	if(clave)
		strcpy(hash_campo[pos].clave, clave);
	else
		hash_campo[pos].clave = NULL;
}

bool hash_campo_guardar(hash_t *hash, const char* clave, void *dato){
	size_t pos = RSHash(clave) % hash->tam;
	
	while(hash->tabla[pos].estado)
		pos = DISTORSION(pos) % hash->tam;
	
	hash->tabla[pos].clave = malloc((strlen(clave) + 1) * sizeof(char));
	if(!hash->tabla[pos].clave)
		return false;
	
	hash_campo_modificar(hash->tabla, pos, OCUPADO, clave, dato);
	
	hash->cant++;
	
	return true;
}

void* hash_campo_borrar(hash_t *hash, size_t pos){
	void* dato = hash->tabla[pos].valor;
	
	free(hash->tabla[pos].clave);
			
	hash_campo_modificar(hash->tabla, pos, BORRADO, NULL, NULL);
	
	hash->cant--;
	return dato;
}

int hash_campo_siguiente(const hash_t* hash, int pos){
	do 
		pos ++;
	while(pos < hash->tam && hash->tabla[pos].estado != OCUPADO);
	
	return pos < hash->tam ? pos : POS_NO_DEFINIDA;
}

int hash_campo_buscar(const hash_t *hash, const char* clave){
	size_t pos = RSHash(clave) % hash->tam;
	
	while(hash->tabla[pos].estado &&
		 (hash->tabla[pos].estado == BORRADO || 
		 (hash->tabla[pos].estado == OCUPADO && strcmp(hash->tabla[pos].clave, clave) != 0)))
			
		pos = DISTORSION(pos) % hash->tam;
		
	if(!hash->tabla[pos].estado) 
		return POS_NO_DEFINIDA;
	
	return (int)pos;
}

/* ****************************************************************
 *         DEFINICION DE FUNCIONES AUXILIARES HASH
 * ***************************************************************/

bool hash_redimensionar(hash_t* hash, size_t nuevo_tam){
	hash_t* hash_nuevo = _hash_crear(hash->destruir_dato, nuevo_tam);

	int pos = hash_campo_siguiente(hash, POS_NO_DEFINIDA);
	
	while(pos != POS_NO_DEFINIDA){
		char* clave = malloc(sizeof(char) * (strlen(hash->tabla[pos].clave) + 1));
		if(!clave)
			return false;
		
		strcpy(clave, hash->tabla[pos].clave);
		
		void* valor = hash_campo_borrar(hash, (size_t)pos);
		
		if(!hash_campo_guardar(hash_nuevo, clave, valor))
			return false;
		
		free(clave);
		pos = hash_campo_siguiente(hash, pos);
	}
	
	free(hash->tabla);
	hash->tabla = hash_nuevo->tabla;
	hash->tam = hash_nuevo->tam;
	hash->cant = hash_nuevo->cant;
	free(hash_nuevo);
	
	return true;
}

float hash_porcentaje_ocupado(hash_t* hash){
	return (float)hash->cant / (float)hash->tam;
}
