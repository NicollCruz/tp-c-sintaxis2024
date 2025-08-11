#include "tokens.h"

extern int yylex();
extern char* yytext;
extern FILE* yyin;

int main()
{
    FILE* f = fopen("entrada.txt","r+b");

    yyin = f;
    int ret;

    int token = 10;
    while( token != 0)  // Llama a yylex() hasta que devuelva 0 (fin de archivo)
    {
        token = yylex();
        switch (token) {

            case IDENTIFICADOR: // Identificador
                // Manejo de identificador
                printf("Token: Identificador - Lexema '%s'\n",yytext);
                break;
            case CONSTANTE: // Constante
                // Manejo de constante
                printf("Token: Constante - Lexema '%s'\n",yytext);
                break;
            case PALABRARESERVADA: //Palabra reservada
                printf("Token: %s\n", yytext);
                break;
            case CARACTER_PUNTUACION: // // Carácter de puntuación
                // Manejo de carácter de puntuación
                printf("Token: '%s'\n",yytext);
                break;
            case OPERADOR: // Operador
                // Manejo de operador     
                printf("Token: '%s'\n",yytext);
                break;
            case ASIGNACION: // Asignación
                // Manejo de asignación
                printf("Token: Asignacion\n");
                break;
        }
    
    }
    fclose(f);
}


