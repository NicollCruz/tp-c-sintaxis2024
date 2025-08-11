%option outfile="scanner.c"
%option header-file="scanner.h"
%option yylineno
%option noinput
%option nounput
%option never-interactive
%{
#include "parser.h"
extern int errores_lexicos;
extern FILE* output;
%}

letra       [a-zA-Z]
digito      [0-9]
alfanumerico [0-9a-zA-Z]
especial    [!@#$%^&_{}|:"'<>?./`~=]
espacio     [\n\r\t ]
alfanumericoespacio [0-9a-zA-Z0 \t]
todotipo [!@#$%^&_{}|:"'<>?./`~=0-9a-zA-Z0]

%%

"programa"                   { return PROGRAMA; } 
"fin"                        { return FIN_PROG; }
"entero"                     { return ENTERO; }
"leer"                       { return LEER; }
"escribir"                   { return ESCRIBIR; }

{letra}({letra}|{digito})*   { return IDENTIFICADOR; }
{digito}+                    { return CONSTANTE; }

"+"                          { return ADD; }
"-"                          { return SUB; }
"*"                          { return MUL; }
"/"                          { return DIV; }
"%"                          { return MOD; }
":="                         { return ASIGNACION; }
"("                          { return PARENTESIS_ABRIR; }
")"                          { return PARENTESIS_CERRAR; }
","                          { return COMA; }
";"                          { return PUNTO_COMA; }

{espacio}                    { }
"//".*                       { }

{digito}{alfanumerico}+       {fprintf(output,"Linea #%d: ERROR LEXICO: constante invalida: %s\n",yylineno, yytext); errores_lexicos++;}                               
{especial}+                   {fprintf(output,"Linea #%d: ERROR LEXICO: Cadena desconocida: %s\n",yylineno, yytext); errores_lexicos++;}

%%

int yywrap() {
    //printf("Token: Fin de Archivo\n");
    return 1;
}
