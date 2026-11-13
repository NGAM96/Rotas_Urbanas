
#include <assert.h>
#include <stdio.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"

int main(void) {

    // TESTE DA LISTA
    puts("=== TESTE DA LISTA ===");

    Lista *lista = lista_criar();

    assert(lista != NULL);
    assert(lista_inserir_fim(lista, 10));
    assert(lista_inserir_fim(lista, 20));
    assert(lista_inserir_fim(lista, 30));

    lista_imprimir(lista);
    lista_liberar(lista);

    puts("Lista: OK\n");


    // TESTE DA FILA
    puts("=== TESTE DA FILA ===");

    Fila *fila = fila_criar();
    int id;

    assert(fila_enfileirar(fila, 10));
    assert(fila_enfileirar(fila, 20));
    assert(fila_enfileirar(fila, 30));

    assert(fila_desenfileirar(fila, &id));
    printf("Removido: %d\n", id);

    assert(fila_desenfileirar(fila, &id));
    printf("Removido: %d\n", id);

    assert(fila_desenfileirar(fila, &id));
    printf("Removido: %d\n", id);

    fila_liberar(fila);

    puts("Fila: OK\n");


    // TESTE DA PILHA
    puts("=== TESTE DA PILHA ===");

    Pilha *pilha = pilha_criar();

    Acao a1 = {ACAO_CADASTRO, 10, 0};
    Acao a2 = {ACAO_ADICAO_CONEXAO, 10, 20};
    Acao a3 = {ACAO_REMOCAO_CONEXAO, 20, 30};

    assert(pilha_push(pilha, a1));
    assert(pilha_push(pilha, a2));
    assert(pilha_push(pilha, a3));

    Acao consulta;

    assert(pilha_peek(pilha, &consulta));
    printf("Topo: IDs %d e %d\n",
           consulta.id1, consulta.id2);

    assert(pilha_pop(pilha, &consulta));

    puts("Historico:");
    pilha_imprimir_ultimas_cinco(pilha);

    pilha_liberar(pilha);

    puts("Pilha: OK");

    puts("\nTODOS OS TESTES PASSARAM!");

    return 0;
}
