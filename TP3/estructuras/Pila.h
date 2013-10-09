#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <iostream>
#include "NodoBase.h"

template <typename T>
class Pila {
    NodoBase<T>* primero;
    NodoBase<T>* ultimo;
    int tamanio; // Para guardar el tamanio de la pila

public:

Pila () {
    this->primero = NULL;
    this->ultimo = NULL;
    this->tamanio = 0;
}

~Pila() {
    while (!this->estaVacia()) {
        this->desapilar();
    }
}

bool estaVacia(){
    return tamanio==0;
}

/**
 * Agregar elemento en la Pila
 */
void apilar(T elementoAgregado) {
    // NodoBase nuevo:
    NodoBase<T>* nodoNuevo = new NodoBase<T>;
    
    nodoNuevo->setElemento(elementoAgregado);
    nodoNuevo->setAnterior(NULL);

    if (this->primero == NULL) { // no hay primero
        this->primero = nodoNuevo;
        this->ultimo = nodoNuevo;
    } else {
        NodoBase<T>* temp = this->ultimo;
        this->ultimo = nodoNuevo;
        this->ultimo->setAnterior(temp);
    }
    this->tamanio++;
}

/**
 * Devuelve y remueve el ultimo elemento de la pila
 */
T desapilar() {
    /*if (primero == ultimo)
     {    throw std::runtime_error("Bad Pop");
     }*/
    // obtener el ultimo elemento
    NodoBase<T>* ultimo = this->ultimo;
    T elemento = ultimo->getElemento();
    
    // mover puntero al anterior elemento
    this->ultimo = ultimo->getAnterior();
    this->tamanio--;

    // Desalocar memoria
    delete (ultimo);
    
    return elemento;
}

/**
 * Ver el ultimo elemento
 */
T obtenerUltimo() {
    NodoBase<T>* ultimo = this->ultimo;
    return ultimo->getElemento();
}

/**
 * Mostrar los elementos de la pila
 */
void mostrar() {
    if (this->tamanio == 0){
        std::cout << "No hay nada para mostrar.\n";
    } else {
        NodoBase<T>* frente = this->ultimo;
        int i, tamanio = this->tamanio;
        std::cout << "Hay " << this->tamanio << " elementos para mostrar: \n";
        for (i = 0; i < tamanio; i++) {
            std::cout << frente->getElemento() << std::endl;            
            frente= frente->getAnterior();
        }
    }
}
};

#endif
