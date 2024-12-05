#ifndef Grafo_HPP
#define Grafo_HPP

#include <vector>

#include "Cabo.h"
#include "Vertice.h"

using namespace std;

class Grafo{

private:

	vector<Vertice> vertices;

public:

	Grafo();

	void adVertice(Vertice novo);
	Vertice* retVertice(int id);
	int energiaTotal();
	int deficit();
	int excesso();
	void cabosCriticos();
	void print();
	void normalizaInicio(); // adiciona um cabo entre o ponto ficticio de inicio ate todos os geradores
	void normalizaFim(); // adiciona um cabo entre todos os consumidores e o ponto ficticio de fim
	void removeInicioFim(); // remove os pontos de inicio e fim para nao interferir no calculo
	int retPos(Vertice atual);
	int retTam();
	void preencheRede();
	void dfs(Vertice* atual, Vertice* fim, vector<Cabo*> caminho, vector<bool> percorridos);
	void fordFulk(vector<Cabo*> caminho);
};

#endif

