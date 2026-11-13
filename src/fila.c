#include <stdlib.h>
#include "fila.h"

typedef struct NoFila {
    int id;
    struct NoFila *prox;
} NoFila;

struct Fila {
    NoFila *inicio;
    NoFila *fim;
};

Fila *fila_criar(void) { return calloc(1, sizeof(Fila)); }
int fila_vazia(const Fila *f) { return !f || f->inicio == NULL; }

int fila_enfileirar(Fila *f, int id) {
    if (!f) return 0;
    NoFila *n = malloc(sizeof(*n));
    if (!n) return 0;
    n->id = id; n->prox = NULL;
    if (f->fim) f->fim->prox = n; else f->inicio = n;
    f->fim = n;
    return 1;
}

int fila_desenfileirar(Fila *f, int *id) {
    if (!f || !f->inicio || !id) return 0;
    NoFila *n = f->inicio;
    *id = n->id;
    f->inicio = n->prox;
    if (!f->inicio) f->fim = NULL;
    free(n);
    return 1;
}

void fila_liberar(Fila *f) {
    if (!f) return;
    int id;
    while (fila_desenfileirar(f, &id)) {}
    free(f);
}
