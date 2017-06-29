#include "CadenaMarkov.hh"

#include <unistd.h>

int main(int argc,char*argv[]){
    
    int numerodeestados = 0;
    std::string archivodeentrada = "\0";
    std::string archivodesalida = "\0";

    //Se reciben los parametros de entrada
    opterr = 0;
    int c;

    while ((c = getopt (argc, argv, ":i:N:o:")) != -1){
        switch (c)
          {
            case 'i':
                archivodeentrada = optarg;
                break;
            case 'N':
                numerodeestados = atoi(optarg);
                break;
            case 'o':
                archivodesalida = optarg;
                break;
            case ':':
                fprintf(stderr, "%s: option '-%c' requires an argument\n",argv[0], optopt);
                return 1;
            case '?':
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%c'.\n", optopt);
                return 1;
            default:
				printf("Se necesita argumento -i archivodeentrada.txt -N numerodeestados -o nombrearchivodesalida.txt\n"); 
                abort ();
          }
    }

    if(numerodeestados == 0 || archivodeentrada == "\0" || archivodesalida == "\0"){
        printf("Se necesita argumento -i archivodeentrada.txt -N numerodeestados -o nombrearchivodesalida.txt\n");
        return 0;
    }

    //inicializar la cadena de markov
    CadenaMarkov cm(numerodeestados, archivodeentrada, archivodesalida);
    
    //lectura del archivo de entrada
    printf("Leyendo el archivo de entrada: %s\n", archivodeentrada.c_str());
    cm.lecturaArchivo();
    
    //escritura del archivo de salida
    printf("Escribiendo resultado en archivo de salida: %s\n", archivodesalida.c_str());
    cm.escrituraArchivo();
    printf("Archivo de salida escrito con exito\n");

    return 0;
}
