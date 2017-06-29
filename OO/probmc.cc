#include "ProbabilidadCadena.hh"
#include <unistd.h>
#define G 0
#define A 1
#define T 2
#define C 3

using namespace std;

int main(int argc,char*argv[]){
	
	std::string cadena;
    std::string archivodeentrada;
	
	opterr = 0;
    int c;
    
	while ((c = getopt (argc, argv, ":i:s:")) != -1){
        switch (c)
          {
            case 'i':
                archivodeentrada = optarg;
                break;
            case 's':
                cadena = optarg;
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
	
    ProbabilidadCadena pc(archivodeentrada, cadena);

	pc.lecturaArchivo();
	
    pc.mostrarCadena();
        	
	cout << "\nLa probabilidad de tener la cadena ingresada es de " << pc.obtenerProbabilidades();
	cout << "\n";	
	return 1;
	}
