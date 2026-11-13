
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "local.h"
#include "bst.h"
#include "grafo.h"
#include "pilha.h"
#include "lista.h"
#include "ordenacao.h"

#define MAX_VERTICES 100

static void mostrar_menu(void) {
    puts("\n========================================");
    puts("          SISTEMA ROTAS URBANAS");
    puts("========================================");
    puts("1  - Cadastrar local");
    puts("2  - Buscar local");
    puts("3  - Remover local");
    puts("4  - Listar locais");
    puts("5  - Ordenar locais por nome");
    puts("6  - Adicionar conexao");
    puts("7  - Remover conexao");
    puts("8  - Consultar conexao direta");
    puts("9  - Listar locais alcancaveis (BFS)");
    puts("10 - Verificar caminho entre locais");
    puts("11 - Consultar historico de alteracoes");
    puts("0  - Encerrar");
    puts("========================================");
}

static int ler_inteiro(const char *mensagem, int *valor) {
    char entrada[128];
    char *fim;
    long numero;

    printf("%s", mensagem);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        return 0;

    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        puts("Entrada muito longa.");
        return 0;
    }

    errno = 0;
    numero = strtol(entrada, &fim, 10);

    while (isspace((unsigned char)*fim))
        fim++;

    if (fim == entrada || *fim != '\0' || errno == ERANGE ||
        numero < INT_MIN || numero > INT_MAX) {
        puts("Numero invalido.");
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

static int ler_texto(const char *mensagem, char *destino) {
    char entrada[TAM_TEXTO + 2];
    size_t inicio = 0;
    size_t fim;
    size_t tamanho;

    printf("%s", mensagem);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        return 0;

    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        puts("Texto muito longo. Limite de 79 caracteres.");
        return 0;
    }

    entrada[strcspn(entrada, "\n")] = '\0';

    tamanho = strlen(entrada);
    fim = tamanho;

    while (inicio < fim && isspace((unsigned char)entrada[inicio]))
        inicio++;

    while (fim > inicio && isspace((unsigned char)entrada[fim - 1]))
        fim--;

    if (inicio == fim) {
        puts("O campo nao pode ficar vazio.");
        return 0;
    }

    tamanho = fim - inicio;

    if (tamanho >= TAM_TEXTO) {
        puts("Texto muito longo. Limite de 79 caracteres.");
        return 0;
    }

    memcpy(destino, entrada + inicio, tamanho);
    destino[tamanho] = '\0';

    return 1;
}

static int registrar_acao(Pilha *historico, TipoAcao tipo,
                          int id1, int id2) {
    Acao acao;

    acao.tipo = tipo;
    acao.id1 = id1;
    acao.id2 = id2;

    if (!pilha_push(historico, acao)) {
        puts("Aviso: alteracao realizada, mas nao foi possivel registrar no historico.");
        return 0;
    }

    return 1;
}

static void cadastrar_local(NoBST **raiz, Grafo *grafo,
                            Pilha *historico) {
    Local local;
    int sucesso;

    puts("\n--- CADASTRO DE LOCAL ---");

    if (!ler_inteiro("ID: ", &local.id))
        return;

    if (local.id <= 0) {
        puts("O ID deve ser positivo.");
        return;
    }

    if (bst_buscar(*raiz, local.id) != NULL) {
        puts("Ja existe um local com esse ID.");
        return;
    }

    if (!ler_texto("Nome: ", local.nome) ||
        !ler_texto("Categoria: ", local.categoria) ||
        !ler_texto("Bairro: ", local.bairro))
        return;

    if (!grafo_adicionar_vertice(grafo, local.id)) {
        puts("Nao foi possivel criar o vertice. Verifique o limite de 100 locais.");
        return;
    }

    *raiz = bst_inserir(*raiz, local, &sucesso);

    if (!sucesso) {
        grafo_remover_vertice(grafo, local.id);
        puts("Erro ao cadastrar local na BST.");
        return;
    }

    registrar_acao(historico, ACAO_CADASTRO, local.id, 0);

    puts("Local cadastrado com sucesso!");
}

static void buscar_local(const NoBST *raiz) {
    int id;
    const Local *local;

    puts("\n--- BUSCAR LOCAL ---");

    if (!ler_inteiro("Informe o ID: ", &id))
        return;

    local = bst_buscar(raiz, id);

    if (local == NULL) {
        puts("Local nao encontrado.");
        return;
    }

    printf("\nID: %d\n", local->id);
    printf("Nome: %s\n", local->nome);
    printf("Categoria: %s\n", local->categoria);
    printf("Bairro: %s\n", local->bairro);
}

static void remover_local(NoBST **raiz, Grafo *grafo,
                          Pilha *historico) {
    int id;
    int sucesso;
    const Local *local;

    puts("\n--- REMOVER LOCAL ---");

    if (!ler_inteiro("Informe o ID: ", &id))
        return;

    local = bst_buscar(*raiz, id);

    if (local == NULL) {
        puts("Local nao encontrado.");
        return;
    }

    if (!grafo_remover_vertice(grafo, id)) {
        puts("Erro ao remover vertice do grafo.");
        return;
    }

    *raiz = bst_remover(*raiz, id, &sucesso);

    if (!sucesso) {
        puts("Erro ao remover registro da BST.");
        return;
    }

    registrar_acao(historico, ACAO_REMOCAO_LOCAL, id, 0);

    puts("Local e suas conexoes removidos com sucesso!");
}

static void listar_locais(const NoBST *raiz) {
    puts("\n--- LISTA DE LOCAIS ---");

    if (raiz == NULL) {
        puts("Nenhum local cadastrado.");
        return;
    }

    bst_listar_em_ordem(raiz);
}

static void ordenar_locais(const NoBST *raiz) {
    Local vetor[MAX_VERTICES];
    int quantidade = 0;

    puts("\n--- LOCAIS ORDENADOS POR NOME ---");

    if (raiz == NULL) {
        puts("Nenhum local cadastrado.");
        return;
    }

    if (!bst_copiar_vetor(raiz, vetor, MAX_VERTICES, &quantidade)) {
        puts("Erro ao copiar os registros para ordenacao.");
        return;
    }

    merge_sort_locais(vetor, quantidade);

    for (int i = 0; i < quantidade; i++) {
        printf("%d | %s | %s | %s\n",
               vetor[i].id,
               vetor[i].nome,
               vetor[i].categoria,
               vetor[i].bairro);
    }
}

static void adicionar_conexao(Grafo *grafo, Pilha *historico) {
    int id1, id2;

    puts("\n--- ADICIONAR CONEXAO ---");

    if (!ler_inteiro("ID do primeiro local: ", &id1) ||
        !ler_inteiro("ID do segundo local: ", &id2))
        return;

    if (!grafo_adicionar_aresta(grafo, id1, id2)) {
        puts("Nao foi possivel adicionar a conexao.");
        puts("Verifique os IDs, a existencia dos locais e se a conexao ja existe.");
        return;
    }

    registrar_acao(historico, ACAO_ADICAO_CONEXAO, id1, id2);

    puts("Conexao adicionada com sucesso!");
}

static void remover_conexao(Grafo *grafo, Pilha *historico) {
    int id1, id2;

    puts("\n--- REMOVER CONEXAO ---");

    if (!ler_inteiro("ID do primeiro local: ", &id1) ||
        !ler_inteiro("ID do segundo local: ", &id2))
        return;

    if (!grafo_remover_aresta(grafo, id1, id2)) {
        puts("Nao foi possivel remover a conexao.");
        return;
    }

    registrar_acao(historico, ACAO_REMOCAO_CONEXAO, id1, id2);

    puts("Conexao removida com sucesso!");
}

static void consultar_conexao(const Grafo *grafo) {
    int id1, id2;

    puts("\n--- CONSULTAR CONEXAO DIRETA ---");

    if (!ler_inteiro("ID do primeiro local: ", &id1) ||
        !ler_inteiro("ID do segundo local: ", &id2))
        return;

    if (grafo_conexao_direta(grafo, id1, id2))
        puts("Existe uma conexao direta entre os locais.");
    else
        puts("Nao existe conexao direta entre os locais.");
}

static void listar_alcancaveis(const Grafo *grafo) {
    int origem;
    Lista *resultado;

    puts("\n--- BUSCA EM LARGURA (BFS) ---");

    if (!ler_inteiro("ID do local de origem: ", &origem))
        return;

    resultado = lista_criar();

    if (resultado == NULL) {
        puts("Erro ao criar lista de resultados.");
        return;
    }

    if (!grafo_bfs(grafo, origem, resultado)) {
        puts("Nao foi possivel realizar a BFS. Verifique o ID de origem.");
        lista_liberar(resultado);
        return;
    }

    puts("Locais alcancaveis, na ordem de descoberta:");
    lista_imprimir(resultado);

    lista_liberar(resultado);
}

static void verificar_caminho(const Grafo *grafo) {
    int origem, destino;

    puts("\n--- VERIFICAR CAMINHO ---");

    if (!ler_inteiro("ID de origem: ", &origem) ||
        !ler_inteiro("ID de destino: ", &destino))
        return;

    if (grafo_existe_caminho(grafo, origem, destino))
        puts("Existe um caminho entre os locais.");
    else
        puts("Nao existe caminho entre os locais.");
}

static void consultar_historico(const Pilha *historico) {
    puts("\n--- HISTORICO DAS ULTIMAS CINCO ALTERACOES ---");
    pilha_imprimir_ultimas_cinco(historico);
}

int main(void) {
    NoBST *raiz = NULL;
    Grafo *grafo = grafo_criar();
    Pilha *historico = pilha_criar();
    int opcao;

    if (grafo == NULL || historico == NULL) {
        fprintf(stderr, "Erro ao inicializar o sistema.\n");
        bst_liberar(raiz);
        grafo_liberar(grafo);
        pilha_liberar(historico);
        return 1;
    }

    do {
        mostrar_menu();

        if (!ler_inteiro("Escolha uma opcao: ", &opcao)) {
            if (feof(stdin)) break;
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrar_local(&raiz, grafo, historico);
                break;

            case 2:
                buscar_local(raiz);
                break;

            case 3:
                remover_local(&raiz, grafo, historico);
                break;

            case 4:
                listar_locais(raiz);
                break;

            case 5:
                ordenar_locais(raiz);
                break;

            case 6:
                adicionar_conexao(grafo, historico);
                break;

            case 7:
                remover_conexao(grafo, historico);
                break;

            case 8:
                consultar_conexao(grafo);
                break;

            case 9:
                listar_alcancaveis(grafo);
                break;

            case 10:
                verificar_caminho(grafo);
                break;

            case 11:
                consultar_historico(historico);
                break;

            case 0:
                puts("Encerrando o Rotas Urbanas...");
                break;

            default:
                puts("Opcao inexistente. Escolha de 0 a 11.");
                break;
        }

    } while (opcao != 0);

    bst_liberar(raiz);
    grafo_liberar(grafo);
    pilha_liberar(historico);

    return 0;
}
