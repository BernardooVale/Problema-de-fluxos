#include <vector>
#include <queue>
#include <iostream>
#include <stack>

#include "Grafo.h"
#include "Cabo.h"
#include "Vertice.h"

Grafo::Grafo() {}

Vertice* Grafo::retVertice(int id) {	// retorna o vertice cujo id ==id

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

void Grafo::adVertice(Vertice novo) {	// adiciona um vertice

	if (this->retVertice(novo.retId()) == nullptr) {
		this->vertices.push_back(novo);
	}
}

bool comp(Cabo x, Cabo y) { return x.retCap() > y.retCap(); }	// funcao interna para std::sort

void Grafo::cabosCriticos() {	// pega todos os cabos criticos

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

void Grafo::normalizaInicio() {	// adiciona um cabo entre o ponto ficticio de inicio ate todos os geradores

	Vertice* inicio = this->retVertice(this->retTam() - 1);

	for (int i = 0; i < this->retTam(); i++) {
		Vertice atual = this->vertices[i];

		if (atual.eGerador()) {
			Cabo novo(inicio->retId(), atual.retId(), 0);
			inicio->adCabo(novo);
		}
	}
}

void Grafo::normalizaFim() { // adiciona um cabo entre todos os consumidores e o destino ficticio

	Vertice fim = *this->retVertice(this->retTam());

	for (int i = 0; i < this->retTam(); i++) {
		Vertice* atual = &this->vertices[i];

		if (!atual->eGerador() && atual->retDemanda() != -1) {
			Cabo novo(atual->retId(), fim.retId(), 0);
			atual->adCabo(novo);
		}
	}

}

void Grafo::removeInicioFim() { // remove os vertices de apoio e as respectivas arestas

	Vertice* inicio = this->retVertice(this->retTam() - 1);
	Vertice* fim = this->retVertice(this->retTam());

	for (int i = 0; i < this->retTam(); i++) {
		Vertice* atual = &this->vertices[i];
		if (!atual->eGerador()) {
			atual->removeCabo(fim->retId());
		}
	}
	this->vertices.erase(find(this->vertices.begin(), this->vertices.end(), *inicio)); // tira inicio
	this->vertices.erase(find(this->vertices.begin(), this->vertices.end(), *fim)); // tira fim
}

int Grafo::retPos(Vertice atual) {	// retorna a posicao de Vertice atual dentro de this.vertices 

	for (int i = 0; i < this->retTam(); i++)
		if (atual == this->vertices[i])
			return i;

	return -1;
}

int Grafo::retTam() { return (int)this->vertices.size(); }	// retorna o tamanho do vertor de vertices

int Grafo::energiaTotal() {	// calcula a energia dentro do sistema

	int total = 0;

	for (auto& vertice : this->vertices)
		total += vertice.retConsumo();

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	total += this->vertices[i].retConsumo();

	return total;
}

int Grafo::deficit() {	// calcula o defict do sistema

	int total = 0;

	for (auto& vertice : this->vertices)
		total += vertice.retDeficit();

	//for (size_t i = 0; i < this->vertices.size(); i++)
	//	total += this->vertices[i].retDeficit();

	return total;
}

int Grafo::excesso(int eTotal) {	// retorna o excesso do sistema

	int total = 0;

	for (int i = 0; i < this->retTam(); i++) {
		Vertice* atual = &this->vertices[i];

		if (atual->eGerador()) {
			total += atual->capSaida();
		}
	}

	return (total - eTotal);
}

struct estagiosCaminho {	// estrutura para guardar o historico de cada passo da bfs
	std::vector<Cabo*> conexHist;
	Cabo* prox = nullptr;
};

void Grafo::bfs(Vertice* inicio, Vertice fim, std::vector<Cabo*>& conexPais) {

	std::queue<estagiosCaminho> fila; // fila de execucao
	int numVertices = this->retTam(); 
	int idFinal = numVertices - 1;	// 
	std::vector<bool> percorridos(numVertices, false); // vetor de percorridos para evitar ciclos

	Cabo* aux = new Cabo(-1, idFinal, 0); // cabo auxiliar so para iniciar o processo
	estagiosCaminho estagios;	// inicializando a struct
	estagios.prox = aux;		// cabo do prox passo
	estagios.conexHist = conexPais;	// historico

	fila.push(estagios);

	while (!fila.empty()) { // enquanto houver caminho na fila

		aux = fila.front().prox;
		std::vector<Cabo*> conexHist = fila.front().conexHist;
		Vertice* atual = this->retVertice(aux->retIdDestino()); // pega o proximo vertice a ser percorrido
		std::cout << "Atual: " << atual->retId() << std::endl;
		fila.pop();

		if (!atual->eGerador() && atual->retId() != idFinal) { // se o atual nao for gerador nem o destino
			conexHist[atual->retId() - 1] = aux; // o ancestral de atual vai ser o cabo aux
		}
		percorridos[atual->retId() - 1] = true; // atual foi percorrido

		for (size_t i = 0; i < atual->grauVertice(); i++) { // para todos as arestas de atual

			Cabo* cabo = atual->retCabo_pos((int)i); // proximo cabo

			std::cout << "ID destino: " << cabo->retIdDestino() << std::endl;

			Vertice* destino = this->retVertice(cabo->retIdDestino()); // vertice destino do cabo

			if (*destino == fim && atual->retDeficit() != 0) { // se o proximo for o ponto ficticio final e o atual puder receber energia

				std::cout << "Destino ficticio" << std::endl;
				conexPais = conexHist;	// retorna o historico daquele caminho especifico
				conexPais[destino->retId() - 1] = cabo; // adiciona o cabo como ancestral do destino
				return; // caminho valido encontrado
			}

			if ((!percorridos[destino->retId() - 1] && !cabo->lotado()) || atual->retDemanda() == -1) { // (se o proximo nao for percorrido e o cabo nao estiver lotado) ou atual for ficticio
				
				if (cabo->eInverso()) { // se for uma aresta de retorno
					Vertice* inicial = this->retVertice(cabo->retIdDestino()); // pega o vertice de inicio (desinvertido)
					Cabo* desinvertido = inicial->retCabo(cabo->retIdOrigem()); // pega a mesma aresta desinvertida

					if (desinvertido->retCorrente() > 0) { // se houver corrente disponivel
						std::cout << "Proximo vertice" << std::endl;
						estagios.prox = cabo; // adiciona o cabo no passo a ser adicionado na fila
						estagios.conexHist = conexHist; // adiciona o historico ao passo
						fila.push(estagios); // adiciona o cabo na fila de execucao
					}
				}
				else {
					std::cout << "Proximo vertice" << std::endl;
					estagios.prox = cabo;	// adiciona o cabo no passo a ser adicionado na fila
					estagios.conexHist = conexHist;	// adiciona o historico ao passo
					fila.push(estagios); // adiciona o cabo na fila de execucao
				}
			}
		}
	}

	return;
}

void Grafo::edmonsKarp() {

	Vertice* inicio = &this->vertices[this->retTam() - 2]; // vertice ficticio de inicio
	Vertice* fim = &this->vertices[this->retTam() - 1];	// verticde ficticio de fim
	int gargalo;

	while(true){ // enquanto houverem caminhos validos (tem um break no final)

		std::vector<Cabo*> conexPais(this->retTam(), nullptr); // caminho

		this->bfs(inicio, *fim, conexPais); // pega o caminho

		if(conexPais[fim->retId() - 1] != nullptr) { // se o destino ficticio tiver ancestral (caminho valido)
			std::stack<Cabo*> caminho;

			// variaveis
			Vertice* destino = fim;
			Cabo* cabo = conexPais[destino->retId() - 1];
			Vertice* origem = this->retVertice(cabo->retIdOrigem());
			Cabo* desinvertido = nullptr;

			gargalo = origem->retDeficit(); // gargalo tem que ser menor ou igual ao quanto falta de energia para o vertice destino real

			std::cout << "Ultimo vertice: " << origem->retId() << std::endl;
			std::cout << "Energia que falta: " << origem->retDeficit() << std::endl;

			while (conexPais[origem->retId() - 1] != nullptr) { // enquanto nao chegar no primeiro

				destino = origem; // passo anterior
				cabo = conexPais[destino->retId() - 1]; // cabo ancestral anterior

				if (cabo->eInverso()) { // se ele for inverso
					std::cout << std::endl << "Cabo invertido" << std::endl << std::endl;
					origem = this->retVertice(cabo->retIdDestino());
					desinvertido = origem->retCabo(cabo->retIdOrigem());
				}
				else { // se ele nao for inverso
					origem = this->retVertice(cabo->retIdOrigem());
				}

				std::cout << "Origem: " << origem->retId() << std::endl;
				std::cout << "Destino: " << destino->retId() << std::endl;

				caminho.push(cabo);

				std::cout << "Cabo: " << cabo->retIdOrigem() << " -> " << cabo->retIdDestino() << ": " << cabo->retCorrente() << "/" << cabo->retCap() << std::endl;

				// acha o gargalo
				if(!cabo->eInverso()){
					if (cabo->ret_capDisponivel() < gargalo) { // se nao for inverso, considera a capacidade disponivel do cabo 
						gargalo = cabo->ret_capDisponivel(); 
					}
				}
				else {
					if (desinvertido->retCorrente() < gargalo) { // se for inverso, considera a corrente do cabo desinvertido
						gargalo = desinvertido->retCorrente();
					}
				}
			}

			while (!caminho.empty()) { // enquanto tiver caminho

				cabo = caminho.top();
				caminho.pop();

				if (cabo->eInverso()) { // se for invertido
					Vertice* inicial = this->retVertice(cabo->retIdDestino());
					desinvertido = inicial->retCabo(cabo->retIdOrigem());
					desinvertido->adCorrente(-(gargalo)); // tira o equivalente ao gargalo da corrente do cabo desinvertido
				}
				else { // se nao for invertido
					cabo->adCorrente(gargalo); // adiciona o equivalente ao gargalo na corrente 
				}

				std::cout << "Cabo: " << cabo->retIdOrigem() << " -> " << cabo->retIdDestino() << ": " << cabo->retCorrente() << "/" << cabo->retCap() << std::endl;
				if (caminho.size() == 0) { // quando chegar no ultimo
					std::cout << "Id do ultimo: " << this->retVertice(cabo->retIdDestino())->retId() << std::endl;
					this->retVertice(cabo->retIdDestino())->adConsumo(gargalo); // adiciona ao vertice a energia equivalente ao gargalo
				}
			}
		}
		if (conexPais[fim->retId() - 1] == nullptr) { // quando o destino nao tiver ancestral (nao ha caminho valido) para
			break;
		}
	}
}