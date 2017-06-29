all: buildmc pimc probmc

buildmc :
	g++ OO/buildmc.cc OO/CadenaMarkov.cc -o bin/buildcm

pimc :
	$ g++ OO/pimc.cc OO/MatrizEstacionaria.cc `pkg-config --cflags --libs gsl` -std=c++11 -o bin/pimc

probmc :
	g++ OO/probmc.cc OO/ProbabilidadCadena.cc `pkg-config --cflags --libs gsl` -std=c++11 -o bin/probmc

clean: 
	\rm bin/probmc bin/pimc bin/buildmc



