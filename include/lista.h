#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

Lista *lista_criar(void);
int lista_inserir_fim(Lista *lista, int id);
void lista_imprimir(const Lista *lista);
void lista_liberar(Lista *lista);

#endif
