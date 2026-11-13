#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

#define MAX_VERTICES 100

typedef struct Grafo Grafo;

Grafo *grafo_criar(void);
int grafo_adicionar_vertice(Grafo *grafo, int id);
int grafo_remover_vertice(Grafo *grafo, int id);
int grafo_adicionar_aresta(Grafo *grafo, int id1, int id2);
int grafo_remover_aresta(Grafo *grafo, int id1, int id2);
int grafo_conexao_direta(const Grafo *grafo, int id1, int id2);
int grafo_bfs(const Grafo *grafo, int origem, Lista *resultado);
int grafo_existe_caminho(const Grafo *grafo, int origem, int destino);
void grafo_liberar(Grafo *grafo);

#endif
