#ifndef LOCAL_H
#define LOCAL_H

#define TAM_TEXTO 80

typedef struct {
    int id;
    char nome[TAM_TEXTO];
    char categoria[TAM_TEXTO];
    char bairro[TAM_TEXTO];
} Local;

#endif
