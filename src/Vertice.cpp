#include "Vertice.h"
#include "Cabo.h"

#include <iostream>

Vertice::Vertice(int id, int demanda) {

	this->id = id;
	this->demanda = demanda;
	demanda == 0 ? this->gerador = true : this->gerador = false;
	this->consumo = 0;
	this->energiaLivre = 0;
}

Cabo* Vertice::retCabo(int destino) {	// retorna o cabo cujo idDestino == destino

	for (auto& cabo : this->cabos)
		if (cabo.retIdDestino() == destino)
			return &cabo;

	//for (int i = 0; i < this->cabos.size(); i++)
	//	if (this->cabos[i].retIdDestino() == destino)
	//		return &this->cabos[i];

	return nullptr;
}

Cabo* Vertice::retCabo_pos(int pos) { return &this->cabos[pos]; } // retorna o cabo cujo cabos[pos]

void Vertice::adCabo(Cabo novo) {	// adiciona um cabo

	if (this->retCabo(novo.retIdDestino()) == nullptr)
		this->cabos.push_back(novo);
}

void Vertice::removeCabo(int id) {	// remove cabo cujo idDestino == id

	for (size_t i = 0; i < this->cabos.size(); i++) {
		if (this->cabos[i].retIdDestino() == id) {
			this->cabos.erase(this->cabos.begin() + (int)i);
		}
	}
}

void Vertice::adConsumo(int consumo) { this->consumo += consumo; }	// adiciona ao valor atual do consumo de energia

void Vertice::cabosCriticos(std::vector<Cabo>& cabosCriticos) {	// retorna os cabos criticos

	for (auto& cabo : this->cabos)
		if (cabo.lotado())
			cabosCriticos.push_back(cabo);

	//for (int i = 0; i < this->cabos.size(); i++)
	//	if (this->cabos[i].lotado())
	//		cabosCriticos.push_back(this->cabos[i]);
}

void Vertice::print() {

	std::cout << "Vertice " << this->id << ": " << this->consumo << "/" << this->demanda << std::endl;

	for (auto& cabo : this->cabos)
		cabo.print();

	//for (int i = 0; i < this->cabos.size(); i++) {
	//	this->cabos[i].print();
	//}
}

int Vertice::grauVertice() { return (int)this->cabos.size(); }	// retorna o grau de saida do vertice
int Vertice::retId() { return this->id; }	// retorna id
int Vertice::retConsumo() { return this->consumo; }	// retorna  o consumo
int Vertice::retDeficit() { return (this->demanda - this->consumo); }	// retorna o deficit (consumo - demanda)
int Vertice::retDemanda() { return this->demanda; }	// retorna a demanda

int Vertice::capSaida() { // retorna a capacidade de saida (geradores)

	int total = 0;

	for (auto& cabo : this->cabos)
		total += cabo.retCap();

	//for (size_t i = 0; i < this->cabos.size(); i++)
	//	total += this->cabos[i].retCap();

	return total;
}

bool Vertice::eGerador() { return this->gerador; }	// retorna se o vertice e um gerador 
bool Vertice::operator==(const Vertice& other) const { return (this->id == other.id); }