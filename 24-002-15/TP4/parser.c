#include "parser.h"

void parser () {
    // <objetivo> -> <programa> FDT
    programa();
    match(FDA);
}
void programa () {
    // <programa> -> INICIO <listaSentencias> FIN
    match(PROGRAMA);//palabra reservada INICIO
   // printf("Programa: %s\n",lexema);
    listaSentencias();
    match(FIN); //palabra reservada FIN
    printf("Fin\n");
}

void listaSentencias () {
    // <listaSentencias> -> <sentencia> {<sentencia>}
    match(IDENTIFICADOR);
    printf("Programa: %s\n",lexema);
    sentencia(); // la primera de la lista
    while (prox_token() != FIN) { // un ciclo indefinido
        token next_token = prox_token();
        //printf("El proximo token en este instante es: %d\n",next_token);
        switch (prox_token()) {
        case IDENTIFICADOR:
        case ENTERO:
        case LEER:
        case ESCRIBIR: // detecto token correcto
            sentencia(); // procesa la secuencia
            // opcional
            break;
        default:
            match(prox_token());   
            break;
        } // fin switch
    }
}

void sentencia() {
    token tok = prox_token();
        switch (tok) {
        case ENTERO:
            match(ENTERO);
            match(IDENTIFICADOR);
            match(PUNTOYCOMA);
            printf("Sentencia declaracion\n");
            break;
        case IDENTIFICADOR: // <sentencia> -> ID := <expresion>;
            match(IDENTIFICADOR); 
            match(ASIGNACION);
            expresion(); 
            match(PUNTOYCOMA);
            printf("Sentencia asignacion\n"); 
            break;
        case LEER: // <sentencia> -> LEER ( <listaIdentificadores> );
            match(LEER);
            printf("Sentencia leer\n");   
            match(PAREN_ABRE);
            //printf("He matcheado leer y parentesis que abre\n");
            listaIdentificadores();
            match(PAREN_CIERRA); 
            match(PUNTOYCOMA);
  
            break;
        case ESCRIBIR: // <sentencia> -> ESCRIBIR (<listaExpresiones>);
            match(ESCRIBIR); 
            match(PAREN_ABRE);
            listaExpresiones();
            match(PAREN_CIERRA); 
            match(PUNTOYCOMA);
            printf("Sentencia escribir\n");
            break;
        default:
            //errorSintactico(tok); 
            break;
        }
}

void listaIdentificadores(){
    //<listaIdentificadores> -> <identificador> {<identificador>}
    match(IDENTIFICADOR);
    //printf("Matchee con un identificador");
    while( prox_token() == COMA )
    {
        match(COMA);
        match(IDENTIFICADOR);
    }
}


void listaExpresiones () {
    // <listaExpresiones> -> <expresion> {COMA <expresion>}
    expresion(); // la primera de la lista de expresiones
    while (prox_token() == COMA) {
        // El resto de las opcionales
        match(COMA); 
        expresion();
    }
}


void expresion() {
    // <expresion> -> <termino> {(+ | -) <termino>}
    termino(); // Procesa el primer termino
    while (prox_token() == SUMA || prox_token() == RESTA) {
        token op = prox_token(); // Guarda el operador
        match(op); 
        termino();
    }
}
void termino() {
    // <termino> -> <primaria> {(* | / | %) <primaria>}
    primaria();
    while (prox_token() == OPERADOR) {
        match(OPERADOR);
        primaria(); // Procesa la siguiente primaria
    }
}

void primaria() {
    // <primaria> := identicador | constante | ( expresion ) | - expresion
    switch (prox_token()) {
        case IDENTIFICADOR:
            match(IDENTIFICADOR);
            break;
        case CONSTANTE:
            match(CONSTANTE); 
            break;
        case PAREN_ABRE:
            match(PAREN_ABRE);
            expresion();
            match(PAREN_CIERRA);
            break;
        case RESTA:
            match(RESTA);
            expresion();
        default:
            //errorSintactico(prox_token()); 
            break;
    }
}