#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Cola.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MOVIMIENTO_INVALIDO '-'

#define CODIGOCRLF  10

#define ARRIBA      'U'
#define ABAJO       'D'
#define IZQUIERDA   'L'
#define DERECHA     'R'


typedef struct Coordenadas {
    int x;
    int y;
} Coordenadas;

/**
 * Procedimiento para abrir un archivo y cargar su contenido en salida,
 * el cual es liberado luego desde el procedimiento que se invocó
 * */
char* abrirArchivo(char* direccion, int *tamanio){
    struct stat sb;
    char *archivoEnMemoria;
    FILE *fp = fopen(direccion, "r");
    if (!fp)
        return '\0';
    if (stat(direccion, &sb))
        return '\0';
    //Alocar suficiente espacio para cargar el puntero de devolución
    archivoEnMemoria = (char *) malloc(sb.st_size);
    if (!archivoEnMemoria){
        fclose(fp);
        return '\0';
    }
    //Cargar el tamaño de lo que devuelve
    *tamanio = (int) sb.st_size;
    //Cargar el puntero de devolución
    if (fread(archivoEnMemoria, sizeof(char), sb.st_size, fp) < 1)
        fprintf(stderr, "\nError in reading or end of file.\n");
    //Cerrar el archivo
    fclose(fp);
    
    return archivoEnMemoria;
}

/**
 * Procedimientos de impresión de datos
 * **/
void imprimirCoord(Coordenadas unaCoord){
    printf("X: %d\n", unaCoord.x);
    printf("Y: %d\n", unaCoord.y);
    }

void imprimirMatriz(char** unaMatriz, int dimX, int dimY){
    printf("La matriz es: \n");
    for (int i=0; i<dimX; i++){
        for (int j=0; j<dimY; j++)
            printf("%c ",unaMatriz[i][j]);
        printf("\n");
    }
}

/**
 * Para leer desde la consola
 * **/
char* lecturaManual(int* tamanio){
    unsigned int maximaLong = 128;
    unsigned int tamanioActual = 0;
 
    char *pLectura = malloc(maximaLong);
    tamanioActual = maximaLong;
 
    if (pLectura != NULL){
    int c = EOF;
    unsigned int i=0;
    //Aceptar hasta el enter o eof
    while ((c = getchar()) != '\n' && c != EOF){
        pLectura[i++]=(char)c;
    //si se alcanza el tamanio max, se realoca
        if (i == tamanioActual){
            tamanioActual = i+maximaLong;
            pLectura = realloc(pLectura, tamanioActual);
            }
        }
    pLectura[i] = '\0';
    *tamanio=i;
    }
    
    
    return (pLectura);
}
    
/**
 * * Procedimiento para crear una nueva matriz de tamaño dinámico
 * */
char** crearMatriz(int dimX, int dimY){
    char** laMatriz;  
    laMatriz = (char**) malloc(dimX*sizeof(char*));  
    for (int i = 0; i < dimX; i++)  
        laMatriz[i] = (char*) malloc(dimY*sizeof(char));  
    return laMatriz;  
}

/**
 * * Procedimiento para llenar con texto una matriz
 * */
void llenarMatriz(char* unTexto, int tamanioTexto, char** unaMatriz, 
    int dimX, int dimY){
    int k=0;
    for (int i=0; i<dimX; i++)
        for (int j=0; j<dimY; j++){
            unaMatriz[i][j] = unTexto[k];
            k++;
            if (k==tamanioTexto-1) //En caso de tener que volver al inicio
                k=0;
            }
}

/**
 * Liberar la memoria utilizada por la matriz
 * */
void desalocarMatriz(char** unaMatriz, int dimX){
    for (int i = 0; i < dimX; i++)  
        free((void*)unaMatriz[i]); 
    free((void*)unaMatriz);
}

/**
 * Procedimiento para leer los parámetros de movimiento sobre la matriz, 
 * y sus dimensiones
 * */
char* lecturaParams(char* entrada, int unTamanio, int *dimX, int *dimY){
    char uno[3];
    char dos[3];
    char* movimientos = (char *) malloc(unTamanio);
    sscanf(entrada, "%[^X]%*c%s %s", uno, dos, movimientos);
    *dimX = atoi(uno);
    *dimY = atoi(dos);
    return movimientos;
    }

/**
* Verifica si la próximo movimiento está dentro de los posibles,
* o sea, dentro de las dimensiones de la matriz.
*/
int estaEnRango(Coordenadas unaPosicion, int dimX, int dimY){
    if ((unaPosicion.x < dimX)  && 
        (unaPosicion.y < dimY)  &&
        (unaPosicion.x >= 0)    && 
        (unaPosicion.y >= 0)    )
            return 1; //true one
    return 0; //false cero
}

/**
 * Recibe la posicion actual de la matriz y una posible
 * el cual se verifica luego si está en rango de dimensiones
 * */
void proponerMovimiento(char unMovimiento, Coordenadas posicionActual, 
    Coordenadas *posicionPosible){
    char upper = toupper(unMovimiento);
    switch (upper){
    case ARRIBA:
        (posicionActual.x)--;
        break;
    case ABAJO:
        (posicionActual.x)++;
        break;
    case IZQUIERDA:
        (posicionActual.y)--;
        break;
    case DERECHA:
        (posicionActual.y)++;
        break;
    
    default:
        posicionActual.y = -1;
        posicionActual.x = -1;
        break;
    }
    *posicionPosible= posicionActual;
    }



/**
 * Este procedimiento va cargando en la cola los movimientos hechos
 * los validos, con el codigo URLD, los invalidos, con el codigo de 
 * movimiento invalido.
 * */
void recorrerMatriz(char** unaMatriz, int dimX, int dimY, char* losMovimientos, 
    Cola *laCola){
    Coordenadas posicionActual, posicionPosible; 
    //Se inicializan en (0,0)
    posicionActual.x=0;
    posicionActual.y=0;
    
    posicionPosible = posicionActual;
    while (*losMovimientos!= '\0'){
        proponerMovimiento(*losMovimientos, posicionActual, &posicionPosible);
        if (estaEnRango(posicionPosible, dimX, dimY)){
    laCola->encolar(laCola, unaMatriz[posicionPosible.x][posicionPosible.y]);
        posicionActual = posicionPosible;
        }else{
        laCola->encolar(laCola, MOVIMIENTO_INVALIDO);
        }
    
    losMovimientos++;
    }
}

/**
 * Se desencola (pop) para mostrar todos los movimientos hechos
 * */
void mostrarMovimientos(Cola *unaCola, int tamanioEstablecido){
    char * addendum = (char *) malloc(tamanioEstablecido);
    char * comienzo = addendum;
    char propuesto;
    int validos = 0;
    //printf ("(unaCola->tamanio): %d", (unaCola->tamanio));
    int i = 0;
    while ((unaCola->tamanio)!=0){
        propuesto = unaCola->desencolar(unaCola);
        if (propuesto == MOVIMIENTO_INVALIDO){
            addendum[i] = '[';
            addendum[i+1] = 'E'; 
            addendum[i+2] = ']'; 
            i=i+3;
            }else{
                addendum[i] = propuesto;
                validos++;
                i++;
                }
        }
    addendum[i]='\0';
    
    printf("%d ", validos);
    while (*comienzo!= '\0'){
        printf("%c", *comienzo);
        comienzo++;
        }
    printf("%c", CODIGOCRLF);
    free(addendum);
    }

/**
 * Para obtener una linea cualquiera de un texto
 * */
char* siguienteLinea(char* entrada, int cantidad){
    char * devuelvo;
    const char *delim = "\n";
    devuelvo = strtok(entrada, delim);
    for (int i=1; i<cantidad; i++)
        devuelvo = strtok(NULL, delim);
    return devuelvo;
}

/**
 * Procedimiento para copiar en otro puntero el contenido
 * apuntado por el primero
 * */
char *copiarContenido(char *str){
    char *dup = malloc((strlen(str) + 1)*sizeof(char));
    dup[(strlen(str))] = '\0';
    return dup ? strcpy(dup, str) : dup;
}

/**
 * Se cuentan la cantidad de lineas que tiene el archivo de entrada
 * */
int obtenerLineas(char* entrada){
    int cantidad = 0;
    while (*entrada!= '\0'){
        if (*entrada ==  '\n')
            cantidad++;
        entrada++;
            }
    return cantidad;
}


/*
 * Principal
 * **/
int main(int argc, char **argv){
    Cola laCola = crearCola();
    
    int dimX, dimY;
    int tamanioParams;
    char* losParams  = 0; //Parametros de movimientos
    char* losMovimientos = 0; //movimientos: "ULRLR"...
    
    if (argc == 3){
        int cantidadLineas = 0;
        char* direccionParam =argv[2];
        losParams = abrirArchivo(direccionParam, &tamanioParams);
        cantidadLineas = obtenerLineas(losParams);
        
        //Se lee el archivo de texto
        char* elTexto = 0;
        int tamanioTexto;
        char* direccionText =argv[1];
        elTexto = abrirArchivo(direccionText, &tamanioTexto);
        //Fin lectura texto
        
        int iteraciones;
        for (iteraciones=1; iteraciones<cantidadLineas; iteraciones++){
            char* originalParams = copiarContenido(losParams);
            char* lineaParams = siguienteLinea(originalParams, iteraciones);
            //if (strlen(lineaParams)>3){
            losMovimientos 
                = lecturaParams(lineaParams, tamanioParams, &dimX, &dimY);
            free(originalParams);//Se desaloca la copia de parametros.
        
            //Crear la matriz con la dimensiones leídas
            char **laMatriz = crearMatriz(dimX, dimY);

            llenarMatriz(elTexto, tamanioTexto, laMatriz, dimX, dimY);
            
            /**
            * Moverse sobre la matriz con el texto y devolver la cola con los 
            * movimientos. 
            */
            recorrerMatriz(laMatriz, dimX, dimY, losMovimientos, &laCola);

            desalocarMatriz(laMatriz, dimX);

            free(losMovimientos); //No se necesitan más los movimientos

            /**
            * Se muestran los movimientos la cantidad de los mismos
            * Se libera el espacio ocupado por la cola al hacer pop
            */
            mostrarMovimientos(&laCola,tamanioParams*3);
            }
        free(elTexto); //Ya no se necesita más el texto
        free(losParams); //No se necesita más el archivo de parámetros
    }else if (argc == 2){
        losParams = lecturaManual(&tamanioParams);
        losMovimientos = lecturaParams(losParams, tamanioParams, &dimX, &dimY);
        free(losParams); //No se necesita más el archivo de parámetros
    
        //Crear la matriz con la dimensiones leídas
        char **laMatriz = crearMatriz(dimX, dimY);
        
        /**
        * Se lee el archivo de texto y se llena la matriz ya creada
        */
        char* elTexto = 0;
        int tamanioTexto;
        char* direccionText =argv[1];
        elTexto = abrirArchivo(direccionText, &tamanioTexto);
        llenarMatriz(elTexto, tamanioTexto, laMatriz, dimX, dimY);
        free(elTexto); //Ya no se necesita más el texto

        /**
        * Moverse sobre la matriz con el texto y devolver la cola con los 
        * movimientos. 
        */
        recorrerMatriz(laMatriz, dimX, dimY, losMovimientos, &laCola);

        desalocarMatriz(laMatriz, dimX);

        free(losMovimientos); //No se necesitan más los movimientos

        /**
        * Se muestran los movimientos la cantidad de los mismos
        * Se libera el espacio ocupado por la cola al hacer pop
        */
        mostrarMovimientos(&laCola,tamanioParams*3);
        }
    return 0;
}
