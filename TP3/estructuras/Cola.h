#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <iostream>
#include "NodoBase.h"

template <typename T>
class Cola {

    NodoBase<T>* frente;
    NodoBase<T>* atras;
    int tamanio; // Para guardar el tamanio de la cola
    int contador;
    NodoBase<T>* iterador;

public:
Cola () {
    this->frente = NULL;
    this->atras = NULL;
    this->tamanio = 0;
}

~Cola() {
    while (!this->estaVacia()) {
        this->desencolar();
    }
}

bool estaVacia(){
    return tamanio==0;
    }

/**
 * Agregar elemento en la Cola
 */
void encolar(T elementoAgregado) {
    
    NodoBase<T>* nodoNuevo = new NodoBase<T>;
    
    nodoNuevo->setElemento(elementoAgregado);
    nodoNuevo->setSiguiente(NULL);

    if (this->frente == NULL) { // no hay frente
        this->frente = nodoNuevo;
    } else {
        this->atras->setSiguiente(nodoNuevo);
    }
    this->atras = nodoNuevo;
    this->tamanio++;
}

/**
 * Devuelve y remueve de la cola, el primer elemento
 */
T desencolar() {
    // obtener el primer elemento
    NodoBase<T>* frente = this->frente;
    T elemento = frente->getElemento();
    
    // mover puntero al siguiente elemento
    this->frente = frente->getSiguiente();
    this->tamanio--;

    // Desalocar memoria
    delete (frente);
    
    return elemento;
}

/**
 * Ver el primer elemento
 */
T obtenerFrente() {
    NodoBase<T>* frente = this->frente;
    return frente->getElemento();
}

/**
 * Mostrar los elementos en la cola
 */
void mostrar() {
    if (this->tamanio == 0){
        std::cout << "No hay nada para mostrar.\n";
    } else {
        NodoBase<T>* frente = this->frente;
        int i, tamanio = this->tamanio;
        std::cout << "Hay " << this->tamanio << " elementos para mostrar: \n";
        for (i = 0; i < tamanio; i++) {
            std::cout << frente->getElemento() << std::endl;            
            frente= frente->getSiguiente();
        }
    }
}

void resetear (){
    iterador = this->frente;
    this->contador = this->tamanio;
    }

bool tieneEnconlados(){
    return this->contador!=0;
    }
    
T obtenerIterado() {
    T devolver;
    this->contador--;
    devolver = iterador->getElemento();
    iterador = iterador->getSiguiente();
    return devolver;
}

};

#endif
