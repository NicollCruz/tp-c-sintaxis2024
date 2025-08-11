#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <ctype.h> // Acá está ctype
#include <stdbool.h>

typedef enum{
    IDENTIFICADOR,
    CONSTANTE,
    PALABRARESERVADA,
    OPERADOR,
    ASIGNACION,
    CARACTER_PUNTUACION,
    ERROR_COMUN =100,
    ERROR_ASIGNACION_SOLO_DOS_PUNTOS,
    ERROR_ASIGNACION_SOLO_IGUAL,
} cod_op;


void crearTabla();

int tipoDeError(int estadoActual, char c);

bool esCaracterDeEspacio(char c);

int tipoDeCaracter(char c);

int escaner(FILE* f);

void concatenar_lexema(char c);

void devolver_al_flujo(int estadoActual, char c, FILE* f);

bool esEstadoFinal(int estadoActual);

bool esMiembro(int arr[], int tamaño, int elemento);

int funcionDeTransicion(int estadoActual, char c);