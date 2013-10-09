#ifndef DOCUMENTO_H_INCLUDED
#define DOCUMENTO_H_INCLUDED

#include <string>
#include "ContenedorDePalabras.h"


class Documento{
private:
    ContenedorDePalabras* misPalabras;
    std::string nombre;
    std::string extension;
    bool valido;

public:
Documento(std::string a, std::string b);
    
~Documento();

void setPalabras(ContenedorDePalabras* lasPalabras);

void NoValido();

std::string getNombreCompleto();

bool tienePalabras();

bool buscarUnaPalabra(std::string unaPalabra);

};

#endif
