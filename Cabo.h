#ifndef Cabo_HPP
#define Cabo_HPP
class Cabo{

private:

	int idOrigem, idDestino, cap, corrente;

	void normalizaCorrente();

public:

	Cabo(int idOrigem, int idDestino, int cap);

	void defCorrente(int corrente); // define o valor da corrente
	void adCorrente(int corrente); // adiciona ao valor atual da corrente
	int retCorrente(); // retorna corrente
	int retIdDestino(); // retorna id destino
	bool lotado(); // retorna se a corrente == cap
	void print();
	int retCap();
	int ret_capDisponivel();
	int retIdOrigem();
};

#endif

