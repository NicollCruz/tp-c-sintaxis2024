Resultados:

1. Muestre un comando que permita compilar todo el proyecto (sin el makefile) de acuerdo a los lineamientos del curso (adherir estrictamente al estándar).

gcc -g -Wall -pedantic-errors -std=c2x -o programa main.c tabla.c conversion.c

2. Compile con el comando anterior pero modifque tabla.c de modo que no incluya conversion.h, copie el resultado y coméntelo.

    gcc -g -Wall -pedantic-errors -std=c2x -o programa main.c tabla.c conversion.c
    
    tabla.c: In function 'tabla':
    tabla.c:10:5: error: implicit declaration of function 'assert' [-Wimplicit-function-declaration]
    10 |     assert(inicio >= 0 && fin >= inicio && incremento > 0);
        |     ^~~~~~
    tabla.c:1:1: note: 'assert' is defined in header '<assert.h>'; this is probably fixable by adding '#include <assert.h>'
    +++ |+#include <assert.h>
        1 | /*
    tabla.c:12:5: error: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    12 |     printf(" |     Nudos|      Km/h|\n");
        |     ^~~~~~
    tabla.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
    +++ |+#include <stdio.h>
        1 | /*
    tabla.c:12:5: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
    12 |     printf(" |     Nudos|      Km/h|\n");
        |     ^~~~~~
    tabla.c:12:5: note: include '<stdio.h>' or provide a declaration of 'printf'
    tabla.c:15:50: error: implicit declaration of function 'conversion' [-Wimplicit-function-declaration]
    15 |         printf(" |         %.2f|    %.4f|\n", i, conversion(i));
        |                                                  ^~~~~~~~~~
    tabla.c:15:40: warning: format '%f' expects argument of type 'double', but argument 3 has type 'int' [-Wformat=]
    15 |         printf(" |         %.2f|    %.4f|\n", i, conversion(i));
        |                                     ~~~^         ~~~~~~~~~~~~~
        |                                        |         |
        |                                        double    int
        |                                     %.4d

Al no incluir el encabezado conversion.h entonces no contariamos con la capacidad de utilizar las funciones: conversion, printf y assert. Conversion forma parte de los archivos conversion.c y conversion.h y las bibliotecas que incluyen las funciones printf y assert están incluídas en dicho archivo.

3. De un comando que compile todos los fuentes menos tabla.c, ejecútelo, muestre el resultado y coméntelo.

    gcc -g -Wall -pedantic-errors -std=c2x -o programa main.c conversion.c
    C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/14.1.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\Usuario\AppData\Local\Temp\cchqCSfi.o: in function `main':
    C:/Users/Usuario/Desktop/Sintaxis/24-002-15/TP1/main.c:15:(.text+0xaf): undefined reference to `tabla'
    collect2.exe: error: ld returned 1 exit status

Al no compilar tabla.c junto con el resto del programa, cuando en main.c se quiere referenciar a la función tabla no podrá encontrarla y finalmente arrojará un error.

4. Copie el comando necesario para obtener conversion.i, el archivo ya preprocesado de conversion.c

    gcc -E conversión.c -o conversión.i

    gcc -E -std=c2x conversion.c -o conversion.i


Nota: comentar significa analizar el resultado, ver que tipo de error es, donde se produce, etc.
