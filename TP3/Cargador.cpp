#include "Cargador.h"

std::string Cargador::GetExtension(const std::string& nombreArchivo){
    if(nombreArchivo.find_last_of(".") != std::string::npos)
        return nombreArchivo.substr(nombreArchivo.find_last_of(".")+1);
    return "";
}

int Cargador::GetCodigoExtension(const std::string& nombreArchivo){
    if(nombreArchivo.find_last_of(".") != std::string::npos){
        std::string c;
        c = nombreArchivo.substr(nombreArchivo.find_last_of(".")+1);
        if (c=="tex")
            return 2;
        else if (c=="html")
            return 1;
        else if (c=="txt")
            return 0;
    }
    return 0;
}

std::string Cargador::GetNombreArchivo(const std::string& nombreArchivo){
    if(nombreArchivo.find_last_of(".") != std::string::npos)
        return nombreArchivo.substr(0,nombreArchivo.find_last_of("."));
    return "";
}

Documento* Cargador::abrirArchivo (std::string nombreArchivo){
    std::string unaLinea;
    std::ifstream archivo;
    archivo.open(nombreArchivo.c_str(), std::ifstream::in);
    
    std::transform(nombreArchivo.begin(),
            nombreArchivo.end(), nombreArchivo.begin(), (int(*)(int)) tolower);
    
    std::string nom =this->GetNombreArchivo(nombreArchivo);
    std::string ext =this->GetExtension(nombreArchivo);
    
    Documento* devolver = new Documento(nom, ext);
    
    parser = new Parser(this->GetCodigoExtension(nombreArchivo));

    if (archivo.is_open()){
        std::string unaLinea;
        while(getline(archivo, unaLinea)) {
            parser->procesarLinea(unaLinea);
        }
        devolver->setPalabras(parser->getPalabras());
        archivo.close();
        delete parser;
        return devolver;
    } else {
        delete devolver;
        delete parser;
        return NULL;
        }

}
