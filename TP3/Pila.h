#ifndef COLA_H
#define COLA_H

#include <stdio.h>
#include <stdlib.h>

#define ELTIPO char

/**
 * Nodo: guarda el elemento y apunta al siguiente 
 */
typedef struct Nodo {
    ELTIPO elemento;
    struct Nodo* siguiente;
} Nodo;

/**
 * Contiene punteros que apunta al primero y último elemento
 */
typedef struct Cola {
    Nodo* frente;
    Nodo* atras;
    
    // Añadir un elemento a la cola
    void (*encolar)(struct Cola*, ELTIPO); 
    // Sacar un elemento de la cola
    ELTIPO (*desencolar)(struct Cola*);
    // Ver el elemento del frente.
    ELTIPO (*obtenerFrente)(struct Cola*);
    // listar todos los elementos de la cola
    void (*mostrarCola)(struct Cola*);
    // Para guardar el tamanio de la cola
    int tamanio;
} Cola;

/**
 * Agregar elemento en la Cola
 */
void encolar(Cola* laCola, ELTIPO elementoAgregado);

/**
 * Devuelve y remueve de la cola, el primer elemento
 */
ELTIPO desencolar(Cola* laCola);

/**
 * Ver el primer elemento
 */
ELTIPO obtenerFrente(Cola* laCola);

/**
 * Mostrar los elementos en la cola
 */
void mostrarCola(Cola* laCola);

/**
 * Crear e inicializar la cola
 */
Cola crearCola();

#endif
