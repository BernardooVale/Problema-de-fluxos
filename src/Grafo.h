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

	void adVertice(Vertice novo);	// adiciona um vertice
	void cabosCriticos();	// pega todos os cabos criticos
	void print();
	void normalizaInicio();	// adiciona um cabo entre o ponto ficticio de inicio ate todos os geradores
	void normalizaFim();	// adiciona um cabo entre todos os consumidores e o ponto ficticio de fim
	void removeInicioFim();	// remove os pontos de inicio e fim para nao interferir no calculo
	void bfs(Vertice* atual, Vertice fim, vector<Cabo*>& conexPais);
	void edmonsKarp();

	int energiaTotal(); // calcula a energia dentro do sistema
	int deficit();	// calcula o defict do sistema
	int excesso(int eTotal); // retorna o excesso do sistema
	int retPos(Vertice atual); // retorna a posicao de Vertice atual dentro de this.vertices 
	int retTam();	// retorna o tamanho do vertor de vertices

	Vertice* retVertice(int id); // retorna o vertice cujo id ==id
};

#endif

