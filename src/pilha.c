#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct NoPilha {
    Acao acao;
    struct NoPilha *prox;
} NoPilha;

struct Pilha { NoPilha *topo; };

Pilha *pilha_criar(void) { return calloc(1, sizeof(Pilha)); }

int pilha_push(Pilha *p, Acao acao) {
    if (!p) return 0;
    NoPilha *n = malloc(sizeof(*n));
    if (!n) return 0;
    n->acao = acao;
    n->prox = p->topo;
    p->topo = n;
    return 1;
}

int pilha_pop(Pilha *p, Acao *acao) {
    if (!p || !p->topo || !acao) return 0;
    NoPilha *n = p->topo;
    *acao = n->acao;
    p->topo = n->prox;
    free(n);
    return 1;
}

int pilha_peek(const Pilha *p, Acao *acao) {
    if (!p || !p->topo || !acao) return 0;
    *acao = p->topo->acao;
    return 1;
}

static const char *nome_acao(TipoAcao tipo) {
    switch (tipo) {
        case ACAO_CADASTRO: return "Cadastro";
        case ACAO_REMOCAO_LOCAL: return "Remocao de local";
        case ACAO_ADICAO_CONEXAO: return "Adicao de conexao";
        case ACAO_REMOCAO_CONEXAO: return "Remocao de conexao";
        default: return "Acao desconhecida";
    }
}

void pilha_imprimir_ultimas_cinco(const Pilha *p) {
    if (!p || !p->topo) { puts("Historico vazio."); return; }
    const NoPilha *atual = p->topo;
    int cont = 0;
    while (atual && cont < 5) {
        printf("%d. %s (IDs: %d", cont + 1, nome_acao(atual->acao.tipo), atual->acao.id1);
        if (atual->acao.id2 > 0) printf(", %d", atual->acao.id2);
        puts(")");
        atual = atual->prox;
        cont++;
    }
}

void pilha_liberar(Pilha *p) {
    if (!p) return;
    NoPilha *atual = p->topo;
    while (atual) {
        NoPilha *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(p);
}
