#ifndef NODOBASE_H_INCLUDED
#define NODOBASE_H_INCLUDED

template <class T>
class NodoBase {
private:
    T elemento;
    NodoBase<T>* anterior;
    NodoBase<T>* siguiente;


public:
NodoBase() {
    this->anterior = NULL;
    this->siguiente = NULL;
    }

void setElemento (T elemento_){
	elemento = elemento_;
    }    

T getElemento (){
	return elemento;
    }

void setSiguiente(NodoBase<T>* unNodo){
    this->siguiente = unNodo;
    }

void setAnterior(NodoBase<T>* unNodo){
    this->anterior = unNodo;
    }

NodoBase<T>* getSiguiente(){
    return this->siguiente;
    }

NodoBase<T>* getAnterior(){
    return this->anterior;
    }

};

#endif
