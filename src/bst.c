
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* Estrutura interna de cada no da arvore */
struct NoBST {
    Local local;
    struct NoBST *esq;
    struct NoBST *dir;
};

/* INSERIR */
NoBST *bst_inserir(NoBST *raiz, Local local, int *sucesso) {

    if (sucesso != NULL)
        *sucesso = 0;

    if (raiz == NULL) {
        NoBST *novo = malloc(sizeof(NoBST));

        if (novo == NULL)
            return NULL;

        novo->local = local;
        novo->esq = NULL;
        novo->dir = NULL;

        if (sucesso != NULL)
            *sucesso = 1;

        return novo;
    }

    if (local.id < raiz->local.id) {
        if (raiz->esq == NULL) {
            NoBST *novo = bst_inserir(NULL, local, sucesso);

            if (novo != NULL)
                raiz->esq = novo;
        } else {
            raiz->esq = bst_inserir(raiz->esq, local, sucesso);
        }
    }
    else if (local.id > raiz->local.id) {
        if (raiz->dir == NULL) {
            NoBST *novo = bst_inserir(NULL, local, sucesso);

            if (novo != NULL)
                raiz->dir = novo;
        } else {
            raiz->dir = bst_inserir(raiz->dir, local, sucesso);
        }
    }

    return raiz;
}

/* BUSCAR */
const Local *bst_buscar(const NoBST *raiz, int id) {

    while (raiz != NULL) {

        if (id == raiz->local.id)
            return &raiz->local;

        if (id < raiz->local.id)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }

    return NULL;
}

/* ENCONTRAR MENOR NO */
static NoBST *menor_no(NoBST *raiz) {

    while (raiz != NULL && raiz->esq != NULL)
        raiz = raiz->esq;

    return raiz;
}

/* REMOVER */
NoBST *bst_remover(NoBST *raiz, int id, int *sucesso) {

    if (sucesso != NULL)
        *sucesso = 0;

    if (raiz == NULL)
        return NULL;

    if (id < raiz->local.id) {
        raiz->esq = bst_remover(raiz->esq, id, sucesso);
    }
    else if (id > raiz->local.id) {
        raiz->dir = bst_remover(raiz->dir, id, sucesso);
    }
    else {

        if (sucesso != NULL)
            *sucesso = 1;

        /* Caso 1: no sem filhos */
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        /* Caso 2: no com apenas um filho */
        if (raiz->esq == NULL || raiz->dir == NULL) {

            NoBST *filho;

            if (raiz->esq != NULL)
                filho = raiz->esq;
            else
                filho = raiz->dir;

            free(raiz);
            return filho;
        }

        /* Caso 3: no com dois filhos */
        NoBST *sucessor = menor_no(raiz->dir);

        raiz->local = sucessor->local;

        int removido;
        raiz->dir = bst_remover(
            raiz->dir,
            sucessor->local.id,
            &removido
        );
    }

    return raiz;
}

/* LISTAR EM ORDEM */
void bst_listar_em_ordem(const NoBST *raiz) {

    if (raiz == NULL)
        return;

    bst_listar_em_ordem(raiz->esq);

    printf("%d | %s | %s | %s\n",
        raiz->local.id,
        raiz->local.nome,
        raiz->local.categoria,
        raiz->local.bairro
    );

    bst_listar_em_ordem(raiz->dir);
}

/* MENOR ID */
int bst_menor_id(const NoBST *raiz, int *id) {

    if (raiz == NULL || id == NULL)
        return 0;

    while (raiz->esq != NULL)
        raiz = raiz->esq;

    *id = raiz->local.id;

    return 1;
}

/* MAIOR ID */
int bst_maior_id(const NoBST *raiz, int *id) {

    if (raiz == NULL || id == NULL)
        return 0;

    while (raiz->dir != NULL)
        raiz = raiz->dir;

    *id = raiz->local.id;

    return 1;
}

/* COPIAR REGISTROS PARA VETOR */
static int copiar_rec(
    const NoBST *raiz,
    Local *vetor,
    int capacidade,
    int *quantidade
) {

    if (raiz == NULL)
        return 1;

    if (!copiar_rec(raiz->esq, vetor, capacidade, quantidade))
        return 0;

    if (*quantidade >= capacidade)
        return 0;

    vetor[*quantidade] = raiz->local;
    (*quantidade)++;

    return copiar_rec(raiz->dir, vetor, capacidade, quantidade);
}

int bst_copiar_vetor(
    const NoBST *raiz,
    Local *vetor,
    int capacidade,
    int *quantidade
) {

    if (vetor == NULL || quantidade == NULL || capacidade < 0)
        return 0;

    *quantidade = 0;

    return copiar_rec(raiz, vetor, capacidade, quantidade);
}

/* LIBERAR ARVORE */
void bst_liberar(NoBST *raiz) {

    if (raiz == NULL)
        return;

    bst_liberar(raiz->esq);
    bst_liberar(raiz->dir);

    free(raiz);
}
