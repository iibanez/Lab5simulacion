#include "MatrizEstacionaria.hh"


int main(){
    
    std::string archivodeentrada = "cadenademarkov.txt";
    std::string archivodesalida = "cadenaestacionaria.txt";
    
    MatrizEstacionaria me(archivodeentrada, archivodesalida);

    me.lecturaArchivo();

    me.solucionSistema();

    me.escrituraArchivo();
  
    return 0;
}
