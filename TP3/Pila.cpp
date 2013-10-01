#include <iostream>

template <typename T>
struct NodoP {
    T elemento;
    NodoP<T>* anterior;

NodoP() {
    anterior = 0;
    }

};

template <typename T>
class Pila {
    NodoP<T>* primero;
    NodoP<T>* ultimo;
    int tamanio; // Para guardar el tamanio de la cola

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
    // NodoP nuevo:
    NodoP<T>* nodoNuevo = new NodoP<T>;
    
    nodoNuevo->elemento = elementoAgregado;
    nodoNuevo->anterior = NULL;

    if (this->primero == NULL) { // no hay primero
        this->primero = nodoNuevo;
        this->ultimo = nodoNuevo;
    } else {
        NodoP<T>* temp = this->ultimo;
        this->ultimo = nodoNuevo;
        this->ultimo->anterior = temp;
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
    NodoP<T>* ultimo = this->ultimo;
    T elemento = ultimo->elemento;
    
    // mover puntero al anterior elemento
    this->ultimo = ultimo->anterior;
    this->tamanio--;

    // Desalocar memoria
    delete (ultimo);
    
    return elemento;
}

/**
 * Ver el primer elemento
 */
T obtenerUltimo() {
    NodoP<T>* ultimo = this->ultimo;
    return ultimo->elemento;
}

/**
 * Mostrar los elementos en la cola
 */
void mostrarCola() {
    if (this->tamanio == 0){
        std::cout << "No hay nada para mostrar.\n";
    } else {
        NodoP<T>* frente = this->frente;
        int i, tamanio = this->tamanio;
        std::cout << "Hay " << this->tamanio << " elementos para mostrar \n";
        for (i = 0; i < tamanio; i++) {
            std::cout << frente->elemento;            
            frente= frente->anterior;
        }
    }
}
};
