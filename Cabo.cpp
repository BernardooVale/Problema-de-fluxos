#include <iostream>

#include "Cabo.h"

Cabo::Cabo(int idOrigem, int idDestino, int cap) {

	this->idDestino = idDestino;
	this->cap = cap;
	this->idOrigem = idOrigem;
	this->corrente = 0;
}

void Cabo::normalizaCorrente() {
	if (this->corrente > this->cap) {
		this->corrente = this->cap;
	}
}

void Cabo::defCorrente(int corrente) {
	this->corrente = corrente; 
	this->normalizaCorrente();
}
void Cabo::adCorrente(int corrente) {
	this->corrente += corrente; 
	this->normalizaCorrente();
}

int Cabo::retCorrente() { return this->corrente; }
int Cabo::retIdDestino() { return this->idDestino; }
bool Cabo::lotado() { return (this->corrente == this->cap ? true : false); }
int Cabo::retCap() { return this->cap; }
int Cabo::ret_capDisponivel() { return this->cap - this->corrente; }
int Cabo::retIdOrigem() { return this->idOrigem; }

void Cabo::print() {
	std::cout << this->idOrigem << " " << this->idDestino << " " /* << this->corrente << "/" */<< this->cap << std::endl;
}