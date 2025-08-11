/*
tabla.c muestra por pantalla (stdout) las filas pedidas, llamando a la función de
conversión. Use assert para poner precondiciones sobre los valores de los parámetros
recibidos.
*/

//#include "tabla.h"

void tabla(float inicio, float fin, float incremento) {
    assert(inicio >= 0 && fin >= inicio && incremento > 0);

    printf(" |     Nudos|      Km/h|\n");
    for (float i = inicio; i <= fin; i += incremento) {
        //printf("%d nudos = %.2f km/h\n", i, conversion(i));
        printf(" |         %.2f|    %.4f|\n", i, conversion(i));
    }
}