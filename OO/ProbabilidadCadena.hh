#ifndef PROBABILIDADCADENA
#define PROBABILIDADCADENA

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#define G 0
#define A 1
#define T 2
#define C 3

using namespace std;

class  ProbabilidadCadena{

	private:
    	std::string archivodeentrada; //nombre del archivo de entrada
		int numerodeestados; //numero de estados
    	gsl_matrix* M;
    	char* estados;
    	int * cadenaAnalizada;
    	int largoCadena;
		std::string cadena;
		int cantidadEstados();
		int * leerCadena();
    public:
    	ProbabilidadCadena(std::string, std::string); //inicializar estructura de  CM y pasar cantidad de estados
    	void lecturaArchivo();
    	float obtenerProbabilidades();
    	void mostrarCadena();
};

#endif
