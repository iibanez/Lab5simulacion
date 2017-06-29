#ifndef CADENAMARKOV
#define CADENAMARKOV

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string.h> 

// Definición de la clase CadenaMarkov

class CadenaMarkov {

	struct CM {
   		char** estados; //se almacenara de que estado al otro
   		int* transiciones; //cantidad de transiciones de un estado a otro
	};

	private:
		  int numerodeestados; //numero de estados
		  int numeroTotalEstados; //numero de combinaciones entre los estados
    	std::string archivodeentrada; //nombre del archivo de entrada
    	std::string archivodesalida; //nombre del archivo de salida
    	struct CM cm; //estructura de cadena de markov
  public:
    	CadenaMarkov(int, std::string, std::string); //inicializar estructura de  CM y pasar cantidad de estados
    	void findPosicion(char anterior, char actual); //utilizada para buscar donde se almacena la transicion y aumentar en 1 el contador
    	void lecturaArchivo();  //lectura del archivo y crear cadena de markov
		  void escrituraArchivo(); //la cadena de markov es escriba en un archivo

};

#endif
