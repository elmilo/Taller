#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CODIDOCR 10

#define maxMatriz 60
#define VIVO 1
#define MUERTO 0
#define IMPRIMIRVIVO printf("1")
#define IMPRIMIRMUERTO printf("0")


/**
 * Bitfield: estructura para almacenar celdas de la matriz del juego de la vida
 * */
typedef struct paraLaMatriz{
  unsigned estado : 1; //1 bit para guardar si está la celda está viva o muerta
  unsigned vecinos : 3; //3 bits para contar cuántos vecinos  tiene la celda
} tipoCelda;


/*
 * Para la frontera de la matriz se necesita invertir las coordenadas con 
 * esta función
 * */
int InvertirDimension(int unaDimension, int tamanio){
    if (unaDimension < 0){
        return tamanio + unaDimension;
        }
    
    if (unaDimension >= tamanio){
        return unaDimension - tamanio;
        }

    return unaDimension;
}

/*
 * Obtiene la cantidad de vecinos vivos de una celda
 * **/
int ContarVecinos 
(tipoCelda matriz[maxMatriz][maxMatriz], int x, int y, int tamanio){
    int vecinos = 0; 
    
    int i, j;
    
    for (i= x-1; i< x+2; i++)
        for (j= y-1; j< y+2; j++){
            if (( i == x) && (j == y)) continue; 
            //No hace nada cuando son iguales
                else 
                    {//Suma vecinos en caso que se cumpla la condicióm
                    int dim1, dim2;
                    dim1 = InvertirDimension(i,tamanio);
                    dim2 = InvertirDimension(j,tamanio);
                    if (matriz[dim1][dim2].estado == VIVO) {
                        vecinos++;
                    }
                }
            }

    return vecinos;
}

/*
 * Procedimiento principal del juego: detecta los casos en que las celdas deben
 * morir o vivir.
 * **/
void EstablecerEstado(tipoCelda *unaCelda){
    //Caso 1: la celda sigue viviendo
if ((unaCelda->estado == VIVO) && 
        ((unaCelda->vecinos == 2) || (unaCelda->vecinos == 3))){
    unaCelda->estado = VIVO;
        } else if ((unaCelda->estado == MUERTO) && (unaCelda->vecinos == 3)){
    //Caso 2: la celda nace
        unaCelda->estado = VIVO;
    } else if (unaCelda->estado == VIVO){
            if ((unaCelda->vecinos == 0) || (unaCelda->vecinos == 1)){
    //Caso 3: la celda muere por sobrepoblacion, soledad o porque no hay lugar
        unaCelda->estado = MUERTO;
        } else if ((unaCelda->vecinos > 3) && (unaCelda->vecinos <=8)) {
            unaCelda->estado = MUERTO;}
     } else if ((unaCelda->estado == MUERTO) && ((unaCelda->vecinos >=0) && 
            (unaCelda->vecinos <= 8))){
         unaCelda->estado = MUERTO;
         }
}

/*
 * Se llama a los 2 procedimientos anteriores para generar el siguiente
 * estadío del juego.
 * **/
void IterarMatriz(tipoCelda matriz[maxMatriz][maxMatriz], int tamanio){
    int i,j;
    for (i = 0; i < tamanio; i++)
        for (j = 0; j < tamanio; j++){
            matriz[i][j].vecinos = ContarVecinos(matriz, i, j, tamanio);
        }
    for (i = 0; i < tamanio; i++)
        for (j = 0; j < tamanio; j++){
            EstablecerEstado(&matriz[i][j]);
        }
}

/*
 * Se imprime una celda, la forma de impresión se puede modificar desde las 
 * constantes en #define
 * ***/
void ImprimirCelda(tipoCelda unaCelda){
    switch (unaCelda.estado){
        case MUERTO:
            IMPRIMIRMUERTO;
            break;
        
        case VIVO:
            IMPRIMIRVIVO;
            break;
    }
}

/*
 * Se llama al anterior
 * ***/
void ImprimirMatriz(tipoCelda matriz[maxMatriz][maxMatriz], int tamanio){
    int i,j;
    for (i=0; i<tamanio; i++){
        for (j=0; j<tamanio; j++){
            ImprimirCelda(matriz[i][j]);
            if (i== tamanio-1 && j == tamanio -1) continue;
            else
                printf(",");
            }
        }
        printf("%c", CODIDOCR); //Imprime el CR
}

/*
 * Procedimiento que se utiliza para dejar en con estados válido las celdas de
 * la matriz del juego.
  * ***/
void EscribirCelda(tipoCelda *unaCelda, char unValor){
    switch (unValor){
        case '0':
            unaCelda->estado = MUERTO;
            break;
        
        case '1':
            unaCelda->estado = VIVO;
            break;
        
        default:
            unaCelda->estado = MUERTO;
            break;
    }
}

/*
 * Para leer desde la consola de la forma 0,1,0,1,1,1,0,0,0
 * **/
void LecturaMatrizManual(tipoCelda matriz[maxMatriz][maxMatriz], int tamanio){
    int i,j;
    i=j=0;
    char unChar = getchar();
    while (unChar != '\n' && unChar!= EOF){
        if (unChar != ','){
            EscribirCelda(&matriz[i][j],unChar);
            j++;
            }
        
        if (j==tamanio) {i++; j=0;
        }

    unChar = getchar();
    }
}

void func(char (*lectura)(int));//Puntero a función
//http://math.hws.edu/bridgeman/courses/331/f05/handouts/c-c++-notes.html

/*
 * 
 * Abrir y tratar un archivo de texto, leyéndolo carácter a carácter.
 * Si no existe se devuelve un código de error 1.
 * En caso contrario, hay éxito.
 * **/
int LecturaMatrizDesdeArchivo 
(const char* direccion, tipoCelda conway[maxMatriz][maxMatriz], int tamanio){
    FILE *fp = fopen(direccion, "r");
    struct stat infoArchivo;

/*********************************************/
    if (!fp)
            return 1;

    if (stat(direccion, &infoArchivo))
            return 1;
    
/*********************************************/
   char unChar = getc(fp);

   int i,j;
   i=j=0;
   
   while (unChar != '\n' && unChar!= EOF){
        if (unChar != ','){
            EscribirCelda(&conway[i][j],unChar);
            j++;
            }
        if (j==tamanio) {
            i++; 
            j=0;
            }
        unChar = getc(fp);
        }
    fclose(fp);
    return 0;
}


/*
 * Se lo llama en cada iteración para hacer los movimientos correspondientes
 * Imprime el siguiente estado del juego
 * **/
void GenerarIteraciones 
(int generacion, tipoCelda matriz[maxMatriz][maxMatriz], int tamanio){
    IterarMatriz(matriz,tamanio);
    ImprimirMatriz(matriz,tamanio);
}


/*
 * Principal
 * **/
int main(int argc, char **argv){
/**
 * ./tp N K estadoInicial
 * N= tamanioMatriz
 * K= cantidadIteraciones
 * estadoInicial (direccion del archivo)
 * */

    tipoCelda matriz[maxMatriz][maxMatriz]; //matriz
    
    int contador;
    int tamanioMatriz;
    int cantidadIteraciones;
    char* estadoInicial;

    if ((argc <= 2) || (argc > 4)){
        return 1;
        } else if (argc ==4) {
            tamanioMatriz = atoi(argv[1]);
            cantidadIteraciones = atoi(argv[2]);
            estadoInicial = argv[3];
            } else if (argc ==3){
                tamanioMatriz = atoi(argv[1]);
                cantidadIteraciones = atoi(argv[2]);
                LecturaMatrizManual(matriz,tamanioMatriz);
                }

    if ((argc == 4) && 
        (LecturaMatrizDesdeArchivo(estadoInicial,matriz,tamanioMatriz)==1)){
        return 2;
    }
    ImprimirMatriz(matriz,tamanioMatriz);
    for (contador = 1; contador <= cantidadIteraciones; contador++){
        GenerarIteraciones(contador, matriz, tamanioMatriz);
    }

    return 0;
}
