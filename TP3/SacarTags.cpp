#include "SacarTags.h"

void SacarTags::procesar(){
for(;;){
    std::string::size_type  posicionComienzo;
    posicionComienzo = entrada.find(delimInicial);
    // NO hay tags
    if(posicionComienzo == std::string::npos){
        listaDeTexto.encolar(entrada);
        break;
    }
    // Si hay tags, se las busca: 
    if(posicionComienzo != 0){
        int pc = posicionComienzo;
        listaDeTexto.encolar(entrada.substr(0, pc));
        entrada = entrada.substr(pc, entrada.size() - pc);
        posicionComienzo = 0;
    }
    //No considerar todo el texto en el tag
    std::string::size_type posicionFin;
    for(posicionFin = posicionComienzo;
        posicionFin < entrada.size() && entrada[posicionFin] != delimFinal;
        ++posicionFin){

        // El delimFinal puede aparecer 
        if(entrada[posicionFin] == '"'){
            posicionFin++;
         while(posicionFin < entrada.size() && entrada[posicionFin] != '"'){
                posicionFin++;
            }
        }
    }

    //Caso especial en donde no hay final del tag
    if(posicionFin == entrada.size()){
        entrada = entrada.substr(posicionFin, entrada.size() - posicionFin);
        break;
    } else {
        //  Agregar el tag al listado (no se usa en el TP)
        posicionFin++;
        int pc = posicionComienzo;
        int pf = posicionFin;
        listaDeTags.encolar(entrada.substr(pc, pf - pc));
        entrada = entrada.substr(pf, entrada.size() - pf);
        }
    }
}

SacarTags::SacarTags(){
        plain = true;
    }

void SacarTags::setEntrada(std::string entrada_){
    entrada = entrada_;
    this->procesar();
    }
    
std::string SacarTags::obtenerCadena(){
    return listaDeTexto.desencolar();
    }

bool SacarTags::noEstaVacio(){
    return !(listaDeTexto.estaVacia());
    }

bool SacarTags::esNecesario(){
    return !plain;
    }

void SacarTags::setDelimitadores(char comienzo, char fin){
    delimInicial = comienzo;
    delimFinal = fin;
}
    
SacarTagsTEX::SacarTagsTEX(){
        this->setDelimitadores('{','}');
        plain = false;
    }

SacarTagsHTML::SacarTagsHTML(){
        this->setDelimitadores('<','>');
        plain = false;
    }



