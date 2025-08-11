#include "parser.h"

//#include "scanner.h"


int main(int argc, char *argv[]) 
{
    
    crearTabla();
    //printf("Estamos iniciando el programa\n");
    file = fopen(argv[1],"r+b");
    parser();
    return 0;
}
