%option outfile="scanner.c"
%option header-file="scanner.h"

%{
#include "tokens.h"
%}

/* Definición de patrones léxicos */
letra       [a-zA-Z]
digito      [0-9]
alfanumerico [0-9a-zA-Z]
especial    [!@#$%^&_{}|:"'<>?./`~=]
espacio     [\n\r\t ]
alfanumericoespacio [0-9a-zA-Z0 \t]
todotipo [!@#$%^&_{}|:"'<>?./`~=0-9a-zA-Z0]
%%


"programa"                   { return PALABRARESERVADA; } 
"fin"                        { return PALABRARESERVADA; }
"entero"                     { return PALABRARESERVADA; }
"leer"                       { return PALABRARESERVADA; }
"escribir"                   { return PALABRARESERVADA; }

{letra}({letra}|{digito})*   { return IDENTIFICADOR; }
{digito}+                    { return CONSTANTE; }

[+\-*/%]                     { return OPERADOR; }
":="                         { return ASIGNACION; }
[(),;]                       { return CARACTER_PUNTUACION; }
{espacio}                    {} 
"//".{alfanumericoespacio}+   {}

{especial}* { printf("ERROR LEXICO: Cadena desconocida: %s\n",yytext); }

{digito}{alfanumerico}+ { printf("ERROR LEXICO: constante invalida: %s\n",yytext); }

{todotipo}+ { printf("ERROR LEXICO: identificador invalido %s\n",yytext); }
%%

int yywrap() {
    printf("Token: Fin de Archivo");
    return 1;
}
