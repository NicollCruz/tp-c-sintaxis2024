# Grupo 15 - SSL K2002 - 2024

## Trabajo Práctico Nº 2 – Escáner


### Integrantes:

- Lucas Alberto Alonso Salinas.
- Malena Ochoa.
- Nicoll Alexandra Cruz Villegas.
- Matias Hernandez.

### Salida esperada y aclaraciones.
- En la tabla de transición, los estados 2 y 4 son estados aceptores para cadenas y constantes reconocidas, respectivamente. Sin embargo, en nuestro TP al terminar de leer la cadena y llegar a dichos estados verificamos si es válida o no para considerar los casos en los cuales tengamos "12A23" o "tot@l1" como errores. Dado que sino se consideraba a "12A" como error y "23" como constante, por mencionar un ejemplo.

- A diferencia de la salida del archivo salida.txt el Error general '@#!' da como resultado errores generales por separado, es decir: 
``` c
        Error general '@'
        Error general '#'
        Error general '!'
