template <typename T>
class NodoAr: public NodoBase{

private:
    size_t altura;
    //izquierda: anterior
    //derecha: siguiente
    

public:
NodoAr(T elemento_){
    altura = 1;
    this->setElemento(elemento);
}

int factorDeBalance() {
    NodoBase<T>* izquierda = this->getAnterior();
    NodoBase<T>* derecha = this->getSiguiente();
    
    if (derecha) {
        if (izquierda) {
            return derecha->altura - izquierda->altura;
        }
    return derecha->altura;
    }
    if (izquierda) {
        return -izquierda->altura;
    }
    return 0;
}


int comparar(T rhs) {
    if (this->elemento < rhs) {
        return 1;
    }
    if (rhs < this->elemento) {
        return -1;
    }
    return 0;
}
};