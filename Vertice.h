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
	int grauVertice(); // retorna o grau de saida do vertice
	bool eGerador(); // retorna se o vertice e um gerador 
	int retId(); // retorna id
	void defConsumo(int consumo); // define o consumo de energia
	void adConsumo(int consumo); // adiciona ao valor atual do consumo de energia
	void normalizaConsumo(); // funcao interna para caso o consumo(energia entrando) seja maior que a demanda 
	int retConsumo(); // retorna  o consumo
	int retDeficit(); // retorna o deficit (consumo - demanda)
	int energiaTotal(); // retorna a quantidade de energia que passa pelos cabos de saida
	void def_energiaLivre(); // funcao interna para armazenar o energia em excesso (consumo - demanda, caso esse valor seja maior que 0)
	int ret_energiaLivre(); // retorna a energia nao utilizada
	void remove_energiaLivre(int quant); // passa a energia armazenada para os cabos
	void cabosCriticos(vector<Cabo>& cabosCriticos);
	Cabo* retCabo(int destino);
	void print();
	bool operator==(const Vertice& outro) const;
	int retDemanda();
	void def_energiaLivre(int valor);
	Cabo* retCabo_pos(int pos);
	int capSaida();
};

#endif
