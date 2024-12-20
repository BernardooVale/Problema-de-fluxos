#include <vector>
#include <queue>
#include <iostream>
#include <stack>

#include "Grafo.h"
#include "Cabo.h"
#include "Vertice.h"

Grafo::Grafo() {}

Vertice* Grafo::retVertice(int id) {

	for (auto& vertice : this->vertices)
		if (vertice.retId() == id)
			return &vertice;

	return nullptr;

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	if (this->vertices[i].retId() == id)
	//		return &this->vertices[i];
	//
	//return nullptr;
}

int Grafo::retPos(Vertice atual) {

	for (size_t i = 0; i < this->vertices.size(); i++)
		if (atual == this->vertices[i])
			return (int)i;

	return -1;
}

void Grafo::adVertice(Vertice novo) {

	if (this->retVertice(novo.retId()) == nullptr) {
		this->vertices.push_back(novo);
	}
}

int Grafo::retTam() { return (int)this->vertices.size(); }

int Grafo::energiaTotal() {

	int total = 0;

	for (auto& vertice : this->vertices)
		total += vertice.energiaTotal();

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	total += this->vertices[i].energiaTotal();

	return total;
}

int Grafo::deficit() {

	int total = 0;

	for (auto& vertice : this->vertices)
		total += vertice.retDeficit();

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	total += this->vertices[i].retDeficit();

	return total;
}

int Grafo::excesso(int eTotal) {

	int total = 0;

	for (size_t i = 0; i < this->vertices.size(); i++) {
		Vertice* atual = &this->vertices[i];

		if (atual->eGerador()) {
			total += atual->capSaida();
		}
	}

	return (total - eTotal);
}

bool comp(Cabo x, Cabo y) {

	return x.retCap() > y.retCap();
}

void Grafo::cabosCriticos() {

	std::vector<Cabo> cabosCriticos;

	for (auto& vertice : this->vertices)
		vertice.cabosCriticos(cabosCriticos);

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	this->vertices[i].cabosCriticos(cabosCriticos);

	std::sort(cabosCriticos.begin(), cabosCriticos.end(), comp);
	
	std::cout << cabosCriticos.size() << std::endl;

	for (auto& cabo : cabosCriticos)
		cabo.print();

	//for (size_t i = 0; i < cabosCriticos.size(); i++)
	//	cabosCriticos[i].print();
}

void Grafo::print() {

	for (auto& vertice : this->vertices)
		vertice.print();

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	this->vertices[i].print();
}

void Grafo::normalizaInicio() {

	Vertice* inicio = this->retVertice(this->retTam() - 1);

	for (size_t i = 0; i < this->vertices.size(); i++) {
		Vertice atual = this->vertices[i];

		if (atual.eGerador()) {
			Cabo novo(inicio->retId(), atual.retId(), 0);
			inicio->adCabo(novo);
		}
	}
}

void Grafo::normalizaFim() { // adiciona um cabo entre todos os consumidores e o destino ficticio

	Vertice fim = *this->retVertice(this->retTam());

	for (size_t i = 0; i < this->vertices.size(); i++) {
		Vertice* atual = &this->vertices[i];

		if (!atual->eGerador() && atual->retDemanda() != -1) {
			Cabo novo(atual->retId(), fim.retId(), 0);
			atual->adCabo(novo);
		}
	}

}

void Grafo::removeInicioFim() { // remove os vertices de apoio

	Vertice* inicio = this->retVertice(this->retTam() - 1);
	Vertice* fim = this->retVertice(this->retTam());

	for (size_t i = 0; i < this->vertices.size(); i++) {
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

	for (size_t i = 0; i < caminho.size(); i++) {
		if (caminho[i]->ret_capDisponivel() < gargalo) {
			gargalo = caminho[i]->ret_capDisponivel();
			std::cout << "Capacidade disponivel: " << caminho[i]->ret_capDisponivel() << std::endl;
		}
	}

	Vertice* destFinal = this->retVertice(caminho[caminho.size() - 1]->retIdDestino());

	if (destFinal->retDeficit() < gargalo)
		gargalo = destFinal->retDeficit();

	std::cout << "Gargalo: " << gargalo << std::endl;

	for (size_t i = 0; i < caminho.size(); i++) {
		Cabo* cabo = caminho[i];
		Vertice* destino = this->retVertice(cabo->retIdDestino());

		cabo->adCorrente(gargalo);
		if (i == caminho.size() - 1) {
			destino->adConsumo(gargalo);
		}
	}
}

void Grafo::bfs(Vertice* inicio, Vertice fim, std::vector<Cabo*>& conexPais) {

	std::queue<Cabo*> fila; // fila de execucao
	int numVertices = (int)this->vertices.size();
	int idFinal = numVertices - 1;
	std::vector<bool> percorridos(numVertices, false); // vetor de percorridos para evitar ciclos

	Cabo* aux = new Cabo(-1, idFinal, 0); // cabo auxiliar so para iniciar o processo

	fila.push(aux);

	while (!fila.empty()) { // enquanto houver caminho na fila

		aux = fila.front();
		Vertice* atual = this->retVertice(aux->retIdDestino()); // pega o proximo vertice a ser percorrido
		std::cout << "Atual: " << atual->retId() << std::endl;
		fila.pop();

		if (!atual->eGerador() && atual->retId() != idFinal) { // se o atual nao for gerador nem o destino
			conexPais[atual->retId() - 1] = aux;
		}
		percorridos[atual->retId() - 1] = true; // atual foi percorrido

		for (size_t i = 0; i < atual->grauVertice(); i++) { // para todos as arestas

			Cabo* cabo = atual->retCabo_pos((int)i); // proximo cabo

			std::cout << "ID destino: " << cabo->retIdDestino() << std::endl;

			Vertice* destino = this->retVertice(cabo->retIdDestino()); // vertice destino do cabo

			if (*destino == fim && atual->retDeficit() != 0) { // se o proximo for o ponto ficticio final e o atual puder receber energia

				std::cout << "Destino ficticio" << std::endl;
				conexPais[destino->retId() - 1] = cabo; // adiciona o cabo como ancestral do destino
				return;
			}

			if ((!percorridos[destino->retId() - 1] && !cabo->lotado()) || atual->retDemanda() == -1) { // (se o proximo nao for percorrido e o cabo nao estiver lotado) ou atual for ficticio

				std::cout << "Proximo vertice" << std::endl;
				fila.push(cabo); // adiciona o cabo na fila de execucao
			}
		}
	}

	return;
}

void Grafo::bfs(Vertice* inicio, Vertice fim, std::vector<Cabo*>& conexPais) {

	std::queue<Cabo*> fila; // fila de execucao
	int numVertices = (int)this->vertices.size();
	int idFinal = numVertices - 1;
	std::vector<bool> percorridos(numVertices, false); // vetor de percorridos para evitar ciclos

	Cabo* aux = new Cabo(-1, idFinal, 0); // cabo auxiliar so para iniciar o processo

	fila.push(aux);

	while (!fila.empty()) { // enquanto houver caminho na fila

		aux = fila.front();
		Vertice* atual = this->retVertice(aux->retIdDestino()); // pega o proximo vertice a ser percorrido
		std::cout << "Atual: " << atual->retId() << std::endl;
		fila.pop();

		if (!atual->eGerador() && atual->retId() != idFinal) { // se o atual nao for gerador nem o destino
			conexPais[atual->retId() - 1] = aux;
		}
		percorridos[atual->retId() - 1] = true; // atual foi percorrido

		for (size_t i = 0; i < atual->grauVertice(); i++) { // para todos as arestas

			Cabo* cabo = atual->retCabo_pos((int)i); // proximo cabo

			std::cout << "ID destino: " << cabo->retIdDestino() << std::endl;

			Vertice* destino = this->retVertice(cabo->retIdDestino()); // vertice destino do cabo

			if (*destino == fim && atual->retDeficit() != 0) { // se o proximo for o ponto ficticio final e o atual puder receber energia

				std::cout << "Destino ficticio" << std::endl;
				conexPais[destino->retId() - 1] = cabo; // adiciona o cabo como ancestral do destino
				return;
			}

			if ((!percorridos[destino->retId() - 1] && !cabo->lotado()) || atual->retDemanda() == -1) { // (se o proximo nao for percorrido e o cabo nao estiver lotado) ou atual for ficticio

				std::cout << "Proximo vertice" << std::endl;
				fila.push(cabo); // adiciona o cabo na fila de execucao
			}
		}
	}

	return;
}

/*
void Grafo::bfs(Vertice* inicio, Vertice fim, vector<Cabo*>& conexPais) {

	std::queue<Vertice*> fila;
	std::vector<bool> percorridos((int)this->vertices.size(), false);
	
	fila.push(inicio);

	while (!fila.empty()){

		Vertice* atual = fila.front();
		std::cout << "Atual: " << atual->retId() << std::endl;
		fila.pop();

		percorridos[atual->retId() - 1] = true;

		for (size_t i = 0; i < atual->grauVertice(); i++) { // para todos as arestas

			Cabo* cabo = atual->retCabo_pos((int)i);

			std::cout << "ID destino: " << cabo->retIdDestino() << std::endl;

			Vertice* destino = this->retVertice(cabo->retIdDestino());

			if (*destino == fim && atual->retDeficit() != 0) { // se o proximo for o ponto ficticio final

				std::cout << "Destino ficticio" << std::endl;

				conexPais[destino->retId() - 1] = cabo;
				return;
			}

			if ((!percorridos[destino->retId() - 1] && !cabo->lotado())) { // se o proximo nao for percorrido e o cabo nao estiver lotado

				std::cout << "Proximo vertice" << std::endl;

				fila.push(destino);
				conexPais[destino->retId() - 1] = cabo;
			}
			else if (atual->retDemanda() == -1) { // se o atual for o ponto ficticio inicial

				std::cout << "Atual era ponto ficticio" << std::endl;

				fila.push(destino);
			}
		}
	}

	return;
}
*/
void Grafo::edmonsKarp() {

	Vertice* inicio = &this->vertices[this->retTam() - 2];
	Vertice* fim = &this->vertices[this->retTam() - 1];
	int gargalo;

	while(true){
		std::vector<Cabo*> conexPais((int)this->vertices.size(), nullptr);

		this->bfs(inicio, *fim, conexPais); // pega o caminho

		if(conexPais[fim->retId() - 1] != nullptr) {
			std::stack<Cabo*> caminho;

			Vertice* destino = fim;
			Cabo* cabo = conexPais[destino->retId() - 1];
			Vertice* origem = this->retVertice(cabo->retIdOrigem());
			gargalo = origem->retDeficit();

			std::cout << "Ultimo vertice: " << origem->retId() << std::endl;
			std::cout << "Energia que falta: " << origem->retDeficit() << std::endl;

			while (conexPais[origem->retId() - 1] != nullptr) { // enquanto nao chegar no primeiro

				destino = origem;
				cabo = conexPais[destino->retId() - 1];
				origem = this->retVertice(cabo->retIdOrigem());

				std::cout << "Origem: " << origem->retId() << std::endl;
				std::cout << "Destino: " << destino->retId() << std::endl;

				caminho.push(cabo);

				std::cout << "Cabo: " << cabo->retIdOrigem() << " -> " << cabo->retIdDestino() << ": " << cabo->retCorrente() << "/" << cabo->retCap() << std::endl;

				if (cabo->ret_capDisponivel() < gargalo) { // acha o gargalo
					gargalo = cabo->ret_capDisponivel();
				}
			}

			while (!caminho.empty()) {
				cabo = caminho.top();
				caminho.pop();
				cabo->adCorrente(gargalo);
				std::cout << "Cabo: " << cabo->retIdOrigem() << " -> " << cabo->retIdDestino() << ": " << cabo->retCorrente() << "/" << cabo->retCap() << std::endl;
				if (caminho.size() == 0) {
					std::cout << "Id do ultimo: " << this->retVertice(cabo->retIdDestino())->retId() << std::endl;
					this->retVertice(cabo->retIdDestino())->adConsumo(gargalo);
				}
			}
		}
		if (conexPais[fim->retId() - 1] == nullptr) {
			break;
		}
	}
}

void Grafo::dfs(Vertice* atual, Vertice* fim, std::vector<Cabo*> caminho, std::vector<bool> percorridos) {

	percorridos[atual->retId() - 1] = true;

	for (int i = 0; i < atual->grauVertice(); i++) {

		Cabo* cabo = atual->retCabo_pos(i);
		Vertice* prox = this->retVertice(cabo->retIdDestino());

		if (!percorridos[prox->retId() - 1]) {

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