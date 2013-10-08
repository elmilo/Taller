#ifndef DOCUMENTO_H_INCLUDED
#define DOCUMENTO_H_INCLUDED

#include <string>
#include "ContenedorDePalabras.h"


class Documento{
private:
    ContenedorDePalabras* misPalabras;
    std::string nombre;
    std::string extension;

public:
Documento(std::string a, std::string b){
    nombre = a;
    extension = b;
}
    
~Documento(){
    delete misPalabras;
    }

void setPalabras(ContenedorDePalabras* lasPalabras){
    
    }
};

#endif
