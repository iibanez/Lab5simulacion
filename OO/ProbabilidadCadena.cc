
#include "ProbabilidadCadena.hh"

using namespace std;
/*
##Clase que permitirá la obtención de la probabilidad de tener una secuencia
* en el adn
* 
* Constructor
* Entrada: 
* _archivodeentrada: Nombre del archivo que contiene la matriz de transiciones asociadas a la cadena de markov
* _cadena: cadena que será utilizada para encontrar la probabilidad ejemplo "AATTAACCGT"
* */
ProbabilidadCadena::ProbabilidadCadena(string _archivodeentrada, string _cadena){
	archivodeentrada = _archivodeentrada;
	cadena = _cadena;
	numerodeestados = cantidadEstados();
	
	largoCadena = cadena.size();
	estados = new char[numerodeestados];
	for(int i = 0; i < numerodeestados;i++){
		estados[i] = '\0';
	}

	M = gsl_matrix_alloc(numerodeestados, numerodeestados);
	cadenaAnalizada = leerCadena();
}

/*
* Esta función encargada de leer los estados desde al archivo de entrada
* 
* Salida:
*   numerodeestados: corresponde a la cantidad de estados que contiene el archivo
*/
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

/*
* Es leido el archivo de entrada y son pasados las probabilidades a una matriz de transicion
*/
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

/* Función utilizada para obtener las probabilides de la matriz de transición
 * y finalmente obtener la probabilidad de la cadena solicitada
 * */
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
	
/* Esta función es utilizada para transforma la cadena en forma de string
 * a una cadena de enteros, que será aprovechada para acceder a las
 * probabilidades de la matriz de transformación
 * */
int * ProbabilidadCadena::leerCadena(){
		 
		static int * resultado = (int*) malloc(sizeof(int)*cadena.size());
		int index = 0;
		
		for(int i = 0; i < cadena.size(); ++i) {
			char currentState = cadena[i];
			
			switch(currentState) {
				case 'G':
					resultado[index] = G;
					index++;
					break;
				case 'A':
					resultado[index] = A;
					index++;
					break;
			   case 'T':
					resultado[index] = T;
					index++;
					break; 
			   case 'C':
					resultado[index] = C;
					index++;
					break;
			   default : 
					printf("\nCarácter inválido omitido: %c\n",cadena[i]);
					largoCadena = largoCadena-1;
			}
		}
		return resultado;
	}

/*	Función utilizada para mostrar la cadena analizada con lenguaje humano
 * y no con los números que son manejados en el programa
 * 
 * */
void ProbabilidadCadena::mostrarCadena(){
	cout << "Largo cadena utilizada:\t" << largoCadena << "\n";
	cout << "Cadena utilizada:\t";
	for(int i = 0; i < largoCadena; i++){
		switch(cadenaAnalizada[i]){
			case G:
				cout << "G";
				break;
			case A:
				cout << "A";
				break;
			case T:
				cout << "T";
				break; 
			case C:
				cout << "C";
				break;
			default:
				printf("Error FATAL");
				break;
			}
		}
	cout <<"\n";
	}
