
#include "ProbabilidadCadena.hh"

using namespace std;

ProbabilidadCadena::ProbabilidadCadena(string _archivodeentrada, string _cadena){
	archivodeentrada = _archivodeentrada;
	cadena = _cadena;
	cout << "Se Calcula la cantidad de estados\n";
	numerodeestados = cantidadEstados();
	
	largoCadena = cadena.size();
	estados = new char[numerodeestados];
	cout << "Se encuentran correctamente los números de estados\n";
	for(int i = 0; i < numerodeestados;i++){
		estados[i] = '\0';
	}

	M = gsl_matrix_alloc(numerodeestados, numerodeestados);
	cadenaAnalizada = leerCadena();
}

int ProbabilidadCadena::cantidadEstados(){
    char cadena[30] = {'\0'};
    // Abre un fichero de entrada
    ifstream fe(archivodeentrada.c_str());
    
    char p;
    int c = 0;
    int cantidadestados = 0;
    while(!fe.eof()){
        fe >> cadena;
        if(c == 0){
            c++;
            p = cadena[0]; 
        }
        
        if(p == cadena[0]){
            cantidadestados++;
        }
    }
    fe.close();

    return cantidadestados;    
}

void ProbabilidadCadena::lecturaArchivo(){
    
    ifstream fe(archivodeentrada.c_str());
    
    string linea;
    float v;
    size_t found;
    int f = 0;
    int c = 0;
    while(!fe.eof()){
        
        getline(fe,linea);
        if(linea.size() > 2){
            found = linea.find(" ");
            v = std::stof(linea.substr(found+1, linea.size()));
            
            for(int i = 0; i < numerodeestados; i++){
                if(linea[0] == estados[i]){
                    break;
                }else if(estados[i] == '\0'){
                    estados[i] = linea[0];
                    break;
                }
            }
            
            gsl_matrix_set(M,f,c,v);
            f++;
            if(f == numerodeestados){
                f = 0;
                c++;
            }
        }
    }
    
    fe.close();
}

float ProbabilidadCadena::obtenerProbabilidades(){
		float probabilidad = 1;
		for(int i = 0; i< largoCadena; i++){
			if(i!=0){
					int currentState = cadenaAnalizada[i];
					int previousState = cadenaAnalizada[i-1];
					float probabilidad2 = gsl_matrix_get(M,currentState,previousState);
					probabilidad = probabilidad*probabilidad2;
			}
		}
		return probabilidad;
	}
	
int * ProbabilidadCadena::leerCadena(){
		float probabilidad = 1;
		cout << "La cantidad de elementos es " << cadena.size() << "\n";
		 
		static int * resultado = (int*) malloc(sizeof(int)*cadena.size());
		
		for(int i = 0; i < cadena.size(); ++i) {
			cout << cadena[i];
			char currentState = cadena[i];
			
			switch(currentState) {
				case 'G':
					resultado[i] = G;
					break;
				case 'A':
					resultado[i] = A;
					break;
			   case 'T':
					resultado[i] = T;
					break; 
			   case 'C':
					resultado[i] = C;
					break;
			   default : 
					printf("ERROR DE LA VIDA");
			}
		}
		return resultado;
	}

void ProbabilidadCadena::mostrarCadena(){
	for(int i = 0; i < largoCadena; i++){
		cout << cadena[i] << " ";
		}
	}
