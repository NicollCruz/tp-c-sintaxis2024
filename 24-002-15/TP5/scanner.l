%option outfile="scanner.c"
%option header-file="scanner.h"
%option yylineno
%{
#include "parser.h"
extern int errores_lexicos;
%}

letra       [a-zA-Z]
digito      [0-9]
alfanumerico [0-9a-zA-Z]
especial [[:punct:]]{-}[+*/%(),;-]


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
":"                          { printf("Linea #%d: ERROR LEXICO: SOLO ':'\n",yylineno, yytext); errores_lexicos++; }
"="                          { printf("Linea #%d: ERROR LEXICO: SOLO '='\n",yylineno, yytext); errores_lexicos++; }


  
[[:space:]]                  { }
"//".*                       { }

{digito}{alfanumerico}+       { printf("Linea #%d: ERROR LEXICO: constante invalida: %s\n",yylineno, yytext); errores_lexicos++;}
{especial}+                   { printf("Linea #%d: ERROR LEXICO: Cadena desconocida: %s\n",yylineno, yytext); errores_lexicos++;}

%%
