#include "Listador.h"


public:
    Listador::Listador();
    
    Listador::Listador(std::string unasDirecciones){
        std::stringstream sin(unasDirecciones);
        std::string unaDireccion;
        //Separo las comas
        while(getline(sin, unaDireccion, ',') ){
                misDirecciones.encolar(unaDireccion);
            }
        while (!misDirecciones.estaVacia()){
            Documento* addendum = abrirArchivo (misDirecciones.desencolar());
            if (addendum != NULL){
                misDocumentos.agregarDocumento(addendum);
                }
            }
        }
    
    void Listador::agregarDocumento(Documento* unDoc);

    Listador::BusquedaCompleta(std::string unasBusquedas){
        std::stringstream sin(unasDirecciones);
        std::string unaBusqueda;
        while(getline(sin, unaBusqueda) ){
                misBusquedas.encolar(unaBusqueda);
            }
        }
    

