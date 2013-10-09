#include <iostream>
#include "Cola.h"
#include "Pila.h"

int main(int argc, char **argv){
    Cola<int> cola;
    
    cola.encolar(4);
    cola.encolar(5);
    cola.encolar(30);
    cola.encolar(-1);
    
    //cola.mostrar();
    
    /*Pila<int> pila;
    
    pila.apilar(4);
    pila.apilar(5);
    pila.apilar(30);
    pila.apilar(-1);
    
    pila.mostrar();*/
    
    std::cout << "Primer intento: " << std::endl;
    
    cola.resetear();
    while (cola.tieneEnconlados()){
        std::cout << cola.obtenerIterado() << std::endl;
        }
	
    std::cout << "Otra línea: " << std::endl;
        
    cola.resetear();
    while (cola.tieneEnconlados()){
        std::cout << cola.obtenerIterado() << std::endl;
        }
        
	return 0;
}

