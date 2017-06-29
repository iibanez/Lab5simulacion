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
    	gsl_vector* solucion;
    	gsl_matrix* ecuaciones;
    	char* estados;
    	int cantidadEstados();
    public:
    	MatrizEstacionaria(std::string, std::string); //inicializar estructura de  CM y pasar cantidad de estados
    	void lecturaArchivo(); 
    	void solucionSistema();
		void escrituraArchivo();

};

#endif