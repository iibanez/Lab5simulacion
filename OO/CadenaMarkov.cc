#include "CadenaMarkov.hh"

using namespace std;

/*
* Esta función corresponde al constructor de la clase y es la encargada de inicializar todos las 
* variables
*
* Entrada:
*   _numerodeestados: corresponde a los estados que se encuentran en el archivo de entrada
*   _archivodeentrada: corresponde al nombre del archivo de entrada
*   _archivodesalida: corresponde al nombre del archivo de salida
*/

CadenaMarkov::CadenaMarkov(int _numerodeestados, string _archivodeentrada, string _archivodesalida){
	numerodeestados = _numerodeestados;
	archivodeentrada = _archivodeentrada;
	archivodesalida = _archivodesalida;

	numeroTotalEstados = numerodeestados*numerodeestados;
	cm.estados = new char*[numeroTotalEstados];
    cm.transiciones = new int[numeroTotalEstados];
    
    for(int i = 0; i < numeroTotalEstados; i++){
        cm.estados[i] = new char[2];
        cm.estados[i][0] = '\0';
        cm.estados[i][1] = '\0';
        
        cm.transiciones[i] = 0;
    }
}

/*
* Esta función se encarga de incrementar en uno el contador de las transiciones
* y en caso de que aun no se haya creado la transicion crearla
*
* Entrada:
*   anterior: corresponde al caracter anterior es el inicio de la transicion
*   actual: corresponde al caracter actual es el fin de la transicion
*/

void CadenaMarkov::findPosicion(char anterior, char actual){
    int i;
    for(i = 0; i < numeroTotalEstados; i++){
        if(cm.estados[i][0] == anterior && cm.estados[i][1] == actual){
            cm.transiciones[i]++;
            return;
        }else if(cm.estados[i][0] == '\0'){
            break;
        }
    }
    
    cm.estados[i][0] = anterior;
    cm.estados[i][1] = actual;
    cm.transiciones[i]++;
}

/*
* Esta función se encarga de leer el archivo de entrada caracter por caracter e ir aumentando el 
* contador de cada una de las transiciones
*/
void CadenaMarkov::lecturaArchivo(){
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
                findPosicion(anterior, actual);
                anterior = actual;
            }
            cadena[i] = '\0';
        }
    }
    fe.close();
}

/*
* Esta función se encarga de escribir en el archivo de salida los valores de porcentaje
* que presenta cada una de las trnasiciones respecto al archivo de entrada
*/
void CadenaMarkov::escrituraArchivo(){
    // Crea un fichero de salida
    ofstream fs(archivodesalida); 
    
    char est[numerodeestados] = {'\0'};
    int total[numerodeestados] = {0};
    
    for(int i=0; i < numeroTotalEstados; i++){
        for(int j=0; j < numerodeestados; j++){
            if(est[j] == '\0'){
                est[j] = cm.estados[i][0];
                break;
            }else if(est[j] == cm.estados[i][0]){
                break;
            }
        }
        
        for(int j=0; j < numerodeestados; j++){
            if(est[j] == cm.estados[i][0]){
                total[j] = cm.transiciones[i] + total[j];
            }
        }
    }
    
    // Enviamos una cadena al fichero de salida:
    int encontro;
    for(int p=0; p < numerodeestados; p++){
        for(int x=0; x < numerodeestados; x++){
            encontro = 0;
            for(int i=0; i < numeroTotalEstados; i++){
                if(cm.estados[i][0] == est[p] && cm.estados[i][1] == est[x]){
                    fs << cm.estados[i][0] << "->" << cm.estados[i][1] << ": " << ((float)cm.transiciones[i]/(float)total[p]) << endl;
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