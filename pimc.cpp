#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>


using namespace std;

int cantidadEstados(string archivodeentrada){
    char cadena[30] = {'\0'};
    // Abre un fichero de entrada
    ifstream fe(archivodeentrada);
    
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
    

void lecturaArchivo(gsl_matrix *M, string archivodeentrada, int cantidadestados, char* estados){
    
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
            
            for(int i = 0; i < cantidadestados; i++){
                if(linea[0] == estados[i]){
                    break;
                }else if(estados[i] == '\0'){
                    estados[i] = linea[0];
                    break;
                }
            }
            
            gsl_matrix_set(M,f,c,v);
            f++;
            if(f == cantidadestados){
                f = 0;
                c++;
            }
        }
    }
    
    fe.close();
}

void solucionSistema(gsl_matrix *M, gsl_vector *x , int cantidadestados){
    
    gsl_vector *b;
    gsl_permutation *p;
    int s;
    
    // Create the vector and the matrix
    b = gsl_vector_alloc(cantidadestados);
    
    for(int i = 0; i < cantidadestados; i++){
        gsl_vector_set(b, i, 0.0);
        gsl_matrix_set(M, i, i, gsl_matrix_get(M,i,i) - 1.0);
    }
    
    for(int i = 0; i < cantidadestados; i++){
        gsl_matrix_set(M, 0, i, 1.0);
    }
    
    gsl_vector_set(b, 0, 1.0);

    // Solve the system A x = b
    // Start by creating a vector to receive the result
    // and a permutation list to pass to the LU decomposition
    
    p = gsl_permutation_alloc(cantidadestados);
    
    // Do the LU decomposition on A and use it to solve the system
    
    gsl_linalg_LU_decomp(M, p, &s);
    gsl_linalg_LU_solve(M, p, b, x);
    
    // Clean up
    gsl_vector_free(b);
    gsl_permutation_free(p);
    gsl_matrix_free(M);
}

void escrituraArchivo(string archivodesalida, int numerodeestados ,char* estados, gsl_vector * x){
    // Crea un fichero de salida
    ofstream fs(archivodesalida); 
    
    for(int i = 0; i< numerodeestados; i++){
        fs << estados[i] << ": " << gsl_vector_get(x, i) << endl;
    }
    
    // Cerrar el fichero, 
    // para luego poder abrirlo para lectura:
    fs.close();
}

int main(){
    
    string archivodeentrada = "cadenademarkov.txt";
    string archivodesalida = "cadenaestacionaria.txt";
    
    int cantidadestados = cantidadEstados(archivodeentrada);
    
    gsl_matrix* M = gsl_matrix_alloc(cantidadestados, cantidadestados);
    
    gsl_vector* x = gsl_vector_alloc(cantidadestados);
    
    char* estados = new char[cantidadestados];
    lecturaArchivo(M, archivodeentrada, cantidadestados, estados);
    
    solucionSistema(M, x, cantidadestados);
    
    escrituraArchivo(archivodesalida, cantidadestados, estados, x);
    
    gsl_vector_free(x);
    
    return 0;
}
