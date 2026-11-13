#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct NoLista {
    int id;
    struct NoLista *prox;
} NoLista;

struct Lista {
    NoLista *inicio;
    NoLista *fim;
};

Lista *lista_criar(void) {
    return calloc(1, sizeof(Lista));
}

int lista_inserir_fim(Lista *lista, int id) {
    if (!lista) return 0;
    NoLista *novo = malloc(sizeof(*novo));
    if (!novo) return 0;
    novo->id = id;
    novo->prox = NULL;
    if (lista->fim) lista->fim->prox = novo;
    else lista->inicio = novo;
    lista->fim = novo;
    return 1;
}

void lista_imprimir(const Lista *lista) {
    if (!lista) return;
    for (NoLista *atual = lista->inicio; atual; atual = atual->prox)
        printf("%d ", atual->id);
    putchar('\n');
}

void lista_liberar(Lista *lista) {
    if (!lista) return;
    NoLista *atual = lista->inicio;
    while (atual) {
        NoLista *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}
