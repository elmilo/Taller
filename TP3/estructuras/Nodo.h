#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>

//HAY QUE IMPLEMENTAR

/**
 * Nodo: guarda el elemento y apunta al siguiente 
 */
typedef struct Nodo {
    ELTIPO elemento;
    struct Nodo* siguiente;
} Nodo;

#endif
