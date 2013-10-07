#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>

//Implementar algún día si sirve para herencia

template <class T>
class NodoBase {

private:
T elemento;

protected:
void setElemento (T elemento_){
	elemento = elemento_;
}

};

#endif
