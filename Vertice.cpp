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

	for (int i = 0; i < this->cabos.size(); i++)
		if (this->cabos[i].retIdDestino() == destino)
			return &this->cabos[i];

	return nullptr;
}

Cabo* Vertice::retCabo_pos(int pos) { return &this->cabos[pos]; }

void Vertice::adCabo(Cabo novo) {

	if(this->retCabo(novo.retIdDestino()) == nullptr)
		this->cabos.push_back(novo);
}

void Vertice::removeCabo(int id) {

	for (int i = 0; i < this->cabos.size(); i++) {
		if (this->cabos[i].retIdDestino() == id) {
			this->cabos.erase(this->cabos.begin() + i);
		}
	}
}

int Vertice::grauVertice() { return this->cabos.size(); }
bool Vertice::eGerador() { return this->gerador; }
int Vertice::retId() { return this->id; }
int Vertice::retConsumo() { return this->consumo; }
int Vertice::retDeficit() { return (this->demanda - this->consumo); }
void Vertice::def_energiaLivre() { this->energiaLivre += this->consumo - this->demanda; }
int Vertice::ret_energiaLivre() { return this->energiaLivre; }
void Vertice::remove_energiaLivre(int quant) { this->energiaLivre -= quant; }
bool Vertice::operator==(const Vertice& other) const { return (this->id == other.id); }
int Vertice::retDemanda() { return this->demanda; }
void Vertice::def_energiaLivre(int valor) { this->energiaLivre = valor; }

void Vertice::normalizaConsumo() {
	if (this->consumo > this->demanda) {
		this->def_energiaLivre();
		this->consumo = this->demanda;
	}
}

void Vertice::defConsumo(int consumo) {
	this->consumo = consumo;
	this->normalizaConsumo();
}

void Vertice::adConsumo(int consumo) {
	this->consumo += consumo;
	this->normalizaConsumo();
}

int Vertice::energiaTotal() { return this->consumo; }

void Vertice::cabosCriticos(std::vector<Cabo>& cabosCriticos) {

	for (int i = 0; i < this->cabos.size(); i++)
		if (this->cabos[i].lotado())
			cabosCriticos.push_back(this->cabos[i]);
}

void Vertice::print() {

	std::cout << "Vertice " << this->id << ": " << this->consumo << "/" << this->demanda << std::endl;

	for (int i = 0; i < this->cabos.size(); i++) {
		this->cabos[i].print();
	}
}
