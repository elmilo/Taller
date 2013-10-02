#include "Cola.h"

/**
 * Agregar elemento en la Cola
 */
void encolar(Cola* laCola, ELTIPO elementoAgregado) {
    // Nodo nuevo:
    Nodo* nodoNuevo = (Nodo*) malloc(sizeof(Nodo));
    
    nodoNuevo->elemento = elementoAgregado;
    nodoNuevo->siguiente = NULL;

    if (laCola->frente == NULL) { // no hay frente
        laCola->frente = nodoNuevo;
    } else {
        laCola->atras->siguiente = nodoNuevo;
    }
    laCola->atras = nodoNuevo;
    laCola->tamanio++;
}

/**
 * Devuelve y remueve de la cola, el primer elemento
 */
ELTIPO desencolar(Cola* laCola) {
    // obtener el primer elemento
    Nodo* frente = laCola->frente;
    ELTIPO elemento = frente->elemento;
    
    // mover puntero al siguiente elemento
    laCola->frente = frente->siguiente;
    laCola->tamanio--;
    /*if (laCola->tamanio == 0){
        printf("el tamaño de la cola es cero\n");
        }*/
    // Desalocar memoria
    free(frente);
    
    return elemento;
}

/**
 * Ver el primer elemento
 */
ELTIPO obtenerFrente(Cola* laCola) {
    Nodo* frente = laCola->frente;
    return frente->elemento;
}

/**
 * Mostrar los elementos en la cola
 */
void mostrarCola(Cola* laCola) {
    if (laCola->tamanio == 0){
        printf("No hay nada para mostrar.\n");
    } else {
        Nodo* frente = laCola->frente;
        int i, tamanio = laCola->tamanio;
        //printf("hay %d elementos:\n", laCola->tamanio);
        for (i = 0; i < tamanio; i++) {
            printf("%c", frente->elemento);
            frente= frente->siguiente;
        }
    }
}

/**
 * Crear e inicializar la cola
 */
Cola crearCola(){
    Cola unaCola;
    unaCola.encolar = &encolar;
    unaCola.desencolar = &desencolar;
    unaCola.obtenerFrente = &obtenerFrente;
    unaCola.mostrarCola = &mostrarCola;
    unaCola.frente = NULL;
    unaCola.atras = NULL;
    unaCola.tamanio = 0;
    return unaCola;
}
