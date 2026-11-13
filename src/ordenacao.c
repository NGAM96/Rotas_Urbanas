
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ordenacao.h"

static int comparar(const Local *a, const Local *b) {
    int r = strcmp(a->nome, b->nome);

    if (r != 0)
        return r;

    return (a->id > b->id) - (a->id < b->id);
}

static void mesclar(Local *v, Local *aux, int ini, int meio, int fim) {
    int i = ini;
    int j = meio + 1;
    int k = ini;

    while (i <= meio && j <= fim)
        aux[k++] = comparar(&v[i], &v[j]) <= 0 ? v[i++] : v[j++];

    while (i <= meio)
        aux[k++] = v[i++];

    while (j <= fim)
        aux[k++] = v[j++];

    for (i = ini; i <= fim; i++)
        v[i] = aux[i];
}

static void ordenar(Local *vetor, Local *aux, int inicio, int fim) {
    if (inicio >= fim)
        return;

    int meio = inicio + (fim - inicio) / 2;

    ordenar(vetor, aux, inicio, meio);
    ordenar(vetor, aux, meio + 1, fim);

    mesclar(vetor, aux, inicio, meio, fim);
}

void merge_sort_locais(Local *vetor, int quantidade) {
    if (vetor == NULL || quantidade <= 1)
        return;

    Local *aux = malloc(quantidade * sizeof(Local));

    if (aux == NULL) {
        printf("Erro: nao foi possivel alocar memoria para ordenacao.\n");
        return;
    }

    ordenar(vetor, aux, 0, quantidade - 1);

    free(aux);
}
