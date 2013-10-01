#include <iostream>

template <typename T>
struct NodoC {
    T elemento;
    NodoC<T>* siguiente;

NodoC() {
    siguiente = 0;
    }
};

template <typename T>
class Cola {

    NodoC<T>* frente;
    NodoC<T>* atras;
    int tamanio; // Para guardar el tamanio de la cola

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
    // NodoC nuevo:
    NodoC<T>* nodoNuevo = new NodoC<T>;
    
    nodoNuevo->elemento = elementoAgregado;
    nodoNuevo->siguiente = NULL;

    if (this->frente == NULL) { // no hay frente
        this->frente = nodoNuevo;
    } else {
        this->atras->siguiente = nodoNuevo;
    }
    this->atras = nodoNuevo;
    this->tamanio++;
}

/**
 * Devuelve y remueve de la cola, el primer elemento
 */
T desencolar() {
    // obtener el primer elemento
    NodoC<T>* frente = this->frente;
    T elemento = frente->elemento;
    
    // mover puntero al siguiente elemento
    this->frente = frente->siguiente;
    this->tamanio--;

    // Desalocar memoria
    delete (frente);
    
    return elemento;
}

/**
 * Ver el primer elemento
 */
T obtenerFrente() {
    NodoC<T>* frente = this->frente;
    return frente->elemento;
}

/**
 * Mostrar los elementos en la cola
 */
void mostrarCola() {
    if (this->tamanio == 0){
        std::cout << "No hay nada para mostrar.\n";
    } else {
        NodoC<T>* frente = this->frente;
        int i, tamanio = this->tamanio;
        std::cout << "Hay " << this->tamanio << " elementos para mostrar \n";
        for (i = 0; i < tamanio; i++) {
            std::cout << frente->elemento;            
            frente= frente->siguiente;
        }
    }
}


};


/*int main(int argc, char **argv)
{
    Cola<int> esto;
    esto.encolar(5);
    esto.encolar(8);
    esto.encolar(9);
    esto.encolar(15);
    //esto.mostrarCola();
    while (!esto.estaVacia()){
        std::cout << esto.desencolar() << "\n";
        }
	return 0;
}*/
