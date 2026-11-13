
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

Local criar_local(int id, const char *nome) {

    Local local;

    local.id = id;
    strcpy(local.nome, nome);
    strcpy(local.categoria, "Servico");
    strcpy(local.bairro, "Centro");

    return local;
}

int main(void) {

    NoBST *raiz = NULL;
    int sucesso;
    int id;

    puts("=== TESTE DA BST ===");

    /* INSERCOES */
    raiz = bst_inserir(raiz, criar_local(50, "Terminal"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(30, "Hospital"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(70, "Parque"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(20, "Escola"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(40, "Shopping"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(60, "Universidade"), &sucesso);
    assert(sucesso);

    raiz = bst_inserir(raiz, criar_local(80, "Aeroporto"), &sucesso);
    assert(sucesso);

    puts("Insercoes: OK");

    /* ID DUPLICADO */
    raiz = bst_inserir(raiz, criar_local(50, "Duplicado"), &sucesso);
    assert(!sucesso);

    puts("Rejeicao de ID duplicado: OK");

    /* BUSCA */
    const Local *local = bst_buscar(raiz, 40);

    assert(local != NULL);
    assert(strcmp(local->nome, "Shopping") == 0);

    assert(bst_buscar(raiz, 999) == NULL);

    puts("Busca existente e inexistente: OK");

    /* PERCURSO EM ORDEM */
    puts("\nLocais em ordem crescente de ID:");
    bst_listar_em_ordem(raiz);

    /* MENOR E MAIOR */
    assert(bst_menor_id(raiz, &id));
    assert(id == 20);
    printf("\nMenor ID: %d\n", id);

    assert(bst_maior_id(raiz, &id));
    assert(id == 80);
    printf("Maior ID: %d\n", id);

    /* REMOCAO DE FOLHA */
    raiz = bst_remover(raiz, 20, &sucesso);
    assert(sucesso);
    assert(bst_buscar(raiz, 20) == NULL);

    puts("\nRemocao de no folha: OK");

    /* REMOCAO DE NO COM UM FILHO */
    raiz = bst_remover(raiz, 30, &sucesso);
    assert(sucesso);
    assert(bst_buscar(raiz, 30) == NULL);

    puts("Remocao de no com um filho: OK");

    /* REMOCAO DE NO COM DOIS FILHOS */
    raiz = bst_remover(raiz, 70, &sucesso);
    assert(sucesso);
    assert(bst_buscar(raiz, 70) == NULL);

    puts("Remocao de no com dois filhos: OK");

    /* REMOCAO INEXISTENTE */
    raiz = bst_remover(raiz, 999, &sucesso);
    assert(!sucesso);

    puts("Rejeicao de remocao inexistente: OK");

    /* LIBERACAO */
    bst_liberar(raiz);

    puts("\nTODOS OS TESTES DA BST PASSARAM!");

    return 0;
}
