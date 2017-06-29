#include "MatrizEstacionaria.hh"

#include <unistd.h>

int main(int argc,char*argv[]){
    
    std::string archivodeentrada;
    std::string archivodesalida;
    
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
                abort ();
          }
    }

    MatrizEstacionaria me(archivodeentrada, archivodesalida);

    me.lecturaArchivo();

    me.solucionSistema();

    me.escrituraArchivo();
  
    return 0;
}
