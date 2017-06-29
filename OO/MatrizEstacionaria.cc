
#include "MatrizEstacionaria.hh"

using namespace std;

/*
* Esta función corresponde al constructor de la clase y es la encargada de inicializar todos las 
* variables
*
* Entrada:
*   _archivodeentrada: corresponde al nombre del archivo de entrada
*   _archivodesalida: corresponde al nombre del archivo de salida
*/
MatrizEstacionaria::MatrizEstacionaria(string _archivodeentrada, string _archivodesalida){
	archivodeentrada = _archivodeentrada;
	archivodesalida = _archivodesalida;
	numerodeestados = cantidadEstados();
	estados = new char[numerodeestados];
	for(int i = 0; i < numerodeestados;i++){
		estados[i] = '\0';
	}
	ecuaciones = gsl_matrix_alloc(numerodeestados, numerodeestados);
    solucion = gsl_vector_alloc(numerodeestados);
}

/*
* Esta función encargada de leer los estados desde al archivo de entrada
* 
* Salida:
*   numerodeestados: corresponde a la cantidad de estados que contiene el archivo
*/
int MatrizEstacionaria::cantidadEstados(){
    char cadena[30] = {'\0'};
    // Abre un fichero de entrada
    ifstream fe(archivodeentrada);
    
    char p;
    int c = 0;
    int numerodeestados = 0;
    while(!fe.eof()){
        fe >> cadena;
        if(c == 0){
            c++;
            p = cadena[0]; 
        }
        
        if(p == cadena[0]){
            numerodeestados++;
        }
    }
    fe.close();

    return numerodeestados;    
}
    
/*
* Es leido el archivo de entrada y son pasados las probabilidades a una matriz de transicion
*/
void MatrizEstacionaria::lecturaArchivo(){
    
    ifstream fe(archivodeentrada);
    
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
            
            gsl_matrix_set(ecuaciones,f,c,v);
            f++;
            if(f == numerodeestados){
                f = 0;
                c++;
            }
        }
    }
    
    fe.close();
}

/*
* El sistema de ecuaciones es resuelto
*/
void MatrizEstacionaria::solucionSistema(){
    
    gsl_vector *b;
    gsl_permutation *p;
    int s;
    
    // crear vector de estados
    b = gsl_vector_alloc(numerodeestados);
    
    for(int i = 0; i < numerodeestados; i++){
        gsl_vector_set(b, i, 0.0);
        gsl_matrix_set(ecuaciones, i, i, gsl_matrix_get(ecuaciones,i,i) - 1.0);
    }
    
    for(int i = 0; i < numerodeestados; i++){
        gsl_matrix_set(ecuaciones, 0, i, 1.0);
    }
    
    gsl_vector_set(b, 0, 1.0);

    // resolver sistema A x = b
    p = gsl_permutation_alloc(numerodeestados);
    gsl_linalg_LU_decomp(ecuaciones, p, &s);
    gsl_linalg_LU_solve(ecuaciones, p, b, solucion);
    
    // liberar memoria de las matrices
    gsl_vector_free(b);
    gsl_permutation_free(p);
}

/*
* La solución del sistema de ecuaciones es escrito en el archivo de salida
*/
void MatrizEstacionaria::escrituraArchivo(){
    // Crea un fichero de salida
    ofstream fs(archivodesalida); 
    
    for(int i = 0; i< numerodeestados; i++){
        fs << estados[i] << ": " << gsl_vector_get(solucion, i) << endl;
    }
    
    // Cerrar el fichero, 
    // para luego poder abrirlo para lectura:
    fs.close();
}
