#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

struct CadenaMarkov {
   char** estados; //se almacenara de que estado al otro
   int* transiciones; //cantidad de transiciones de un estado a otro
};


void initCadenaMarkov(struct CadenaMarkov *cm, int numerodeestados){
    cm->estados = new char*[numerodeestados];
    cm->transiciones = new int[numerodeestados];
    
    for(int i = 0; i < numerodeestados; i++){
        cm->estados[i] = new char[2];
        cm->estados[i][0] = '\0';
        cm->estados[i][1] = '\0';
        
        cm->transiciones[i] = 0;
    }
}


void findPosicion(char anterior, char actual, int numerodeestados, struct CadenaMarkov *cm){
    int i;
    for(i = 0; i < numerodeestados; i++){
        if(cm->estados[i][0] == anterior && cm->estados[i][1] == actual){
            cm->transiciones[i]++;
            return;
        }else if(cm->estados[i][0] == '\0'){
            break;
        }
    }
    
    cm->estados[i][0] = anterior;
    cm->estados[i][1] = actual;
    cm->transiciones[i]++;
}


void lecturaArchivo(struct CadenaMarkov *cm, int numerodeestados, string archivodeentrada){
    char cadena[128] = {'\0'};
    // Abre un fichero de entrada
    ifstream fe(archivodeentrada);
    
    char anterior = ' ';
    char actual;
    while(!fe.eof()){
        fe >> cadena;
        for(int i = 0; i <128; i++){
            actual = cadena[i];
            if(anterior == ' '){
                anterior = actual;
            }else if(actual != '\0' && actual != ' ' && actual != 'N'){
                //cout << anterior << "->" << actual << endl;
                findPosicion(anterior, actual, numerodeestados, cm);
                anterior = actual;
            }
            cadena[i] = '\0';
        }
    }
    fe.close();
}


void escrituraArchivo(struct CadenaMarkov *cm, int numeroTotalEstados,int numerodeestados, string archivodesalida){
    // Crea un fichero de salida
    ofstream fs(archivodesalida); 
    
    char est[numerodeestados] = {'\0'};
    int total[numerodeestados] = {0};
    
    for(int i=0; i < numeroTotalEstados; i++){
        for(int j=0; j < numerodeestados; j++){
            if(est[j] == '\0'){
                est[j] = cm->estados[i][0];
                break;
            }else if(est[j] == cm->estados[i][0]){
                break;
            }
        }
        
        for(int j=0; j < numerodeestados; j++){
            if(est[j] == cm->estados[i][0]){
                total[j] = cm->transiciones[i] + total[j];
            }
        }
    }
    
    // Enviamos una cadena al fichero de salida:
    int encontro;
    for(int p=0; p < numerodeestados; p++){
        for(int x=0; x < numerodeestados; x++){
            encontro = 0;
            for(int i=0; i < numeroTotalEstados; i++){
                if(cm->estados[i][0] == est[p] && cm->estados[i][1] == est[x]){
                    fs << cm->estados[i][0] << "->" << cm->estados[i][1] << ": " << ((float)cm->transiciones[i]/(float)total[p]) << endl;
                    encontro = 1;
                }
            }
            if(encontro == 0){
                fs << est[p] << "->" << est[x] << ": 0" << endl;
            }
        }
    }
    
    // Cerrar el fichero, 
    // para luego poder abrirlo para lectura:
    fs.close();
}


int main(){
    
    int numerodeestados = 4;
    string archivodeentrada = "dna.txt";
    string archivodesalida = "cadenademarkov.txt";
    
    struct CadenaMarkov cm;
    int numeroTotalEstados = numerodeestados*numerodeestados;
    //inicializar la cadena de markov
    initCadenaMarkov(&cm, numeroTotalEstados);
    
    //lectura del archivo de entrada
    lecturaArchivo(&cm, numeroTotalEstados, archivodeentrada);
    
    //escritura del archivo de salida
    escrituraArchivo(&cm, numeroTotalEstados, numerodeestados, archivodesalida);
    
    return 0;
}
