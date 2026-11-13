# Rotas Urbanas

Aplicação de terminal desenvolvida em linguagem C (padrão C11) para cadastrar locais urbanos e representar conexões entre eles. O projeto foi elaborado para a disciplina de Estrutura de Dados da FATEC Ribeirão Preto.

## Funcionalidades

- Cadastrar, consultar, listar e remover locais.
- Registrar e remover conexões entre locais.
- Consultar conexão direta e verificar a existência de caminho.
- Percorrer locais alcançáveis por meio da busca em largura (BFS).
- Ordenar locais alfabeticamente pelo nome, com desempate pelo ID.
- Consultar o histórico das cinco operações mais recentes.

## Estruturas e algoritmos

- **Árvore Binária de Busca (BST):** organiza os locais pelo ID.
- **Lista encadeada:** armazena os resultados da BFS.
- **Fila dinâmica:** controla a ordem de visitação na BFS.
- **Pilha dinâmica:** mantém o histórico de operações.
- **Grafo com lista de adjacência:** representa as conexões não direcionadas entre locais.
- **Busca em largura (BFS):** identifica os vértices alcançáveis a partir de uma origem.
- **Merge Sort:** ordena uma cópia dos registros pelo nome e, em caso de empate, pelo ID.

A BST e uma estrutura linear dinâmica compõem o núcleo do trabalho. Grafo/BFS e Merge Sort foram mantidos como funcionalidades adicionais já implementadas, conforme as orientações posteriores do docente.

## Organização dos arquivos

```text
Rotas Urbanas/
├── include/       # Interfaces dos módulos (.h)
├── src/           # Implementações e programa principal (.c)
├── tests/         # Testes dos módulos
├── docs/          # Relatório técnico e documentação
├── Makefile       # Compilação e execução dos testes
├── README.md
└── .gitignore
```

## Requisitos

- GCC com suporte ao padrão C11.
- GNU Make (para utilizar os comandos do Makefile).
- Terminal compatível com os comandos do ambiente utilizado.

## Compilar e executar

Na pasta raiz do projeto:

```bash
make
```

O executável será criado em `build/rotas_urbanas.exe`.

Para iniciar o programa:

```bash
make run
```

Também é possível compilar diretamente, sem Make:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/*.c -o rotas_urbanas.exe
```

No Windows PowerShell, se a compilação direta acima foi utilizada, execute com:

```powershell
.\rotas_urbanas.exe
```

Se estiver utilizando o Makefile com MinGW, o executável ficará em `build/rotas_urbanas.exe`; nesse caso, utilize `make run` em um terminal com GNU Make.

## Executar os testes

Para compilar e executar todos os testes automatizados:

```bash
make test
```

O comando cria os executáveis de teste dentro de `build/` e executa, em sequência:

1. `tests/test_estruturas.c` — lista, fila e pilha.
2. `tests/test_bst.c` — inserção, busca, percurso e remoção na árvore.
3. `tests/test_grafo.c` — vértices, arestas, BFS, caminhos e limite de capacidade.
4. `tests/test_ordenacao.c` — Merge Sort, ordem alfabética e desempate por ID.

Para remover os executáveis e arquivos de compilação gerados:

```bash
make clean
```

## Limitações conhecidas

- O grafo aceita até 100 vértices simultâneos.
- A BST não possui balanceamento automático; seu desempenho depende da distribuição dos IDs inseridos.
- O programa é executado em terminal e não utiliza interface gráfica.

## Documentação

O relatório técnico está disponível em `docs/Relatorio_Tecnico_Rotas_Urbanas.pdf`.

## Informações acadêmicas

- **Instituição:** FATEC Ribeirão Preto
- **Curso:** Análise e Desenvolvimento de Sistemas
- **Disciplina:** Estrutura de Dados
- **Projeto:** Rotas Urbanas
