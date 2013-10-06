#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Cola.c"


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
 * 
 * Procedimiento para recorrer todo el archivo e ir cargando en la matriz.
 * Si se llega a un limite de dimension, se corta, o si se llega a recorrer
 * todo el archivo y quedan dimensiones, se resetea el file pointer
 * */
int recorrerTextoLlenarMatriz
    (const char* direccion, char** unaMatriz, int dimX, int dimY){
    FILE *fp = fopen(direccion, "r");
    //struct stat infoArchivo;

/*********************************************/
    /*if (!fp)
            return 1;

    if (stat(direccion, &infoArchivo))
            return 1;*/
    
/*********************************************/
    int i,j;
    i=j=0;
    char unChar = getc(fp);
    while (unChar!= EOF){
        unaMatriz[i][j] = unChar;
        j++;
        /*
         *Caso 1: se llega al final de la fila
         * y se resetea j
         * */
        if (j==dimY-1 && i!=dimX-1) {
            i++; 
            j=0;
        }
        /*
        *Caso 2: se completa la matriz 
        *y no se sigue leyendo
        * */
        if ((j==dimY-1) && (i==dimX-1)){
            fclose(fp);
            return 0;
        }
        
        unChar = getc(fp);
        /*
        *Caso 3: se llega al final del archivo sin 
        *haber completado la matriz
        * */
        /*if (unChar == EOF && (j<dimY-1) && (i<dimX-1)){
            rewind(fp);
            unChar = getc(fp);
        }*/
    }
    
    fclose(fp);
    return 0;
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
 * Para leer parámetros desde un archivo
 * **/
char* leerParamsArchivo(char* direccion, int* tamanio){
    unsigned int maximaLong = 128;
    unsigned int tamanioActual = 0;
    
    FILE *fp = fopen(direccion, "r");
    
    char *pLectura = malloc(maximaLong);
    tamanioActual = maximaLong;
 
    if (pLectura != NULL){
        int unChar = EOF;
        unsigned int i=0;
        //Aceptar hasta el eof
        while ((unChar = getc(fp)) != EOF){
            pLectura[i++]=(char)unChar;
            //si se alcanza el tamanio max, se realoca
            if (i == tamanioActual){
                tamanioActual = i+maximaLong;
                pLectura = realloc(pLectura, tamanioActual);
            }
        }
        pLectura[i] = '\0';
        *tamanio=i;
    }
    
    fclose(fp);
    return (pLectura);
}

/**
 * Para leer los parámetros desde la consola
 * **/
char* leerParamsConsola(int* tamanio){
    unsigned int maximaLong = 128;
    unsigned int tamanioActual = 0;
 
    char *pLectura = malloc(maximaLong);
    tamanioActual = maximaLong;
 
    if (pLectura != NULL){
        int unChar = EOF;
        unsigned int i=0;
        //Aceptar hasta el enter o eof
        while ((unChar = getchar()) != '\n' && unChar != EOF){
            pLectura[i++]=(char)unChar;
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
    /*for (int i = 0; i < dimX; i++) 
        for (int j = 0; i < dimY; j++)
            laMatriz[i][j] = 'i';*/
    return laMatriz;  
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
 * Para leer los parámetros de movimiento sobre la matriz, 
 * y sus dimensiones.
 * Se parsea con sscanf y expresiones regulares
 * */
char* parsearParams(char* entrada, int unTamanio, int *dimX, int *dimY){
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
void moverseSobreMatriz
    (char** unaMatriz, int dimX, int dimY, char* losMovimientos, Cola *laCola){
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
 * Se desencola (pop) hasta que esté vacía la estructura
 * para mostrar todos los movimientos hechos
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
char* siguienteLinea(char* entrada, int numeroDeLinea){
    char * devuelvo;
    const char *delim = "\n";
    devuelvo = strtok(entrada, delim);
    for (int i=1; i<numeroDeLinea; i++)
        devuelvo = strtok(NULL, delim);
    return devuelvo;
}

/**
 * Procedimiento para copiar en otro puntero el contenido
 * apuntado por el primero
 * */
/*char *copiarContenido(char *str){
    char *dup = malloc((strlen(str) + 1)*sizeof(char));
    dup[(strlen(str))] = '\0';
    return dup ? strcpy(dup, str) : dup;
}*/
char* copiarContenido(char *str){
    char *dup = malloc((strlen(str) + 1)*sizeof(char));
    strncpy(dup, str, strlen(str));
    //dup = '\0';
    dup[(strlen(str) + 1)] = '\0';
    return dup;
}

/**
 * Se cuentan la cantidad de lineas que tiene el archivo de entrada
 * */
int contarLineas(char* entrada){
    int cantidad = 0;
    while (*entrada!= '\0'){
        if (*entrada ==  '\n')
            cantidad++;
        entrada++;
            }
    return cantidad;
}

void ciclar(char* lineaParams, int tamanioParams, char* direccionText){
    int dimX, dimY;
    Cola laCola = crearCola();
    char* losMovimientos = 0; //movimientos: "ULRLR"...

    losMovimientos = parsearParams(lineaParams, tamanioParams, &dimX, &dimY);
    //Crear la matriz con la dimensiones leídas
    char **laMatriz = crearMatriz(dimX, dimY);
    recorrerTextoLlenarMatriz(direccionText, laMatriz, dimX, dimY);
    
    /**
    * Moverse sobre la matriz con el texto y devolver la cola con los 
    * movimientos. 
    */
    moverseSobreMatriz(laMatriz, dimX, dimY, losMovimientos, &laCola);

    desalocarMatriz(laMatriz, dimX);

    free(losMovimientos); //No se necesitan más los movimientos
    /**
    * Se muestran los movimientos la cantidad de los mismos
    * Se libera el espacio ocupado por la cola al hacer pop
    */
    mostrarMovimientos(&laCola,tamanioParams*3);
}

/*
 * Principal
 * **/
int main(int argc, char **argv){
    int tamanioParams;
    char* losParams  = 0; //Parametros de movimientos
    char* direccionTexto = argv[1];

    if (argc == 3){
        int tamanioParams = 0;
        char* direccionParam =argv[2];
        losParams = leerParamsArchivo(direccionParam, &tamanioParams);
        int cantidadLineas = contarLineas(losParams);
        for (int iteraciones=1; iteraciones<cantidadLineas; iteraciones++){
            char* originalParams = copiarContenido(losParams);
            char* lineaParams = siguienteLinea(originalParams, iteraciones);
            ciclar(lineaParams, tamanioParams, direccionTexto);
            free(originalParams);//Se desaloca la copia de parametros.
            }
        free(losParams); //No se necesita más el archivo de parámetros
    }else if (argc == 2){
        losParams = leerParamsConsola(&tamanioParams);
        ciclar(losParams, tamanioParams, direccionTexto);
        }
    return 0;
}
