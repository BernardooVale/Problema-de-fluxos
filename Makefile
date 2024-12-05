# Nome do executável
EXEC = tp2

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# Arquivos fonte
SRCS = main.cpp Cabo.cpp Vertice.cpp Grafo.cpp

# Arquivos de cabeçalho
HEADERS = Cabo.h Vertice.h Grafo.h

# Objetos gerados a partir dos arquivos fonte
OBJS = $(SRCS:.cpp=.o)

# Regra padrão (para compilar o executável)
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# Como compilar os arquivos .cpp para .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza de arquivos gerados
clean:
	rm -f $(OBJS) $(EXEC)

# Regras para recomeçar do zero
re: clean all
