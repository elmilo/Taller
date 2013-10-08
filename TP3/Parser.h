#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "ContenedorDePalabras.h"
#include "SacarTags.h"

class Parser {
private:
    ContenedorDePalabras* misPalabras;
    SacarTags* extractor;
    int codExtension;
    
    
public:
    Parser (int cod);

    Parser();
    
    void procesarLinea(std::string unaLinea);

    std::string minus(std::string &entrada_);

    ContenedorDePalabras* getPalabras();
};

#endif
