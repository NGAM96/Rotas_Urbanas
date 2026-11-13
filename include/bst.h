#ifndef BST_H
#define BST_H

#include "local.h"

typedef struct NoBST NoBST;

NoBST *bst_inserir(NoBST *raiz, Local local, int *sucesso);
const Local *bst_buscar(const NoBST *raiz, int id);
NoBST *bst_remover(NoBST *raiz, int id, int *sucesso);
void bst_listar_em_ordem(const NoBST *raiz);
int bst_menor_id(const NoBST *raiz, int *id);
int bst_maior_id(const NoBST *raiz, int *id);
int bst_copiar_vetor(const NoBST *raiz, Local *vetor, int capacidade, int *quantidade);
void bst_liberar(NoBST *raiz);

#endif
