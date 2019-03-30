#Definicion de FLAGS
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wtype-limits -pedantic
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(NOMBRE_COMPILADO)

#Definicion de RAIZ
RAIZ = abb.c abb.h abb_test_alumno.c pila.c pila.h testing.c testing.h
RAIZ_C = abb.c abb_test_alumno.c pila.c testing.c

#Definicion de NOMBRE_COMPILADO
NOMBRE_COMPILADO = abb

#------

#COMANDOS
all:$(RAIZ)
	$(CC) $(CFLAGS) $(RAIZ_C) -o $(NOMBRE_COMPILADO)

run: all
	$(VALGRIND)



