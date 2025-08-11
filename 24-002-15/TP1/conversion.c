/*Conversion.c recibe una velocidad en nudos y devuelve la correspondiente en km/h.
Nota: 1 nudo equivale a 1,852 km/h.
*/
#include "conversion.h"
const float equivalencia = 1.852;
 
float conversion(float nudo) {
    return nudo * equivalencia;
}