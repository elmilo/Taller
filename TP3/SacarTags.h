#ifndef SACARTAGS_H_INCLUDED
#define SACARTAGS_H_INCLUDED

#include "estructuras/Cola.h"
#include <string>
#include <iostream>

class SacarTags{
private:
    Cola<std::string> listaDeTags;
    Cola<std::string> listaDeTexto;
    std::string entrada;
    void procesar();

protected:
    char delimInicial;
    char delimFinal;
    bool plain;

public:
    //SacarTags(std::string entrada_);
    SacarTags();
    //~SacarTags();

    void setDelimitadores(char comienzo, char fin);
    void setEntrada(std::string entrada_);
    std::string obtenerCadena();
    bool noEstaVacio();
    bool esNecesario();
};


class SacarTagsHTML : public SacarTags{
public:
    //SacarTagsHTML(std::string entrada_);
    SacarTagsHTML();
};

class SacarTagsTEX : public SacarTags{
public:
    //SacarTagsTEX(std::string entrada_);
    SacarTagsTEX();
};

#endif
