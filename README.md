# Lab5simulacion

### Compilar Orientado a Objetos

Para compilar cada uno de los modulos por separado.

```sh
$ g++ buildmc.cc CadenaMarkov.cc -o buildcm
$ g++ pimc.cc MatrizEstacionaria.cc `pkg-config --cflags --libs gsl` -std=c++11 -o pimc
$ g++ probmc.cc ProbabilidadCadena.cc `pkg-config --cflags --libs gsl` -std=c++11 -o probmc
```

