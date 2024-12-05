#include <vector>
#include <queue>
#include <iostream>

#include "Grafo.h"
#include "Cabo.h"
#include "Vertice.h"

Grafo::Grafo(){}

Vertice* Grafo::retVertice(int id) {

	for (int i = 0; i < this->vertices.size(); i++)
		if (this->vertices[i].retId() == id)
			return &this->vertices[i];

	return nullptr;
}

int Grafo::retPos(Vertice atual) {

	for (int i = 0; i < this->vertices.size(); i++)
		if (atual == this->vertices[i])
			return i;
}

void Grafo::adVertice(Vertice novo) {

	if (this->retVertice(novo.retId()) == nullptr) {
		this->vertices.push_back(novo);
	}
}

int Grafo::retTam() { return this->vertices.size(); }

int Grafo::energiaTotal() {

	int total = 0;

	for (int i = 0; i < this->vertices.size(); i++)
		total += this->vertices[i].energiaTotal();

	return total;
}

int Grafo::deficit() {

	int total = 0;

	for (int i = 0; i < this->vertices.size(); i++)
		total += this->vertices[i].retDeficit();

	return total;
}

int Grafo::excesso() {

	int total = 0;

	for (int i = 0; i < this->vertices.size(); i++)
		total += this->vertices[i].ret_energiaLivre();

	return total;
}

void Grafo::cabosCriticos() {

	std::vector<Cabo> cabosCriticos;

	for (int i = 0; i < this->vertices.size(); i++)
		this->vertices[i].cabosCriticos(cabosCriticos);

	for (int i = 0; i < cabosCriticos.size(); i++)
		cabosCriticos[i].print();
}

void Grafo::print() {

	for (int i = 0; i < this->vertices.size(); i++)
		this->vertices[i].print();
}

void Grafo::normalizaInicio() {

	Vertice* inicio = this->retVertice(this->retTam() - 1);

	for (int i = 0; i < this->vertices.size(); i++) {
		Vertice atual = this->vertices[i];

		if(atual.eGerador()){
			Cabo novo(inicio->retId(), atual.retId(), 0);
			inicio->adCabo(novo);
		}
	}
}

void Grafo::normalizaFim() {

	Vertice fim = *this->retVertice(this->retTam());

	for (int i = 0; i < this->vertices.size(); i++) {
		Vertice* atual = &this->vertices[i];

		if (!atual->eGerador() && atual->retDemanda() != -1) {
			Cabo novo(atual->retId(), fim.retId(), 0);
			atual->adCabo(novo);
		}
	}

}

void Grafo::removeInicioFim() {

	Vertice* inicio = this->retVertice(this->retTam() -1);
	Vertice* fim = this->retVertice(this->retTam());

	for (int i = 0; i < this->vertices.size(); i++) {
		Vertice* atual = &this->vertices[i];
		if (!atual->eGerador()) {
			atual->removeCabo(fim->retId());
		}
	}
	this->vertices.erase(find(this->vertices.begin(), this->vertices.end(), *inicio)); // tira inicio
	this->vertices.erase(find(this->vertices.begin(), this->vertices.end(), *fim)); // tira fim
}


void Grafo::fordFulk(std::vector<Cabo*> caminho) {

	int gargalo = INT_MAX;

	for (int i = 0; i < caminho.size(); i++) {
		if (caminho[i]->ret_capDisponivel() < gargalo){
			gargalo = caminho[i]->ret_capDisponivel();
			std::cout << "Capacidade disponivel: " << caminho[i]->ret_capDisponivel() << std::endl;
		}
	}

	Vertice* destFinal = this->retVertice(caminho[caminho.size() - 1]->retIdDestino());

	if (destFinal->retDeficit() < gargalo)
		gargalo = destFinal->retDeficit();

	std::cout << "Gargalo: " << gargalo << std::endl;

	for (int i = 0; i < caminho.size(); i++) {
		Cabo* cabo = caminho[i];
		Vertice* destino = this->retVertice(cabo->retIdDestino());

		cabo->adCorrente(gargalo);
		if(i == caminho.size() - 1){
			destino->adConsumo(gargalo);
		}
	}
}

void Grafo::dfs(Vertice* atual, Vertice* fim, std::vector<Cabo*> caminho, std::vector<bool> percorridos) {

	percorridos[atual->retId() - 1] = true;

	for (int i = 0; i < atual->grauVertice(); i++) {

		Cabo* cabo = atual->retCabo_pos(i);
		Vertice* prox = this->retVertice(cabo->retIdDestino());

		if(!percorridos[prox->retId() - 1]) {

			std::cout << "Origem do cabo e destino " << cabo->retIdOrigem() << " " << cabo->retIdDestino() << std::endl;
			std::cout << "Id do prox " << prox->retId() << std::endl;

			if (atual->retDemanda() == -1) { // ponto ficticio inicial
				this->dfs(prox, fim, caminho, percorridos);

			}
			else if (prox == fim) { // proximo e o ponto ficticio final (chegamos no destino
				this->fordFulk(caminho);

			}
			else if (!prox->eGerador()) { // se o atual e o proximo forem pontos validos
				caminho.push_back(cabo);
				this->dfs(prox, fim, caminho, percorridos);
				caminho.pop_back();
				percorridos[prox->retId() - 1] = false;
			}
		}
	}
}

void Grafo::preencheRede() {

	Vertice* inicio = &this->vertices[this->retTam() - 2];
	Vertice* fim = &this->vertices[this->retTam() - 1];
	std::vector<Cabo*> caminho;
	std::vector<bool> percorridos(this->vertices.size(), false);

	this->dfs(inicio, fim, caminho, percorridos);
}