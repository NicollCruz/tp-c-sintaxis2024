#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern FILE *output;
extern int yyparse();
extern FILE *yyin;

int errores_lexicos = 0;
extern int yynerrs;
extern int errores_semanticos;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stdout, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }
    
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    output = fopen("mainok.c", "w");  // Abrimos el archivo de salida
    if (!output) {
        perror("No se pudo abrir el archivo para generar el código C");
        return 1;
    }
    yyin = input_file;
    if (yyparse() == 0) {
        //printf("Compilacion exitosa\n");
        if( !(yynerrs == 0 && errores_lexicos == 0 &&  errores_semanticos == 0) )
        {
            fprintf(output,"Errores sintactico: %d - Errores lexicos: %d - Errores semanticos: %d\n",yynerrs,errores_lexicos, errores_semanticos);
        }
    } else {
        //printf("Hubo errores durante la compilacion\n");
    }

    fclose(input_file);
    fclose(output);
    return 0;
}   
