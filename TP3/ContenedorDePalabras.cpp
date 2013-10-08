#include "ContenedorDePalabras.h"

ContenedorDePalabras::ContenedorDePalabras();

void ContenedorDePalabras::agregarPalabra(std::string unaPalabra){
    listado.agregar(unaPalabra);
    }

bool ContenedorDePalabras::estaPalabra(std::string unaPalabra){
    return (unArbol.buscar(unaPalabra)!=0);
    }

bool ContenedorDePalabras::estaVacio(){
    return (unArbol.getCantidad()==0);
    }
}
