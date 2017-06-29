# Lab5simulacion

### Compilar

Para compilar cada uno de los modulos por separado.

```sh
$ g++ buildmc.cc CadenaMarkov.cc -o buildcm
$ g++ pimc.cc MatrizEstacionaria.cc `pkg-config --cflags --libs gsl` -std=c++11 -o pimc
$ g++ probmc.cc ProbabilidadCadena.cc `pkg-config --cflags --libs gsl` -std=c++11 -o probmc
```
Para compilar todos los modulos con makefile.

```sh
$  make all
```

