#include "CadenaMarkov.hh"

int main(){
    
    int numerodeestados = 4;
    std::string archivodeentrada = "dna.txt";
    std::string archivodesalida = "cadenademarkov.txt";
    
    //inicializar la cadena de markov
    CadenaMarkov cm(numerodeestados, archivodeentrada, archivodesalida);
    
    //lectura del archivo de entrada
    cm.lecturaArchivo();
    
    //escritura del archivo de salida
    cm.escrituraArchivo();
    
    return 0;
}
