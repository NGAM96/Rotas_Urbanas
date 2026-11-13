
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "fila.h"

typedef struct NoAdj {
    int id;
    struct NoAdj *prox;
} NoAdj;

typedef struct {
    int id;
    NoAdj *adjacencias;
} Vertice;

struct Grafo {
    Vertice vertices[MAX_VERTICES];
    int quantidade;
};

static int buscar_indice(const Grafo *grafo, int id) {
    if (grafo == NULL) return -1;

    for (int i = 0; i < grafo->quantidade; i++) {
        if (grafo->vertices[i].id == id)
            return i;
    }

    return -1;
}

static int adjacencia_existe(const Vertice *vertice, int id) {
    NoAdj *atual = vertice->adjacencias;

    while (atual != NULL) {
        if (atual->id == id) return 1;
        atual = atual->prox;
    }

    return 0;
}

static int inserir_adjacencia(Vertice *vertice, int id) {
    NoAdj *novo = malloc(sizeof(NoAdj));

    if (novo == NULL) return 0;

    novo->id = id;
    novo->prox = vertice->adjacencias;
    vertice->adjacencias = novo;

    return 1;
}

static int remover_adjacencia(Vertice *vertice, int id) {
    NoAdj *atual = vertice->adjacencias;
    NoAdj *anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL)
                vertice->adjacencias = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

Grafo *grafo_criar(void) {
    Grafo *grafo = malloc(sizeof(Grafo));

    if (grafo == NULL) return NULL;

    grafo->quantidade = 0;

    return grafo;
}

int grafo_adicionar_vertice(Grafo *grafo, int id) {
    if (grafo == NULL || id <= 0) return 0;

    if (grafo->quantidade >= MAX_VERTICES) return 0;

    if (buscar_indice(grafo, id) != -1) return 0;

    Vertice *novo = &grafo->vertices[grafo->quantidade];

    novo->id = id;
    novo->adjacencias = NULL;

    grafo->quantidade++;

    return 1;
}

int grafo_remover_vertice(Grafo *grafo, int id) {
    int indice = buscar_indice(grafo, id);

    if (indice == -1) return 0;

    NoAdj *atual = grafo->vertices[indice].adjacencias;

    while (atual != NULL) {
        NoAdj *prox = atual->prox;

        int outro = buscar_indice(grafo, atual->id);

        if (outro != -1)
            remover_adjacencia(&grafo->vertices[outro], id);

        free(atual);
        atual = prox;
    }

    for (int i = indice; i < grafo->quantidade - 1; i++)
        grafo->vertices[i] = grafo->vertices[i + 1];

    grafo->quantidade--;

    return 1;
}

int grafo_adicionar_aresta(Grafo *grafo, int id1, int id2) {
    int i1 = buscar_indice(grafo, id1);
    int i2 = buscar_indice(grafo, id2);

    if (i1 == -1 || i2 == -1 || id1 == id2)
        return 0;

    if (adjacencia_existe(&grafo->vertices[i1], id2))
        return 0;

    if (!inserir_adjacencia(&grafo->vertices[i1], id2))
        return 0;

    if (!inserir_adjacencia(&grafo->vertices[i2], id1)) {
        remover_adjacencia(&grafo->vertices[i1], id2);
        return 0;
    }

    return 1;
}

int grafo_remover_aresta(Grafo *grafo, int id1, int id2) {
    int i1 = buscar_indice(grafo, id1);
    int i2 = buscar_indice(grafo, id2);

    if (i1 == -1 || i2 == -1 || id1 == id2)
        return 0;

    if (!adjacencia_existe(&grafo->vertices[i1], id2))
        return 0;

    remover_adjacencia(&grafo->vertices[i1], id2);
    remover_adjacencia(&grafo->vertices[i2], id1);

    return 1;
}

int grafo_conexao_direta(const Grafo *grafo, int id1, int id2) {
    int i1 = buscar_indice(grafo, id1);
    int i2 = buscar_indice(grafo, id2);

    if (i1 == -1 || i2 == -1 || id1 == id2)
        return 0;

    return adjacencia_existe(&grafo->vertices[i1], id2);
}

int grafo_bfs(const Grafo *grafo, int origem, Lista *resultado) {
    if (grafo == NULL || resultado == NULL)
        return 0;

    int indice = buscar_indice(grafo, origem);

    if (indice == -1) return 0;

    int visitados[MAX_VERTICES] = {0};

    Fila *fila = fila_criar();

    if (fila == NULL) return 0;

    if (!fila_enfileirar(fila, origem)) {
        fila_liberar(fila);
        return 0;
    }

    visitados[indice] = 1;

    int sucesso = 1;

    while (!fila_vazia(fila)) {
        int id_atual;

        if (!fila_desenfileirar(fila, &id_atual)) {
            sucesso = 0;
            break;
        }

        if (!lista_inserir_fim(resultado, id_atual)) {
            sucesso = 0;
            break;
        }

        int ids[MAX_VERTICES];
        int total = 0;

        int atual_indice = buscar_indice(grafo, id_atual);
        NoAdj *atual = grafo->vertices[atual_indice].adjacencias;

        while (atual != NULL) {
            ids[total++] = atual->id;
            atual = atual->prox;
        }

        for (int i = 0; i < total; i++) {
            for (int j = i + 1; j < total; j++) {
                if (ids[i] > ids[j]) {
                    int temp = ids[i];
                    ids[i] = ids[j];
                    ids[j] = temp;
                }
            }
        }

        for (int i = 0; i < total; i++) {
            int vizinho = buscar_indice(grafo, ids[i]);

            if (vizinho != -1 && !visitados[vizinho]) {
                visitados[vizinho] = 1;

                if (!fila_enfileirar(fila, ids[i])) {
                    sucesso = 0;
                    break;
                }
            }
        }

        if (!sucesso) break;
    }

    fila_liberar(fila);

    return sucesso;
}

int grafo_existe_caminho(const Grafo *grafo, int origem, int destino) {
    if (grafo == NULL) return 0;

    if (buscar_indice(grafo, origem) == -1 ||
        buscar_indice(grafo, destino) == -1)
        return 0;

    if (origem == destino) return 1;

    int visitados[MAX_VERTICES] = {0};
    Fila *fila = fila_criar();

    if (fila == NULL) return 0;

    fila_enfileirar(fila, origem);
    visitados[buscar_indice(grafo, origem)] = 1;

    int encontrou = 0;

    while (!fila_vazia(fila) && !encontrou) {
        int id_atual;

        if (!fila_desenfileirar(fila, &id_atual))
            break;

        int indice = buscar_indice(grafo, id_atual);
        NoAdj *atual = grafo->vertices[indice].adjacencias;

        while (atual != NULL) {
            int vizinho = buscar_indice(grafo, atual->id);

            if (atual->id == destino) {
                encontrou = 1;
                break;
            }

            if (vizinho != -1 && !visitados[vizinho]) {
                visitados[vizinho] = 1;
                fila_enfileirar(fila, atual->id);
            }

            atual = atual->prox;
        }
    }

    fila_liberar(fila);

    return encontrou;
}

void grafo_liberar(Grafo *grafo) {
    if (grafo == NULL) return;

    for (int i = 0; i < grafo->quantidade; i++) {
        NoAdj *atual = grafo->vertices[i].adjacencias;

        while (atual != NULL) {
            NoAdj *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    free(grafo);
}
