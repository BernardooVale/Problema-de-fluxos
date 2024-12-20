# Definindo variáveis
CXX = g++                        # Compilador C++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror # Flags de compilação
SRC_DIR = src                      # Diretório onde estão os arquivos fonte
OBJ_DIR = obj                      # Diretório onde os arquivos objeto serão armazenados
TARGET = tp2                       # Nome do executável

SRC= $(wildcard $(SRC_DIR)/*.cpp)

HEADERS = $(wildcard $(SRC_DIR)/*.h)

# Gerando os arquivos objeto correspondentes
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS) 
		$(CC) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CXXFLAGS) -c $< -O $@

clean:
		rm -rf $(OBJ_DIR) $(TARGET)

.PHONY all clean