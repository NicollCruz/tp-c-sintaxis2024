%define parse.error verbose%{
#define YYERROR_VERBOSE
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"  // Este es el archivo de tokens generado por Flex


// Declaraciones para las funciones de manejo de errores y escaneo
void yyerror(const char *s);
int yylex();

%}

%defines "parser.h"
%output "parser.c"

%token IDENTIFICADOR CONSTANTE PALABRARESERVADA OPERADOR ASIGNACION CARACTER_PUNTUACION
%token ENTERO LEER ESCRIBIR FIN_PROG PROGRAMA 
%token PARENTESIS_ABRIR PARENTESIS_CERRAR COMA PUNTO_COMA

// Precedencia de operadores
%left ADD SUB
%left MUL DIV MOD
%right NEG           //precedence NEG

%%

programa:
    PROGRAMA IDENTIFICADOR {
        printf("Programa: %s\n", yytext);
    } listaSentencias FIN_PROG
    | error '\n'
    ;

listaSentencias:
      sentencia
    | listaSentencias sentencia
    | error '\n'
    ;

sentencia:
      ENTERO IDENTIFICADOR {
          printf("Sentencia declaracion: %s\n", yytext);
      } PUNTO_COMA
      
    | IDENTIFICADOR ASIGNACION expresion PUNTO_COMA
      {
          printf("Sentencia asignacion\n");
      }
    | LEER PARENTESIS_ABRIR
      {
          //printf("Abre parentesis\n");
      } listaIdentificadores PARENTESIS_CERRAR {
          //printf("Cierra parentesis\n");
      } PUNTO_COMA
      {
          printf("Sentencia de leer. \n");
      }
    | ESCRIBIR PARENTESIS_ABRIR {
          //printf("Abre parentesis\n");
      } listaExpresiones PARENTESIS_CERRAR {
          //printf("Cierra parentesis\n");
      } PUNTO_COMA
      {
          printf("Sentencia de escribir \n");
      }
    | error PUNTO_COMA
    ;

listaIdentificadores:
      IDENTIFICADOR
    | listaIdentificadores COMA IDENTIFICADOR
    ;

listaExpresiones:
      expresion
    | listaExpresiones COMA expresion
    ;

expresion:
     SUB expresion %prec NEG  {
        printf("Inversion\n");
      }
    | expresion ADD expresion {
        printf("Suma\n");
      }
    | expresion SUB expresion {
        printf("Resta\n");
      }
    | expresion MUL expresion {
        printf("Multiplicacion\n");
      }
    | expresion DIV expresion {
        printf("Division\n");
      }
    | expresion MOD expresion {
        printf("Modulo\n");
      }
    | IDENTIFICADOR
    | CONSTANTE
    | PARENTESIS_ABRIR { printf("Abre parentesis.\n"); } expresion PARENTESIS_CERRAR { printf("Cierra parentesis.\n"); }
    ;


%%

void yyerror(const char *s) {

    fprintf(stderr,"Linea #%d: Error: %s\n",yylineno, s);  //error sintáctico
}
