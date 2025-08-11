#include "semantic.h"

bool verificar_declaracion(char *identificador) {
    if (existe_simbolo(identificador)) {
        //fprintf(stdout, "Error: Variable %s ya declarada.\n", identificador);
        //exit(1);  // Detiene la ejecución si hay un error semántico
        return true;
    }
    return false;
}

bool verificar_uso(char *identifier) {
    if (!existe_simbolo(identifier)) {
        //fprintf(stdout, "Error: Variable %s no declarada.\n", identifier);
        // exit(1);
        return true;
    }
    return false;
}

char* mensaje_error_semantico_no_declarado(char* text) {
    // Asignar memoria suficiente para el mensaje completo
    char* ret = malloc(100);

    if (ret == NULL) {
        // Manejo de error si la memoria no pudo ser asignada
        return NULL;
    }

    // Copiar la cadena inicial en la memoria asignada
    strcpy(ret, "Error semantico: identificador ");

    // Concatenar las otras cadenas
    strcat(ret, text);
    strcat(ret, " NO declarado");

    return ret;
}

char* mensaje_error_semantico_ya_declarado(char* text) {
    // Asignar memoria suficiente para el mensaje completo
    char* ret = malloc(100);

    if (ret == NULL) {
        // Manejo de error si la memoria no pudo ser asignada
        return NULL;
    }

    // Copiar la cadena inicial en la memoria asignada
    strcpy(ret, "Error semantico: identificador ");

    // Concatenar las otras cadenas
    strcat(ret, text);
    strcat(ret, " ya declarado");

    return ret;
}

int number = 1;

char* int_to_string(int num) {
    char* str = (char*)malloc(12 * sizeof(char));
    sprintf(str, "%d", num);
    return str; // Retorna la cadena dinámica
}

char* crear_nombre_variable_temporal()
{
    char* numero_variable = int_to_string(number);
    number++;
    char* ret = malloc(100);
    strcpy(ret, "_Temp");
    strcat(ret,numero_variable);
    return ret;
}