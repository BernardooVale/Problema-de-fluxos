#ifndef Cabo_HPP
#define Cabo_HPP
class Cabo {

private:

	int idOrigem, idDestino, cap, corrente;
	bool inverso;

public:

	Cabo(int idOrigem, int idDestino, int cap);
	Cabo(int idOrigem, int idDestino, int cap, bool inverso);

	void adCorrente(int corrente); // adiciona ao valor atual da corrente

	int retCorrente(); // retorna corrente
	int retIdDestino(); // retorna id destino
	int retCap();
	int ret_capDisponivel();
	int retIdOrigem();

	bool lotado(); // retorna se a corrente == cap
	bool eInverso();

	void print();
};

#endif

