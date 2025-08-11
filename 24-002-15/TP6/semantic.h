#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

bool verificar_declaracion(char *identificador);
bool verificar_uso(char *identifier);
char* mensaje_error_semantico_no_declarado(char* text);
char* mensaje_error_semantico_ya_declarado(char* text);
char* int_to_string(int num);
char* crear_nombre_variable_temporal();

#endif
