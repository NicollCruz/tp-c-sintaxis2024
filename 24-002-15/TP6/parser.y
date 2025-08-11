%define parse.error verbose%{
#define YYERROR_VERBOSE
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"  // Este es el archivo de tokens generado por Flex
#include "semantic.h"
#include "symbol.h"

// Declaraciones para las funciones de manejo de errores y escaneo
void yyerror(const char *s);
int yylex();
FILE *output;  // Archivo de salida 
int errores_semanticos = 0;
int es_escritura = 1; // Nos sirve para ver si nos encontramos en el caso de escritura
char* expresion_actual;
char* identificador_actual;

%}

%defines "parser.h"
%output "parser.c"

%token IDENTIFICADOR CONSTANTE PALABRARESERVADA OPERADOR ASIGNACION CARACTER_PUNTUACION
%token ENTERO LEER ESCRIBIR FIN_PROG PROGRAMA 
%token PARENTESIS_ABRIR PARENTESIS_CERRAR COMA PUNTO_COMA

%union {
    char* str; // Para manejar cadenas de texto
    int num;   // Si necesitas manejar enteros directamente
}
%type <str> expresion IDENTIFICADOR CONSTANTE

// Precedencia de operadores
%left ADD SUB
%left MUL DIV MOD
%right NEG           //precedence NEG

%%

programa:
    PROGRAMA IDENTIFICADOR {
        //printf("Programa: %s\n", yytext);
        fprintf(output, "#include <stdio.h>\n\n");
        fprintf(output, "int main() { \n");
    } listaSentencias FIN_PROG
    {
        fprintf(output, "\treturn 0;\n");
        fprintf(output, "}\n");
    }
    | error '\n'
    ;

listaSentencias:
      sentencia
    | listaSentencias sentencia
    | error '\n'
    ;

sentencia:
      ENTERO IDENTIFICADOR {
          //printf("Sentencia declaracion: %s\n", yytext);
          if( verificar_declaracion(yytext) )
          {
            errores_semanticos++;
            char* texto_error = mensaje_error_semantico_ya_declarado(yytext);
            yyerror(texto_error);
          }
          else
          {
            insertar_simbolo(yytext);
            //printf("--SEMANTICA--// El simbolo fue insertado al diccionario\n");
            fprintf(output, "\tint %s;\n", yytext); //declaracion de variable en c
          }
      } PUNTO_COMA
      
    | IDENTIFICADOR
      {
        if( verificar_uso(yytext))
        {
            errores_semanticos++;
            char* texto_error = mensaje_error_semantico_no_declarado(yytext);
            yyerror(texto_error);
        }
        identificador_actual = malloc(100);
        strcpy(identificador_actual,yytext);
        //printf("--SEMANTICA--// El simbolo existe en el diccionario\n");
      } 
      ASIGNACION expresion PUNTO_COMA
      {
          //printf("Sentencia asignacion\n");
           fprintf(output, "\t%s = %s;\n", identificador_actual,expresion_actual);
      }
    | LEER PARENTESIS_ABRIR
      {
          //printf("Abre parentesis\n");
      } listaIdentificadores PARENTESIS_CERRAR {
          //printf("Cierra parentesis\n");
      } PUNTO_COMA
      {
          //printf("Sentencia de leer. \n");
      }
    | ESCRIBIR PARENTESIS_ABRIR {
          //printf("Abre parentesis\n");
          es_escritura = 0;
      } listaExpresiones PARENTESIS_CERRAR {
          //printf("Cierra parentesis\n");
      } PUNTO_COMA
      {
          //printf("Sentencia de escribir \n");
          es_escritura = 1;
      }
    | error PUNTO_COMA
    ;

listaIdentificadores:
      IDENTIFICADOR
      {
        if( verificar_uso(yytext))
        {
            errores_semanticos++;
            char* texto_error = mensaje_error_semantico_no_declarado(yytext);
            yyerror(texto_error);
        }
        else
        {
          //printf("--SEMANTICA--// El simbolo existe en el diccionario\n");
          fprintf(output, "\tscanf(\"%%d\", &%s);\n", yytext);
        }
      } 
    | listaIdentificadores COMA IDENTIFICADOR
    {
        if( verificar_uso(yytext))
        {
            errores_semanticos++;
            char* texto_error = mensaje_error_semantico_no_declarado(yytext);
            yyerror(texto_error);
        }
        else
        {
          //printf("--SEMANTICA--// El simbolo existe en el diccionario\n");
          fprintf(output, "\tscanf(\"%%d\", &%s);\n", yytext);
        }
      } 
    ;

listaExpresiones:
    expresion
    {
        if (es_escritura == 0) {
          fprintf(output, "\tprintf(\"%%d\", %s);\n", expresion_actual);
        }
    }
    | listaExpresiones COMA expresion
    {
        if (es_escritura == 0) {
            fprintf(output, "\tprintf(\"%%d\", %s);\n", expresion_actual);
        }
    }
    ;

// Dentro de acá trabajaremos las variables temporales
expresion:
      SUB expresion %prec NEG {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = -%s;\n", temp, $2);
          $$ = temp;
          expresion_actual = temp;
      }
    | expresion ADD expresion {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = %s + %s;\n", temp, $1, $3);
          $$ = temp;
          expresion_actual = temp;
      }
    | expresion SUB expresion {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = %s - %s;\n", temp, $1, $3);
          $$ = temp;
          expresion_actual = temp;
      }
    | expresion MUL expresion {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = %s * %s;\n", temp, $1, $3);
          $$ = temp;
          expresion_actual = temp;
      }
    | expresion DIV expresion {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = %s / %s;\n", temp, $1, $3);
          $$ = temp;
          expresion_actual = temp;
      }
    | expresion MOD expresion {
          char* temp = crear_nombre_variable_temporal();
          fprintf(output, "\tint %s;\n", temp);
          fprintf(output, "\t%s = %s %% %s;\n", temp, $1, $3);
          $$ = temp;
          expresion_actual = temp;
      }
    | IDENTIFICADOR {
          expresion_actual = strdup(yytext);
          if (verificar_uso(yytext)) {
              errores_semanticos++;
              char* texto_error = mensaje_error_semantico_no_declarado(yytext);
              yyerror(texto_error);
          } else {
              $$ = strdup(yytext);
          }
      }
    | CONSTANTE {
          expresion_actual = strdup(yytext);
          $$ = strdup(yytext);
      }
    | PARENTESIS_ABRIR expresion
      {
        if (es_escritura == 0) 
        {
          fprintf(output, "\tprintf(\"%%d\", %s;\n", expresion_actual);
        }
      } 
    PARENTESIS_CERRAR
      {
          $$ = $2;
      }
    ;

%%

void yyerror(const char *s) {
    fprintf(output,"Linea #%d: Error: %s\n",yylineno, s);  //error sintáctico
}
