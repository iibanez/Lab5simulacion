# Lab5simulacion

## compilar archivos

g++ -lgsl -lgslcblas -lm pimc.cpp -o pimc

g++ buildmc.cpp -o buildmc 

## Compilar Orientado a Objetos

g++ buildmc.cc CadenaMarkov.cc -o buildcm
g++ pimc.cc MatrizEstacionaria.cc `pkg-config --cflags --libs gsl` -std=c++11 -o pimc
