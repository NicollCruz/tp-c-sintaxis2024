#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Symbol 
{
    char *nombre;
    struct Symbol *siguiente;
} Symbol;

Symbol *tabla_simbolos = NULL;

void insertar_simbolo(char *nombre) 
{
    if ( existe_simbolo(nombre) ) return;
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->nombre = strdup(nombre);
    symbol->siguiente = tabla_simbolos;
    tabla_simbolos = symbol;
}

int existe_simbolo(char *nombre) 
{
    Symbol *current = tabla_simbolos;
    while (current) 
    {
        if (strcmp(current->nombre, nombre) == 0) {
            return 1;
        }
        current = current->siguiente;
    }
    return 0;
}
