
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "ordenacao.h"

static Local criar_local(int id, const char *nome) {
    Local local;

    local.id = id;
    strcpy(local.nome, nome);
    strcpy(local.categoria, "Servico");
    strcpy(local.bairro, "Centro");

    return local;
}

int main(void) {
    Local locais[] = {
        criar_local(30, "Shopping"),
        criar_local(20, "Aeroporto"),
        criar_local(50, "Hospital"),
        criar_local(10, "Aeroporto"),
        criar_local(40, "Parque")
    };

    puts("=== TESTE DO MERGE SORT ===");

    merge_sort_locais(locais, 5);

    assert(strcmp(locais[0].nome, "Aeroporto") == 0);
    assert(locais[0].id == 10);

    assert(strcmp(locais[1].nome, "Aeroporto") == 0);
    assert(locais[1].id == 20);

    assert(strcmp(locais[2].nome, "Hospital") == 0);
    assert(strcmp(locais[3].nome, "Parque") == 0);
    assert(strcmp(locais[4].nome, "Shopping") == 0);

    puts("Ordenacao alfabetica: OK");
    puts("Desempate por ID: OK");

    puts("\nResultado:");

    for (int i = 0; i < 5; i++) {
        printf("%d | %s\n", locais[i].id, locais[i].nome);
    }

    Local unico[] = {
        criar_local(1, "Terminal")
    };

    merge_sort_locais(unico, 1);
    assert(strcmp(unico[0].nome, "Terminal") == 0);

    merge_sort_locais(NULL, 5);
    merge_sort_locais(locais, 0);

    puts("\nTratamento de vetor vazio e unitario: OK");
    puts("\nTODOS OS TESTES DO MERGE SORT PASSARAM!");

    return 0;
}
