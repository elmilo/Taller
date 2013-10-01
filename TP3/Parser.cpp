#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

#define TAGA '<'
#define TAGB '>'

void extraerTags(){ //(string entrada){
    std::size_t comienzo(0), final(0);
    std::string entrada = "<foo>1,2,3,4</foo><foo>5,6,7,8</foo><foo>9,10,11,12</foo>";
    comienzo = entrada.find(TAGA);
    final = entrada.find(TAGB);
    //std::cout << "comienzo: " << comienzo << "\n";
    //std::cout << "final: "<< final << "\n\n\n";
    std::string temp = entrada.substr (final+1,std::string::npos);
    while ((comienzo != std::string::npos) && (final!=std::string::npos)){
            //temp = entrada.substr (final+1,std::string::npos);
            comienzo = temp.find(TAGA);
                std::cout << temp << "\n";
            //std::cout << "comienzo: " << comienzo << "\n";
            final = temp.find(TAGB);
            
            //std::cout << "final: "<< final << "\n\n\n";
            temp = temp.substr (final+1,std::string::npos);
      }
    std::cout << entrada << "\n";
    //std::cout << temp << "\n";
}

int main(){
    extraerTags();
    /*std::ifstream entrada;
    entrada.open("ejemplo", std::ifstream::in);

    std::string unaLinea;
    
    while(std::getline(entrada, unaLinea)){
        
        std::istringstream iss(unaLinea);
        std::string resultado;
            
        if(std::getline(iss, resultado , '<')){
                std::cout << "un parser: " << resultado << "\n";
//                std::getline(iss, resultado, '>');
                std::string token;
                while( std::getline(iss, token, '>')){
                    while( std::getline(iss, token, ' ')){
                    std::cout << token << std::endl;
                }
                }
            
            if( resultado == "bar" ){
               std::cout << "\n acá llego\n" << std::endl;
            }
        }
    }
    entrada.close();*/
    return 0;
}
