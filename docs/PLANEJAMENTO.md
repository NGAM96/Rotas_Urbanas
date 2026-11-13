# Documentação técnica — Rotas Urbanas

## Dados de um local

Cada registro contém:
- `id`: inteiro positivo e único;
- `nome`: texto com até 79 caracteres;
- `categoria`: texto com até 79 caracteres;
- `bairro`: texto com até 79 caracteres.

## Organização das estruturas

- BST indexada pelo ID para armazenar e consultar locais.
- Grafo não direcionado representado por lista de adjacência.
- Fila dinâmica para controlar a BFS.
- Lista encadeada para armazenar a ordem de descoberta da BFS.
- Pilha dinâmica para manter o histórico de ações.
- Merge Sort aplicado a um vetor auxiliar de cópias dos registros.

## Regras da BFS

- Marcar o vértice como visitado ao enfileirá-lo.
- Processar os vizinhos em ordem crescente de ID.
- Incluir a origem no resultado.
- Acrescentar os IDs descobertos ao final da lista de resultado.

## Ordenação

O Merge Sort compara os nomes com `strcmp`. Quando os nomes são iguais, utiliza o ID crescente como critério de desempate. A ordenação ocorre em vetor auxiliar e não altera a BST.

## Compilação e testes

As instruções reproduzíveis estão no arquivo `README.md`. Utilize `make` para compilar, `make run` para executar, `make test` para executar os testes e `make clean` para remover os artefatos gerados.
