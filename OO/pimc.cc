#include "MatrizEstacionaria.hh"

#include <unistd.h>

int main(int argc,char*argv[]){
    
    std::string archivodeentrada = "\0";
    std::string archivodesalida = "\0";
    
    opterr = 0;
    int c;

    while ((c = getopt (argc, argv, ":i:o:")) != -1){
        switch (c)
          {
            case 'i':
                archivodeentrada = optarg;
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
                printf("Se necesita argumento -i archivodeentrada.txt -o nombrearchivodesalida.txt\n"); 
                abort ();
          }
    }

    if(archivodeentrada == "\0" || archivodesalida == "\0"){
        printf("Se necesita argumento -i archivodeentrada.txt -o nombrearchivodesalida.txt\n");
        return 0;
    }

    //se inicializa el ojeto
    MatrizEstacionaria me(archivodeentrada, archivodesalida);

    //se lee el archivo de entrada
    printf("Leyendo el archivo de entrada: %s\n", archivodeentrada.c_str());
    me.lecturaArchivo();

    //se resuleve el sistema de ecuaciones
    printf("Solucionando sistema de ecuaciones\n");
    me.solucionSistema();

    //se escribe los resultados en el archivo de salida
    printf("Escribiendo resultado en archivo de salida: %s\n", archivodesalida.c_str());
    me.escrituraArchivo();
    printf("Archivo de salida escrito con exito\n");
  
    return 0;
}
