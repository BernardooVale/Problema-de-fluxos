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


void Cabo::adCorrente(int corrente) { this->corrente += corrente; }				// adiciona ao valor atual da corrente

int Cabo::retCorrente() { return this->corrente; }								// retorna corrente
int Cabo::retIdDestino() { return this->idDestino; }							// retorna id destino
int Cabo::retCap() { return this->cap; }										// retorna a capacidade
int Cabo::ret_capDisponivel() { return this->cap - this->corrente; }			// retorna cap - corrente
int Cabo::retIdOrigem() { return this->idOrigem; }								// retorna id origem

bool Cabo::lotado() { return (this->corrente == this->cap ? true : false); }	// retorna corrente == cap ?
bool Cabo::eInverso() { return this->inverso; }									// retorna inverso ?

void Cabo::print() {
	std::cout << this->idOrigem << " -> " << this->idDestino << " " /* << this->corrente << "/" */ << this->corrente << "/" << this->cap << std::endl;
}