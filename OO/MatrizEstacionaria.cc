
#include "MatrizEstacionaria.hh"

using namespace std;

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

void MatrizEstacionaria::solucionSistema(){
    
    gsl_vector *b;
    gsl_permutation *p;
    int s;
    
    // Create the vector and the matrix
    b = gsl_vector_alloc(numerodeestados);
    
    for(int i = 0; i < numerodeestados; i++){
        gsl_vector_set(b, i, 0.0);
        gsl_matrix_set(ecuaciones, i, i, gsl_matrix_get(ecuaciones,i,i) - 1.0);
    }
    
    for(int i = 0; i < numerodeestados; i++){
        gsl_matrix_set(ecuaciones, 0, i, 1.0);
    }
    
    gsl_vector_set(b, 0, 1.0);

    // Solve the system A x = b
    // Start by creating a vector to receive the result
    // and a permutation list to pass to the LU decomposition
    
    p = gsl_permutation_alloc(numerodeestados);
    
    // Do the LU decomposition on A and use it to solve the system
    
    gsl_linalg_LU_decomp(ecuaciones, p, &s);
    gsl_linalg_LU_solve(ecuaciones, p, b, solucion);
    
    // Clean up
    gsl_vector_free(b);
    gsl_permutation_free(p);
    gsl_matrix_free(ecuaciones);
}

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
