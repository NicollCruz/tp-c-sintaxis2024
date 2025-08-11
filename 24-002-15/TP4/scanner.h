#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum{
    IDENTIFICADOR, 
    CONSTANTE,
    SUMA,
    RESTA,
    OPERADOR,
    ASIGNACION,
    PAREN_ABRE,
    PAREN_CIERRA,
    COMA,
    PUNTOYCOMA,
    ERROR_COMUN,
    ERROR_ASIGNACION,
    FDA, //FIN DE ARCHIVO PARA MATCHEAR EN EL PARSER
    PROGRAMA,
    FIN,
    ENTERO,
    LEER,
    ESCRIBIR
} token;

extern char* lexema;

extern FILE* file;

/*
typedef struct 
{
    char* lexema;
    cod_op codigo;
} Lexema;
*/

token escaner();

void crearTabla();

bool tipoDeError(token estadoViejo, token estadoActual, char c, token* tipoError);

void verificarLexema(char* lexema, int estadoFinal, token* tipoError);

bool esCaracterDeEspacio(char c);

void aplicarAccionSegunEstado(FILE* f, int estadoActual, char);

//void mostrar_tabla_transiciones();

token tipoDeToken(int estado, token tipoDeError);

token buscar(char* lexema, char* tabla_de_palabras_reservadas[5]);

token prox_token();

void match(token tok);

char* token_to_string(token tok);

void error_sintactico(token tok);

void imprimir_mensaje_error(token token_actual);
