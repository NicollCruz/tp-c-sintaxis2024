#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error: Faltan argumentos. Uso: programa inicio fin [incremento]\n");
        return 1;
    }

    float inicio = atof(argv[1]);
    float fin = atof(argv[2]);
    float incremento = (argc == 4) ? atof(argv[3]) : 1;

    tabla(inicio, fin, incremento);

    return 0;
}
