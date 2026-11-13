#ifndef FILA_H
#define FILA_H

typedef struct Fila Fila;

Fila *fila_criar(void);
int fila_vazia(const Fila *fila);
int fila_enfileirar(Fila *fila, int id);
int fila_desenfileirar(Fila *fila, int *id);
void fila_liberar(Fila *fila);

#endif
