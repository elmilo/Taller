#include "ContenedorDePalabras.h"

void ContenedorDePalabras::agregarPalabra(std::string unaPalabra){
    listado.agregar(unaPalabra);
    }

bool ContenedorDePalabras::estaPalabra(std::string unaPalabra){
    return (listado.buscar(unaPalabra)!=0);
    }

bool ContenedorDePalabras::estaVacio(){
    return (listado.getCantidad()==0);
    }

