CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude

SRC = src/bst.c src/grafo.c src/lista.c src/fila.c src/pilha.c src/ordenacao.c
APP_SRC = src/main.c $(SRC)
APP = build/rotas_urbanas.exe
TESTS = build/test_estruturas.exe build/test_bst.exe build/test_grafo.exe build/test_ordenacao.exe

.PHONY: all run test clean

all: $(APP)

$(APP): $(APP_SRC) | build
	$(CC) $(CFLAGS) $(APP_SRC) -o $(APP)

build/test_estruturas.exe: tests/test_estruturas.c src/lista.c src/fila.c src/pilha.c | build
	$(CC) $(CFLAGS) $^ -o $@

build/test_bst.exe: tests/test_bst.c src/bst.c | build
	$(CC) $(CFLAGS) $^ -o $@

build/test_grafo.exe: tests/test_grafo.c src/grafo.c src/lista.c src/fila.c | build
	$(CC) $(CFLAGS) $^ -o $@

build/test_ordenacao.exe: tests/test_ordenacao.c src/ordenacao.c | build
	$(CC) $(CFLAGS) $^ -o $@

build:
	mkdir -p build

run: $(APP)
	./$(APP)

test: $(TESTS)
	@echo "=== Teste das estruturas lineares ==="
	@./build/test_estruturas.exe
	@echo "=== Teste da BST ==="
	@./build/test_bst.exe
	@echo "=== Teste do grafo e BFS ==="
	@./build/test_grafo.exe
	@echo "=== Teste do Merge Sort ==="
	@./build/test_ordenacao.exe
	@echo "=== Todos os testes foram executados. ==="

clean:
	rm -rf build
