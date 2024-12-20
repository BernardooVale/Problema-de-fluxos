#include <iostream>

#include "Cabo.h"

Cabo::Cabo(int idOrigem, int idDestino, int cap, bool inverso){

	this->idDestino = idDestino;
	this->cap = cap;
	this->idOrigem = idOrigem;
	this->corrente = 0;
	this->inverso = inverso;
}

Cabo::Cabo(int idOrigem, int idDestino, int cap) {

	this->idDestino = idDestino;
	this->cap = cap;
	this->idOrigem = idOrigem;
	this->corrente = 0;
	this->inverso = false;
}


void Cabo::adCorrente(int corrente) { this->corrente += corrente; }

int Cabo::retCorrente() { return this->corrente; }
int Cabo::retIdDestino() { return this->idDestino; }
int Cabo::retCap() { return this->cap; }
int Cabo::ret_capDisponivel() { return this->cap - this->corrente; }
int Cabo::retIdOrigem() { return this->idOrigem; }

bool Cabo::lotado() { return (this->corrente == this->cap ? true : false); }
bool Cabo::eInverso() { return this->inverso; }

void Cabo::print() {
	std::cout << this->idOrigem << " -> " << this->idDestino << " " /* << this->corrente << "/" */ << this->corrente << "/" << this->cap << std::endl;
}