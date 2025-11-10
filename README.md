# 🏙️ Sistema de Cálculo de Vizinhança entre Cidades

Este projeto em **C** lê dados de cidades posicionadas ao longo de uma estrada e determina qual cidade possui a **menor vizinhança** — ou seja, o menor espaço médio de influência entre cidades vizinhas.

---

## 📘 Descrição

O programa:

- Lê um arquivo de entrada com o comprimento da estrada `T`, o número de cidades `N`, e depois `N` linhas com a posição e o nome de cada cidade.  
- Armazena as cidades em uma **lista encadeada** ordenada por posição.  
- Calcula a **vizinhança** de cada cidade: a distância entre os limites esquerdo e direito (pontos médios com as cidades vizinhas).  
- Retorna o **nome** da cidade com menor vizinhança (ou o valor da menor vizinhança, conforme a função utilizada).

---

## 📂 Estrutura do projeto

```
.
├── cidades.h          # Declarações das estruturas e protótipos
├── cidades.c          # Implementação das funções de manipulação e cálculo
├── main.c             # Programa principal (exemplo de uso)
├── exemplo.txt        # Arquivo de entrada de exemplo
└── README.md          # Este arquivo
```

---

## 🧮 Estruturas principais (em `cidades.h`)

```c
typedef struct Cidade {
    char Nome[256];
    int Posicao;
    struct Cidade *Proximo;
} Cidade;

typedef struct {
    int N;          // Comprimento da estrada
    int T;          // Número de cidades
    Cidade *Inicio; // Ponteiro para o início da lista encadeada
} Estrada;
```

---

## ⚙️ Funções importantes (em `cidades.c`)

- `Estrada *getEstrada(const char *nomeArquivo)`  
  Lê o arquivo e retorna um ponteiro para `Estrada` preenchida (ou `NULL` em erro).

- `void inserirCidade(Estrada *estrada, char *nome, int posicao)`  
  Insere uma cidade na lista de forma ordenada por posição.

- `double calcularVizinhanca(Estrada *estrada, Cidade *cidade)`  
  Calcula o intervalo da vizinhança de uma cidade.

- `double calcularMenorVizinhanca(const char *nomeArquivo)`  
  Retorna o valor da menor vizinhança entre todas as cidades do arquivo (ou `-1.0` em erro).

- `char *cidadeMenorVizinhanca(const char *nomeArquivo)`  
  Retorna uma string alocada com o nome da cidade que tem a menor vizinhança (ou `NULL` em erro).  
  **Responsabilidade do chamador liberar a memória.**

---

## 📄 Formato do arquivo de entrada

O arquivo deve seguir este formato:

```
<T>
<N>
<X1> <Nome da Cidade 1>
<X2> <Nome da Cidade 2>
...
<XN> <Nome da Cidade N>
```

**Exemplo (`exemplo.txt`):**

```
100
4
10 Cidade A
35 Cidade B
70 Cidade C
90 Cidade D
```

**Regras e validações implementadas:**

- `3 <= T <= 1000000`
- `2 <= N <= 10000`
- `0 < Xi < T` para cada posição Xi
- Não são permitidas cidades com posições duplicadas
- Nomes podem conter espaços (lidos até o fim da linha)

---

## ▶️ Compilação e execução

Exemplo mínimo para compilar (assumindo `main.c`, `cidades.c` e `cidades.h`):

```bash
gcc main.c cidades.c -o programa
./programa
```

No `main.c` de exemplo, faça a leitura do nome do arquivo de entrada e chame  
`cidadeMenorVizinhanca()` ou `calcularMenorVizinhanca()` para exibir o resultado.

---

## 🧑‍💻 Autor

Desenvolvido por **Pablo Henrique A. de Souza & Gustavo Almeida de Sousa**  
Projeto de prática de **Estruturas de Dados em C**.

---
