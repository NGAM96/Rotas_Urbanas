#ifndef PILHA_H
#define PILHA_H

typedef enum {
    ACAO_CADASTRO,
    ACAO_REMOCAO_LOCAL,
    ACAO_ADICAO_CONEXAO,
    ACAO_REMOCAO_CONEXAO
} TipoAcao;

typedef struct {
    TipoAcao tipo;
    int id1;
    int id2;
} Acao;

typedef struct Pilha Pilha;

Pilha *pilha_criar(void);
int pilha_push(Pilha *pilha, Acao acao);
int pilha_pop(Pilha *pilha, Acao *acao);
int pilha_peek(const Pilha *pilha, Acao *acao);
void pilha_imprimir_ultimas_cinco(const Pilha *pilha);
void pilha_liberar(Pilha *pilha);

#endif
