CXX = g++
SRC = src/*.cpp
INC = -Iinclude
TARGET = tsp

# Compilação normal e otimizada (como estava antes)
all: build
	
build:
	$(CXX) $(SRC) $(INC) -o $(TARGET) -O3

# -----------------------------------------------------
# MODO DE DEBUG (Use este para achar o Segfault)
# -g: Adiciona símbolos de debug (linhas do código)
# -O0: Desativa otimização para não bagunçar o rastreio
# -fsanitize=address: Detecta acesso fora de vetores/matrizes
# -Wall -Wextra: Mostra avisos extras no código
# -----------------------------------------------------
debug:
	$(CXX) $(SRC) $(INC) -o $(TARGET) -O0 -g -fsanitize=address -Wall -Wextra

run:
	./$(TARGET)

# Comando direto para abrir no GDB (opcional)
run-gdb: debug
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET)