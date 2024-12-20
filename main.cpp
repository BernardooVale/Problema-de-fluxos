
#include <iostream>
#include <fstream>

#include "Cabo.h"
#include "Vertice.h"
#include "Grafo.h"

using namespace std;

void manual() {

    Grafo redeEletrica;

    int vertices, cabos;

    cout << "Digite %d numero de vertices e %d numero de cabos" << endl;
    cin >> vertices >> cabos;

    int id, demanda;

    for (int i = 0; i < vertices; i++) {
        cout << "Digite %d id e %d demanda(0 se for gerador)" << endl;
        cin >> id >> demanda;
        Vertice novo(id, demanda);

        redeEletrica.adVertice(novo);
    }

    int origem, destino, cap;

    for (int i = 0; i < cabos; i++) {
        cout << "Digite %d id origem %d id destino %d capacidade" << endl;
        cin >> origem >> destino >> cap;
        Cabo cabo(origem, destino, cap);

        redeEletrica.retVertice(origem)->adCabo(cabo);
    }

    Vertice inicio(redeEletrica.retTam() + 1, -1); // Ponto ficticio de inicio
    redeEletrica.adVertice(inicio);
    Vertice fim(redeEletrica.retTam() + 1, -1); // Ponto ficticio de final
    redeEletrica.adVertice(fim);

    // O algoritimo vai comecar do ponto inicio, que possui conexoes para todos os geradores, e tem como destino o ponto final que recebe uma aresta de todos os consumidores.
    // Isso é feito para rodar uma vez apenas o algoritimo, ao inves de rodar ele a partir de todos os geradores para todos os consumidores

    redeEletrica.normalizaInicio();
    redeEletrica.normalizaFim();

    redeEletrica.edmonsKarp();
    redeEletrica.removeInicioFim();

    int eTotal = redeEletrica.energiaTotal();

    std::cout << "Energia total: " << eTotal << std::endl;
    std::cout << "Deficit total: " << redeEletrica.deficit() << std::endl;
    std::cout << "Excesso total: " << redeEletrica.excesso(eTotal) << std::endl;
    redeEletrica.cabosCriticos();

    std::cout << std::endl;

    redeEletrica.print();
}

void automatico() {

    Grafo redeEletrica;

    ifstream arquivo("teste.txt");
    int vertices, cabos;

    arquivo >> vertices >> cabos;

    int id, demanda;

    for (int i = 0; i < vertices; i++) {
        arquivo >> id >> demanda;
        Vertice novo(id, demanda);

        redeEletrica.adVertice(novo);
    }

    int origem, destino, cap;

    for (int i = 0; i < cabos; i++) {
        arquivo >> origem >> destino >> cap;
        Cabo cabo(origem, destino, cap);
        redeEletrica.retVertice(origem)->adCabo(cabo);

        Cabo caboRetorno(destino, origem, cap, true);
        redeEletrica.retVertice(destino)->adCabo(caboRetorno);
    }

    arquivo.close();

    cout << endl;

    //redeEletrica.preencheRede();

    cout << endl << "Edmonds-Karp:" << endl;

    Vertice inicio(redeEletrica.retTam() + 1, -1); // Ponto ficticio de inicio
    redeEletrica.adVertice(inicio);
    Vertice fim(redeEletrica.retTam() + 1, -1); // Ponto ficticio de final
    redeEletrica.adVertice(fim);

    // O algoritimo vai comecar do ponto inicio, que possui conexoes para todos os geradores, e tem como destino o ponto final que recebe uma aresta de todos os consumidores.
    // Isso é feito para rodar uma vez apenas o algoritimo, ao inves de rodar ele a partir de todos os geradores para todos os consumidores

    redeEletrica.normalizaInicio();
    redeEletrica.normalizaFim();

    redeEletrica.edmonsKarp();
    redeEletrica.removeInicioFim();

    int eTotal = redeEletrica.energiaTotal();

    std::cout << "Energia total: " << eTotal << std::endl;
    std::cout << "Deficit total: " << redeEletrica.deficit() << std::endl;
    std::cout << "Excesso total: " << redeEletrica.excesso(eTotal) << std::endl;
    redeEletrica.cabosCriticos();

    std::cout << std::endl;

    redeEletrica.print();
}

int main() {

    int teste;

    cout << "(0) Teste manual \n(1) Teste automatico" << std::endl;
    cin >> teste;

    teste == 0 ? manual() : automatico();
}

