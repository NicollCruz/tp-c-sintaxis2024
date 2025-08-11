#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    IDENTIFICADOR =1,
    CONSTANTE,
    PALABRARESERVADA,
    OPERADOR,
    ASIGNACION,
    CARACTER_PUNTUACION,
    ERROR_COMUN,
    ERROR_ASIGNACION
} Token;