PATH = /OO
CC = g++
CFLAGS = `pkg-config --cflags --libs gsl`
OPTION = -std=c++11

buildmc :
	$(CC) buildmc.cc CadenaMarkov.cc $(CFLAGS) $(OPTION) -o buildmc

pimc :
	$(CC) pimc.cc MatrizEstacionaria.cc $(CFLAGS) $(OPTION) -o pimc

probmc :
	$(CC) probmc.cc ProbabilidadCadena.cc -o $(CFLAGS) $(OPTION) probmc

all: buildmc pimc probmc

clean: \rm *.o *~ p1

