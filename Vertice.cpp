#include "Vertice.h"

#include <iostream>

Vertice::Vertice(int id, int demanda) {

	this->id = id;
	this->demanda = demanda;
	demanda == 0 ? this->gerador = true : this->gerador = false;
	this->consumo = 0;
	this->energiaLivre = 0;
}

Cabo* Vertice::retCabo(int destino) {

	for (auto& cabo : this->cabos)
		if (cabo.retIdDestino() == destino)
			return &cabo;

	//for (int i = 0; i < this->cabos.size(); i++)
	//	if (this->cabos[i].retIdDestino() == destino)
	//		return &this->cabos[i];

	return nullptr;
}

Cabo* Vertice::retCabo_pos(int pos) { return &this->cabos[pos]; }

void Vertice::adCabo(Cabo novo) {

	if (this->retCabo(novo.retIdDestino()) == nullptr)
		this->cabos.push_back(novo);
}

void Vertice::removeCabo(int id) {

	for (size_t i = 0; i < this->cabos.size(); i++) {
		if (this->cabos[i].retIdDestino() == id) {
			this->cabos.erase(this->cabos.begin() + (int)i);
		}
	}
}

void Vertice::adConsumo(int consumo) { this->consumo += consumo; }

void Vertice::cabosCriticos(std::vector<Cabo>& cabosCriticos) {

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

int Vertice::grauVertice() { return (int)this->cabos.size(); }
int Vertice::retId() { return this->id; }
int Vertice::retConsumo() { return this->consumo; }
int Vertice::retDeficit() { return (this->demanda - this->consumo); }
int Vertice::retDemanda() { return this->demanda; }
int Vertice::energiaTotal() { return this->consumo; }

int Vertice::capSaida() {

	int total = 0;

	for (auto& cabo : this->cabos)
		total += cabo.retCap();

	//for (size_t i = 0; i < this->cabos.size(); i++)
	//	total += this->cabos[i].retCap();

	return total;
}

bool Vertice::eGerador() { return this->gerador; }
bool Vertice::operator==(const Vertice& other) const { return (this->id == other.id); }