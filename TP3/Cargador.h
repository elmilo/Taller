#ifndef CARGADOR_H_INCLUDED
#define CARGADOR_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Documento.h"
#include "Parser.h"
#include "estructuras/Cola.h"

class Cargador {

private:
    Parser* parser;
    
    std::string GetExtension(const std::string& nombreArchivo);
    std::string GetNombreArchivo(const std::string& nombreArchivo);
    int GetCodigoExtension(const std::string& nombreArchivo);
    
public:
    Documento* abrirArchivo (std::string nombreArchivo);

};

#endif
