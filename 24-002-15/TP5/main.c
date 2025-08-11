#include "parser.h"
#include <stdio.h>
extern FILE* yyin;
int errores_lexicos;
extern int yynerrs;
    
int main(int argc, char *argv[]) 
{
    yyin= stdin;

    errores_lexicos = 0;
    // llamar al PARSER
     if (yyparse() == 0) {
        printf("Compilacion terminada con exito.\n");
        printf("Errores sintactico: %d - Errores lexicos: %d\n",yynerrs,errores_lexicos);
    } else {
        printf("Error en el analisis sintactico.\n");
        printf("Errores sintactico: %d - Errores lexicos: %d\n",yynerrs,errores_lexicos);
    }

    return 0;
}
