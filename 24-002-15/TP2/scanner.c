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
#define COMA 9
#define PUNTO_COMA 10
#define DOS_PUNTOS 11
#define IGUAL 12
#define FDT 13
#define ESP 14
#define OTRO 15

int tabla[18][16];
int estadosTerminales[14] = {2,4,5,6,7,8,9,10,11,12,13,15,16,17};
char *lexema;

int escaner(FILE* f)
{
    // Inicializamos variables
    char c;
    int estadoActual = 0;
    lexema = malloc(200);
    lexema[0] = '\0';

    c = fgetc(f);
    estadoActual = funcionDeTransicion(estadoActual,c);
    concatenar_lexema(c);
    
    while( !esEstadoFinal(estadoActual) && estadoActual != 99 )
    {
        c = fgetc(f);
        estadoActual = funcionDeTransicion(estadoActual,c);
        if( esEstadoFinal(estadoActual) )
        {
            devolver_al_flujo(estadoActual,c,f);
        }
        else
        {
            concatenar_lexema(c);
        }

    }

    // Manejo de errores
    if( estadoActual == 99 )
    {
        int tipoError = tipoDeError(estadoActual,c);
        return tipoError;
    }

    return estadoActual;
}

int funcionDeTransicion(int estadoActual, char c)
{
    if( iscntrl(c) != 0)
    {
        c = ' ';
    }
    int caracter = tipoDeCaracter(c);
    return tabla[estadoActual][caracter];
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
    if (c == ',') return COMA;
    if (c == ';') return PUNTO_COMA;
    if (c == ' ') return ESP;
    if (c == '=') return IGUAL;
    if (c == EOF) return FDT;

    return OTRO;  // Otros 
}

bool esEstadoFinal(int estadoActual)
{
    return esMiembro(estadosTerminales,13,estadoActual);
}

bool esMiembro(int arr[], int tamaño, int elemento) 
{
    for (int i = 0; i < tamaño; i++) {
        if (arr[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool esCaracterDeEspacio(char c)
{
    return (iscntrl(c) != 0 || isspace(c) != 0);
}

void devolver_al_flujo(int estadoActual, char c, FILE* f)
{
    if( estadoActual == 2 || estadoActual == 4)
    {
        ungetc(c,f);
    }
    else
    {
        concatenar_lexema(c);
    }
}

void concatenar_lexema(char c)
{
    if( !esCaracterDeEspacio(c) )
    {
        char* ptr = malloc(sizeof(char));
        *ptr = c;
        strncat(lexema,ptr,1);
        free(ptr);
    }
}

int tipoDeError(int estadoActual, char c)
{
    //Si obtuvimos un ":" sin un "=" después, error de asignación
    if( strcmp(lexema,":") == 0)
    {
        return ERROR_ASIGNACION_SOLO_DOS_PUNTOS;
    }
    else
    {
        if( strcmp(lexema,"=") == 0)
        {
            return ERROR_ASIGNACION_SOLO_IGUAL;
        }
        else
        {
                return ERROR_COMUN;
        }
    }
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
        tabla[17][15] = 17;
    }
}