#include <iostream>
#include <string>


class Parser {
private:
    ContenedorDePalabras* misPalabras;
    SacarTags* extractor;
    int codExtension;
    
    
public:
    Parser (int cod){
        misPalabras = new ContenedorDePalabras;
        codExtension = cod;
        switch (codExtension){
            case '1':
                extractor = new SacarTagsTEX();
                break;
            case '2':
                extractor = new SacarTagsHTML();
                break;
            default:
                extractor = new SacarTags();
        }
    }

    Parser(){
        codExtension = 0;
        }
    
    void procesarLinea(std::string unaLinea){
        if (extractor->esNecesario()){
            extractor->setEntrada(unaLinea);
            while (extractor->noEstaVacio()){
                std::string lineaLimpia = extractor->obtenerCadena();
                std::stringstream sin(lineaLimpia);
                std::string unaPalabra;
                //Separo los espacios
                while(getline(sin, unaPalabra, ' ') ){
                    misPalabras->agregarPalabra(this->minus(unaPalabra));
                }
        } else{
            std::stringstream sin(unaLinea);
            std::string unaPalabra;
            //Separo los espacios
            while(getline(sin, unaPalabra, ' ') ){
                misPalabras->agregarPalabra(this->minus(unaPalabra));
                }
            }
        }
    }

std::string& minus(std::string &entrada_){
    for (std::string::size_type i=0; i<entrada_.length(); ++i)
        entrada_[i] = std::tolower(entrada_[i],loc);
    return &entrada_;
}



ContenedorDePalabras* getPalabras(){
    return &misPalabras;
    }

};
