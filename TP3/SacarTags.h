#include "/estructuras/Cola.h"
#include <vector>
#include <string>
#include <iostream>

class SacarTags{
private:
    Cola<std::string> listaDeTags;
    Cola<std::string> listaDeTexto;
    std::string entrada;
    void procesar();

protected:
    char * delimInicial;
    char * delimFinal;
    bool plain;

public:
    //SacarTags(std::string entrada_);
    SacarTags();

    setEntrada(std::string entrada_);
    std::string obtenerCadena();
    bool estaVacio();
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
