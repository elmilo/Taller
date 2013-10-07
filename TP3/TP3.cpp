#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    int cantidadParametros, opcion;

    cantidadParametros = 0;
    while ((opcion = getopt(argc, argv, "m:d:q:")) != -1) {
        switch (opcion) {
        case 'm':
            printf("Parametro m: %s\n", optarg);
            cantidadParametros++;
            break;
        case 'd':
            printf("Parametro d: %s\n", optarg);
            cantidadParametros++;
            break;
        case 'q':
            printf("Parametro q: %s\n", optarg);
            cantidadParametros++;
        break;
        default: /* '?' */
            //fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
