#include "scanner.h"

#define L 0
#define D 1
#define MAS 2
#define MENOS 3
#define ASTERISCO 4
#define BARRA 5
#define PORCIENTO 6
#define PARENT_ABRE 7
#define PARENT_CIERRA 8
#define COMAA 9
#define PUNTO_COMA 10
#define DOS_PUNTOS 11
#define IGUAL 12
#define FDT 13
#define ESP 14
#define OTRO 15

int tabla[18][16];
int estadosTerminales[14] = {2,4,5,6,7,8,9,10,11,12,13,15,16,17};
char* tabla_de_palabras_reservadas[5] = {"programa","fin","entero","leer","escribir"};
char* lexema;
FILE* file;


static bool debo_escanear = true;
static token token_actual;


token prox_token()
{
    if( debo_escanear )
    {
        token_actual = escaner(file);
        //printf("El token actual leido es: %d\n",token_actual);
        // Casos de error
        while( token_actual == ERROR_ASIGNACION || token_actual == ERROR_COMUN )
        {
            //printf("Estoy en el while\n");
            if( token_actual == ERROR_ASIGNACION || token_actual == ERROR_COMUN )
            {
                //imprimir
                imprimir_mensaje_error(token_actual);
            }
            token_actual = escaner(file);
        }
        debo_escanear = false;
        if( token_actual == IDENTIFICADOR )
        {
            //printf("Estoy en el if\n");
            token resultado = buscar(lexema, tabla_de_palabras_reservadas);
            token_actual = resultado;
        }
        //printf("Retornaremos el siguiente token: %d\n",token_actual);
    }
    return token_actual;
}

void match(token tok)
{
    if( tok != prox_token() )
    {
        error_sintactico(prox_token());
    }
    debo_escanear = true;
}


// Hay que verificar si funciona
token buscar(char* lexema, char* tabla_de_palabras_reservadas[5])
{
    if( strcmp(lexema,tabla_de_palabras_reservadas[0]) == 0 )
    {
        return PROGRAMA;
    }
    if( strcmp(lexema,tabla_de_palabras_reservadas[1]) == 0  )
    {
        return FIN;
    }

    if( strcmp(lexema,tabla_de_palabras_reservadas[2]) == 0)
    {
        return ENTERO;
    }

    if( strcmp(lexema,tabla_de_palabras_reservadas[3]) == 0 )
    {
        return LEER;
    }

    if( strcmp(lexema,tabla_de_palabras_reservadas[4]) == 0 )
    {
        return ESCRIBIR;
    }

    return IDENTIFICADOR;
}

void imprimir_mensaje_error(token token_actual)
{
    if( token_actual == ERROR_ASIGNACION )
    {
        printf("Error de asignacion por: solo '%s'\n",lexema);
    }
    else
    {
        if( token_actual == ERROR_COMUN )
        {
            printf("Error general '%s'\n",lexema);
        }
    }
}

char* token_to_string(token tok)
{
    switch (tok){
        case PAREN_ABRE:
            return "Abrir parentesis ('(')";
            break;
        case PAREN_CIERRA:
            return "Cerrar parentesis (')')";
            break;
        case PUNTOYCOMA:
            return "Punto y Coma (';')";
            break;
        case IDENTIFICADOR:
            return "Identificador ";
            break;
        case COMA:
            return "Coma (',') ";
            break;
        case SUMA:
            return "Suma ('+') ";
            break;
        case RESTA:
            return "Resta ('-') ";
            break;
        case OPERADOR:
            return "Operador ('*, /, %%')";
            break;
        case ASIGNACION:
            return "Asiganacion (= , :) ";
            break;
        case CONSTANTE:
            return "Constante";
            break;
    }
}

void error_sintactico(token tok)
{
    char* tokenAImprimir = token_to_string(tok);
    if( tok == IDENTIFICADOR)
    {
        printf("Error sintactico, no se esperaba el token %s('%s')\n",tokenAImprimir,lexema);
    }
    else
    {
        printf("Error sintactico, no se esperaba el token %s\n",tokenAImprimir);
    }
}

int tipoDeCaracter(char c)
{
    if (isalpha(c)) return L;  // Letras
    if (isdigit(c)) return D;  // Dígitos
    if (c == ':') return DOS_PUNTOS;
    if (c == '+' ) return MAS;
    if (c == '-') return MENOS;
    if (c == '*' ) return ASTERISCO;
    if (c == '/') return BARRA;
    if (c == '%') return PORCIENTO;
    if (c == '(') return PARENT_ABRE;
    if (c == ')') return PARENT_CIERRA;
    if (c == ',') return COMAA;
    if (c == ';') return PUNTO_COMA;
    if (c == ' ') return ESP;
    if (c == '=') return IGUAL;
    if (c == EOF) return FDT;

    return OTRO;  // Otros 
}

int funcionDeTransicion(int estadoActual, char c)
{
    // De ser alguno de estos caracteres, tomarlos como un espacio
    if( c == '\r' || c == '\n' || c == '\t' )
    {
        c = ' ';
    }
    int caracter = tipoDeCaracter(c);
    return tabla[estadoActual][caracter];
}

bool esMiembro(int arr[], int tamaño, int elemento) {
    for (int i = 0; i < tamaño; i++) {
        if (arr[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool esEstadoFinal(int estadoActual)
{
    return esMiembro(estadosTerminales,13,estadoActual);
}

bool tipoDeError(token estadoViejo, token estadoActual, char c, token* tipoError)
{
    //Si obtuvimos un ":" sin un "=" después, error de asignación
    if( estadoViejo == 14 && estadoActual != 15 )
    {
        *tipoError = ERROR_ASIGNACION;
        return true;
    }

    if( estadoViejo == 0 && estadoActual == 17 )
    {
        //Si obtuvimos un "=" sin un ":" antes, error de asignación
        if( c == '=' )
        {
            *tipoError = ERROR_ASIGNACION;
        }
        else
        {
            // Se encontró un caracter inválido
            *tipoError = ERROR_COMUN;
        }
        return true;
    }
    return false;
}

token escaner()
{
    //printf("Hola, estoy aca\n");
    //leer programa
    bool error = false;
    token* tipoError = malloc(sizeof(token));
    *tipoError = -1;
    int estadoActual = 0;

    lexema = malloc(200);
    lexema[0] = '\0';  // buffer esté vacío al principio

    // Mientras no lleguemos a un estado final o tengamos error
    while( !esEstadoFinal(estadoActual) && !error )
    {
        // Obtenemos caracter
        char c;
        c = fgetc(file);
        //printf("El caracter encontrado es: %c\n",c);

        // Aplicamos funcion
        int estadoViejo = estadoActual; // guardamos estado anterior para contemplar errores
        estadoActual = funcionDeTransicion(estadoActual,c);

        // Aplicamos error
        error = tipoDeError(estadoViejo, estadoActual, c, tipoError);

        //aplicamos comportamiento dependiendo del estado
        aplicarAccionSegunEstado(file, estadoActual, c);

        
        // Contatenamos para la devolucion
        char* ptr = malloc(sizeof(char));
        *ptr = c;
        if( !esCaracterDeEspacio(c) && estadoActual != 2 && estadoActual != 4 )
        {
            strncat(lexema,ptr,1);
        }
        
        free(ptr);
        /*
        printf("Mi estado actual es: %d\n",estadoActual);
        printf("Estoy iterando\n");
        */
    }

    //Devolucion
    verificarLexema(lexema,estadoActual,tipoError); //Para verificar la validez de las cadenas de caracteres y constantes

    /*
    Lexema* to_ret = malloc(sizeof(Lexema));
    to_ret->lexema = malloc(strlen(lexema)+1);
    to_ret->codigo = tipoDeToken(estadoActual,*tipoError);
    strcpy(to_ret->lexema,lexema);
    */

    /*
    free(lexema);
    free(tipoError);
    */

    token to_ret = tipoDeToken(estadoActual,*tipoError);
    return to_ret;
}

void verificarLexema(char* lexema, int estadoFinal, token* tipoError) // verifica las cadenas invalidas
{
    if( estadoFinal == 2 )
    {
        //debo verificar cadena
        for(int i = 0; i < strlen(lexema); i++)
        {
            if( !isalpha(lexema[i]) && !isdigit(lexema[i]) )
            {
                *tipoError = ERROR_COMUN;
                return;
            }
        }
    }
    else
    {
        if( estadoFinal == 4 )
        {
            //debo verificar constante numérica
            for(int i = 0; i < strlen(lexema); i++)
            {
                if( !isdigit(lexema[i]) )
                {
                    *tipoError = ERROR_COMUN;
                    return;
                }
            }
        }
    }
}

token tipoDeToken(int estado, token tipoDeError)
{
    if( tipoDeError == ERROR_COMUN)
    {
        //printf("We are gonna send a ERROR_COMUN\n");
        return ERROR_COMUN;
    }
    else
    {
        if( tipoDeError == ERROR_ASIGNACION )
        {
            //printf("We are gonna send a ERROR_ASIGNACION\n");
            return ERROR_ASIGNACION;
        }    
    }

    if( estado == 2)//identificador
    {
        return IDENTIFICADOR;
    }
    else if(estado == 4) //Constante
    {
        return CONSTANTE;
    }
    else if( estado == 5 ) //operador suma
    {
        return SUMA;
    }
    else if( estado == 6 ) //operador resta
    {
        return RESTA;
    }
    else if(estado == 7 || estado == 8 || estado == 9) //operador * % /
    {
        return OPERADOR;
    }
    else if(estado == 10)
    {
        return PAREN_ABRE;
    }
      else if(estado == 11)
    {
        return PAREN_CIERRA;
    }
        else if(estado == 12)
    {
        return COMA;
    }
      else if(estado == 13)
    {
        return PUNTOYCOMA;
    }
    else if ( estado ==15) //asignación
    {
        return ASIGNACION;
    }
    else if( estado == 16) //fdt
    {
        return FDA;
    }
}

void aplicarAccionSegunEstado(FILE* f, int estadoActual, char c)
{
    if( estadoActual == 2 || estadoActual == 4 )
    {
        ungetc(c,f); //"devolver" un carácter a un flujo de entrada. Esto significa que puedes volver a poner un carácter en el buffer de entrada de un archivo
    }
}

bool esCaracterDeEspacio(char c)
{
    return (c == '\n' || c == '\r' || c == '\t' || c == ' ');
}


void crearTabla()
{
    //[fila][columna]
    //Estado cero
    tabla[0][0] = 1; //L
    tabla[0][1] = 3; //D
    tabla[0][2] = 5; //+
    tabla[0][3] = 6; //-
    tabla[0][4] = 7; //*
    tabla[0][5] = 8; // /
    tabla[0][6] = 9; // %
    tabla[0][7] = 10; // (
    tabla[0][8] = 11; // )
    tabla[0][9] = 12; // ,
    tabla[0][10] = 13; // ;
    tabla[0][11] = 14; // :
    tabla[0][12] = 17; // =
    tabla[0][13] = 16; // FDT
    tabla[0][14] = 0; // ESPACIO
    tabla[0][15] = 17; // OTRO

    //Estado uno
    tabla[1][0] = 1;
    tabla[1][1] = 1;
    for(int j = 2; j < 16; j++)
    {
        tabla[1][j]=2;
    }
    tabla[1][15] = 1;
    
    //Estado dos
    for(int j = 0; j < 16; j++)
    {
        tabla[2][j]=99;
    }
    
    //Estado tres
    for(int j = 0; j < 16; j++)
    {
      
        if( j == 1 )
        {
            tabla[3][j]=3;
        }
        else
        {
            tabla[3][j]=4;
        }
    }
    tabla[3][0] = 3;

    //Estado cuatro al trece
    for (int i = 4; i <= 13; i++) {
        for (int j = 0; j < 16; j++) {
            tabla[i][j] = 99; // Estado de error para todos los caracteres
        }
    }

    //Estado catorce
    for(int j = 0; j < 16; j++)
    {
        if( j == 12)
        {
            tabla[14][j] = 15;
        }
        else
        {
            tabla[14][j]=17;
        }
    }   

    //Estado quince a 17
    for (int i = 15; i <= 17; i++) {
        for (int j = 0; j < 16; j++) {
            tabla[i][j] = 99; // Estado de error para todos los caracteres
        }
    }

}