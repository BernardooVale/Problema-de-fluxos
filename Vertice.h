#ifndef Vertice_HPP
#define Vertice_HPP

#include <vector>
#include "Cabo.h"

using namespace std;

class Vertice {

private:

	int id, demanda, consumo, energiaLivre;
	bool gerador;
	vector<Cabo> cabos;

public:

	Vertice(int id, int demanda);

	void adCabo(Cabo novo); // adiciona um cabo
	void removeCabo(int id);
	void adConsumo(int consumo); // adiciona ao valor atual do consumo de energia
	void cabosCriticos(vector<Cabo>& cabosCriticos);
	void print();

	int grauVertice(); // retorna o grau de saida do vertice
	int retId(); // retorna id
	int retConsumo(); // retorna  o consumo
	int retDeficit(); // retorna o deficit (consumo - demanda)
	int energiaTotal(); // retorna a quantidade de energia que passa pelos cabos de saida
	int retDemanda();
	int capSaida();

	bool eGerador(); // retorna se o vertice e um gerador 
	bool operator==(const Vertice& outro) const;

	Cabo* retCabo(int destino);
	Cabo* retCabo_pos(int pos);
};

#endif
