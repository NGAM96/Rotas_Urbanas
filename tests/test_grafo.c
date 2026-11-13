
#include <assert.h>
#include <stdio.h>

#include "grafo.h"
#include "lista.h"

int main(void) {
    Grafo *grafo = grafo_criar();
    Lista *resultado = lista_criar();

    assert(grafo != NULL);
    assert(resultado != NULL);

    puts("=== TESTE DO GRAFO ===");

    assert(grafo_adicionar_vertice(grafo, 10));
    assert(grafo_adicionar_vertice(grafo, 20));
    assert(grafo_adicionar_vertice(grafo, 30));
    assert(grafo_adicionar_vertice(grafo, 40));
    assert(grafo_adicionar_vertice(grafo, 50));

    puts("Criacao de vertices: OK");

    assert(!grafo_adicionar_vertice(grafo, 10));
    assert(!grafo_adicionar_vertice(grafo, 0));

    puts("Rejeicao de vertices invalidos: OK");

    assert(grafo_adicionar_aresta(grafo, 10, 20));
    assert(grafo_adicionar_aresta(grafo, 10, 30));
    assert(grafo_adicionar_aresta(grafo, 20, 40));
    assert(grafo_adicionar_aresta(grafo, 30, 50));

    puts("Criacao de conexoes: OK");

    assert(!grafo_adicionar_aresta(grafo, 10, 20));
    assert(!grafo_adicionar_aresta(grafo, 20, 10));
    assert(!grafo_adicionar_aresta(grafo, 10, 10));
    assert(!grafo_adicionar_aresta(grafo, 10, 999));

    puts("Rejeicao de conexoes invalidas: OK");

    assert(grafo_conexao_direta(grafo, 10, 20));
    assert(grafo_conexao_direta(grafo, 20, 10));
    assert(!grafo_conexao_direta(grafo, 10, 50));

    puts("Consulta de conexao direta: OK");

    assert(grafo_bfs(grafo, 10, resultado));

    puts("\nResultado da BFS (ordem esperada: 10, 20, 30, 40, 50):");
    lista_imprimir(resultado);

    puts("BFS: OK");

    assert(grafo_existe_caminho(grafo, 10, 50));
    assert(!grafo_existe_caminho(grafo, 10, 999));
    assert(grafo_existe_caminho(grafo, 10, 10));

    puts("Verificacao de caminhos: OK");

    assert(grafo_remover_aresta(grafo, 10, 20));
    assert(!grafo_conexao_direta(grafo, 10, 20));
    assert(!grafo_remover_aresta(grafo, 10, 20));

    puts("Remocao de conexao: OK");

    assert(grafo_remover_vertice(grafo, 30));
    assert(!grafo_conexao_direta(grafo, 10, 30));
    assert(!grafo_remover_vertice(grafo, 30));

    puts("Remocao de vertice: OK");

   
    puts("\n=== TESTE DO LIMITE DE VERTICES ===");

    Grafo *grafo_limite = grafo_criar();

    assert(grafo_limite != NULL);

    for (int i = 1; i <= 100; i++) {
        assert(grafo_adicionar_vertice(grafo_limite, i));
    }

    puts("Cadastro de 100 vertices: OK");

    assert(!grafo_adicionar_vertice(grafo_limite, 101));

    puts("Rejeicao do 101o vertice: OK");

    assert(grafo_remover_vertice(grafo_limite, 50));

    puts("Remocao de um vertice: OK");

    assert(grafo_adicionar_vertice(grafo_limite, 101));

    puts("Cadastro apos liberar uma vaga: OK");

    grafo_liberar(grafo_limite);

   
    lista_liberar(resultado);
    grafo_liberar(grafo);

    puts("\nTODOS OS TESTES DO GRAFO PASSARAM!");

    return 0;
}
