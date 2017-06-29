#ifndef MATRIZESTACIONARIA
#define MATRIZESTACIONARIA

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

// Definición de la clase MatrizEstacionaria

class  MatrizEstacionaria{

	private:
		int numerodeestados; //numero de estados
    	std::string archivodeentrada; //nombre del archivo de entrada
    	std::string archivodesalida; //nombre del archivo de salida
    	gsl_vector* solucion; // ecuaciones*X = solucion
    	gsl_matrix* ecuaciones;
    	char* estados;
    	int cantidadEstados(); //es leida la cantidad de estados desde el archivo de entrada
    public:
    	MatrizEstacionaria(std::string, std::string); //inicializar estructura de  CM y pasar cantidad de estados
    	void lecturaArchivo();  //lectura del archivo de entrada y crear matriz de transiciones
    	void solucionSistema(); //dar solucion al sistema de ecuaciones
		void escrituraArchivo(); //escritura de la solcion en un archivo de salida

};

#endif