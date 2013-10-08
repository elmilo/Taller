#ifndef CARGADOR_H_INCLUDED
#define CARGADOR_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "/estructuras/Cola.h"

class Cargador {

private:
    Parser* parser;
public:
    void abrirArchivo (std::string nombreArchivo);
    
    std::string GetExtension(const std::string& nombreArchivo);
    std::string GetNombreArchivo(const std::string& nombreArchivo);
    std::string GetCodigoExtension(const std::string& nombreArchivo);
};

#endif
