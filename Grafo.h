#ifndef Grafo_HPP
#define Grafo_HPP

#include <vector>

#include "Cabo.h"
#include "Vertice.h"

using namespace std;

class Grafo {

private:

	vector<Vertice> vertices;

public:

	Grafo();

	void adVertice(Vertice novo);
	void cabosCriticos();
	void print();
	void normalizaInicio(); // adiciona um cabo entre o ponto ficticio de inicio ate todos os geradores
	void normalizaFim(); // adiciona um cabo entre todos os consumidores e o ponto ficticio de fim
	void removeInicioFim(); // remove os pontos de inicio e fim para nao interferir no calculo
	void bfs(Vertice* atual, Vertice fim, vector<Cabo*>& conexPais);
	void edmonsKarp();

	int energiaTotal();
	int deficit();
	int excesso(int eTotal);
	int retPos(Vertice atual);
	int retTam();

	Vertice* retVertice(int id);
};

#endif

