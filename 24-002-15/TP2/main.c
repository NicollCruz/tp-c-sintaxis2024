#include "scanner.h"

int main()
{
    // Abrir el archivo
    FILE* file = fopen("entrada.txt","r+b");
    extern char *lexema;
    crearTabla();

    bool fDT = false;
    
    while( !fDT )
    {
        int estado = escaner(file);
    
        // Manejo del token
        switch (estado) 
        {
            case 16: // Fin de archivo           
                fDT = true;
                //printf("Fin de texto.\n");
                break;
            case 2: // Identificador
                printf("Identificador '%s'\n",lexema);
                break;
            case 4: // Constante
                printf("Constante '%s'\n",lexema);
                break;
            case 5: // operador +
                printf("Mas '%s'\n",lexema);
                break;
            case 6: //operador -
                printf("Menos '%s'\n",lexema);
                break;
            case 7: //operrador *
                printf("Multiplicacion '%s'\n",lexema);
                break;
            case 8: // operador /
                printf("Division '%s'\n",lexema);
                break;
            case 9: //operador %           
                printf("Resto '%s'\n",lexema);
                break;
            case 10: // Carácter de puntuación  (
                printf("Parentesis que abre '%s'\n",lexema);
                break;
            case 11: // Carácter de puntuación  )
                printf("Parentesis que cierra '%s'\n",lexema);
                break;
            case 12: // Carácter de puntuación (del 10 al 13) ,
                printf("Coma '%s'\n",lexema);
                break;
            case 13: // Carácter de puntuación  ;
                printf("Punto y coma '%s'\n",lexema);
                break;
            case 15: // Asignación
                printf("Asignacion '%s'\n",lexema);
                break;
            case 100: // Error general
                printf("Error general: '%s'\n",lexema);
                break;
            case 101:// Error asignacion solo:
                printf("Error en asignacion por : solo  '%s'\n",lexema);
            break;
            case 102:// Error asignacion solo =
                printf("Error en asignacion por = solo  '%s'\n",lexema);
                break;
            default:
                printf("Entre a default, no se donde estoy\n");
                break;
        }
        free(lexema);
    }
    fclose(file);
    return 0;
}
