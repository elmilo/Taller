#include "Documento.h"

Documento::Documento(std::string a, std::string b){
    nombre = a;
    extension = b;
}
    
Documento::~Documento(){
    delete misPalabras;
    }

void Documento::setPalabras(ContenedorDePalabras* lasPalabras){
    misPalabras = lasPalabras;
    valido = true;
}

void Documento::NoValido(){
    valido = false;
}

bool Documento::tienePalabras(){
    return valido;
    }

std::string Documento::getNombreCompleto(){
    return nombre + extension;
    }

bool Documento::buscarUnaPalabra(std::string unaPalabra){
     return misPalabras->estaPalabra(unPalabra);
    }
