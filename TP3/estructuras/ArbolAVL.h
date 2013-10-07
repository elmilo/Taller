#include "Pila.h"

template <typename T>
struct NodoAr {

NodoAr<T>* izquierda;
NodoAr<T>* derecha;
size_t altura;
T elemento;

NodoAr(T elemento_) {
    izquierda = 0;
    derecha = 0;
    altura = 1;
    elemento = elemento_;
}


int factorDeBalance() {
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


template <typename T>
class ArbolAVL {
    NodoAr<T>* raiz;
  
public:
ArbolAVL(T elemento) {
    raiz = new NodoAr<T>(elemento);
}


NodoAr<T>* agregar(T elemento) {
    return raiz = agregar(elemento, raiz);
}


NodoAr<T>* remover(T elemento) {
    return raiz = remover(elemento, raiz);
}


NodoAr<T>* buscar(T elemento) {
    return buscar(elemento, raiz);
}


~ArbolAVL() {
    Pila<NodoAr<T>*> nodos;
    nodos.apilar(raiz);
    while (!nodos.estaVacia()) {
        NodoAr<T>* nodo = nodos.obtenerUltimo();
        if (nodo->izquierda) {
            nodos.apilar(nodo->izquierda);
            nodo->izquierda = 0;
            continue;
        }
        if (nodo->derecha) {
            nodos.apilar(nodo->derecha);
            nodo->derecha = 0;
            continue;
        }
        nodos.desapilar();
        delete nodo;
    }
}
  
private:
NodoAr<T>* agregar(T elemento, NodoAr<T>* nodo) {
    if (!nodo) {
        return new NodoAr<T>(elemento);
    }
    switch(nodo->comparar(elemento)) {
        case 0:
            return nodo;
        case -1:
            nodo->izquierda = agregar(elemento, nodo->izquierda);
            break;
        case 1:
            nodo->derecha = agregar(elemento, nodo->derecha);
    }
    return balance(nodo);
}


NodoAr<T>* remover(T elemento, NodoAr<T>* nodo) {
    if (!nodo) {
        throw std::exception();
    }
    switch(nodo->comparar(elemento)) {
        case 1:
            nodo->derecha = remover(elemento, nodo->derecha);
            break;
        case -1:
            nodo->izquierda = remover(elemento, nodo->izquierda);
            break;
        case 0:
            NodoAr<T>* lhs = nodo->izquierda;
            NodoAr<T>* rhs = nodo->derecha;
            delete nodo;
            if (!rhs) {
                return lhs;
            }
            if (!lhs) {
                return rhs;
            }
            NodoAr<T>* replacing = getMin(rhs);
            replacing->izquierda = lhs;
            replacing->derecha = removerMin(rhs);
            return balance(replacing);
    }
    return balance(nodo);
}


NodoAr<T>* buscar(T elemento, NodoAr<T>* nodo) {
    if (!nodo) {
        return 0;
    }
    switch(nodo->comparar(elemento)) {
        case 0:
            return nodo;
        case -1:
            return buscar(elemento, nodo->izquierda);
        case 1:
            return buscar(elemento, nodo->derecha);
    }
    return 0;
}


NodoAr<T>* getMin(NodoAr<T>* nodo) {
    if (nodo->izquierda) {
        return getMin(nodo->izquierda);
    }
    return nodo;
}


NodoAr<T>* removerMin(NodoAr<T>* nodo) {
    if (!nodo->izquierda) {
        return nodo->derecha;
    }
    nodo->izquierda = removerMin(nodo->izquierda);
    return balance(nodo);
}


NodoAr<T>* rotarDerecha(NodoAr<T>* padre) {
    NodoAr<T>* arriba = padre->izquierda;
    padre->izquierda = arriba->derecha;
    arriba->derecha = padre;
    recalcularAltura(padre);
    recalcularAltura(arriba);
    return arriba;
}


NodoAr<T>* rotarIzquierda(NodoAr<T>* padre) {
    NodoAr<T>* arriba = padre->derecha;
    padre->derecha = arriba->izquierda;
    arriba->izquierda = padre;
    recalcularAltura(padre);
    recalcularAltura(arriba);
    return arriba;
}


NodoAr<T>* balance(NodoAr<T>* nodo) {
    recalcularAltura(nodo);
    switch(nodo->factorDeBalance()) {
        case 2:
            if (nodo->derecha->factorDeBalance() < 0) {
                nodo->derecha = rotarDerecha(nodo->derecha);
            }
            return rotarIzquierda(nodo);
        case -2:
            if (nodo->izquierda->factorDeBalance() > 0) {
                nodo->izquierda = rotarIzquierda(nodo->izquierda);
            }
            return rotarDerecha(nodo);
        default:
            return nodo;
    }
}


bool recalcularAltura(NodoAr<T>* nodo) {
    size_t alturaAntigua = nodo->altura;
    nodo->altura = 1 + max(nodo->izquierda, nodo->derecha);
    return !(alturaAntigua == nodo->altura);
}


size_t max(NodoAr<T>* lhs, NodoAr<T>* rhs) {
    if (lhs != 0) {
        if (rhs != 0) {
            return lhs->altura > rhs->altura ? lhs->altura : rhs->altura;
        }
      return lhs->altura;
    }
    if (rhs != 0) {
        return rhs->altura;
    }
    return 0;
  }
};

/*int main() {
  int a[] = {0, 115, 243, 8, 98, 34, 71};
  ArbolAVL<int> unArbol(a[0]);
  for (size_t i = 1; i < 7; ++i) {
     std::cout << "a[" << i << "] = " << a[i] << std::endl;
     std::cout << "raiz: " << unArbol.agregar(a[i])->elemento << std::endl;;
   }
  unArbol.agregar(9);
  if (unArbol.buscar(9)==0){
      std::cout <<"\n No encontrado \n";
      }
  unArbol.buscar(243);
  unArbol.remover(115);
  return 0;
}*/
