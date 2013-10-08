#ifndef LISTADOR_H_INCLUDED
#define LISTADOR_H_INCLUDED

#include "estructuras/Cola.h"
#include "Documento.h"
#include "Cargador.h"
#include <iostream>
#include <string>
#include <sstream>

class Listador {
private:
    Cola<Documentos*> misDocumentos;
    Cola<std::string> misDirecciones;
    Cola<std::string> misBusquedas;

public:
    Listador();
    
    Listador(std::string unasDirecciones);
    
    void agregarDocumento(Documento* unDoc);
    
    void procesarLinea(std::string unaLinea);
};

#endif
