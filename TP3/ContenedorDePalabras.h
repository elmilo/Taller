#ifndef CONTENEDORDEPALABRAS_H_INCLUDED
#define CONTENEDORDEPALABRAS_H_INCLUDED

#include <iostream>
#include <string>
#include "estructuras/ArbolAVL.h"

class ContenedorDePalabras {
private:
    //Este arbol mantiene palabras únicas, no repite
    ArbolAVL<std::string> listado; 
    
public:

void agregarPalabra(std::string unaPalabra);

bool estaPalabra(std::string unaPalabra);

bool estaVacio();
};

#endif
