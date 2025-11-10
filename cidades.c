#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

void inserirCidade(Estrada *estrada, char *nome, int posicao);
double calcularVizinhanca(Estrada *estrada, Cidade *cidade);

// Função auxiliar para inserir cidade na lista (ordenada por posição)
void inserirCidade(Estrada *estrada, char *nome, int posicao) {
    Cidade *nova = (Cidade *)malloc(sizeof(Cidade));
    if (nova == NULL) return;
    
    strcpy(nova->Nome, nome);
    nova->Posicao = posicao;
    nova->Proximo = NULL;
    
    // Se a lista está vazia ou deve inserir no início
    if (estrada->Inicio == NULL || estrada->Inicio->Posicao > posicao) {
        nova->Proximo = estrada->Inicio;
        estrada->Inicio = nova;
        return;
    }
    
    // Procurar posição correta (ordenado por posição)
    Cidade *atual = estrada->Inicio;
    while (atual->Proximo != NULL && atual->Proximo->Posicao < posicao) {
        atual = atual->Proximo;
    }
    
    nova->Proximo = atual->Proximo;
    atual->Proximo = nova;
}

// Função auxiliar para calcular a vizinhança de uma cidade
double calcularVizinhanca(Estrada *estrada, Cidade *cidade) {
    double vizinhanca = 0.0;
    double limiteEsquerdo, limiteDireito;
    
    // Encontrar cidade anterior e próxima
    Cidade *anterior = NULL;
    Cidade *proximo = NULL;
    
    Cidade *atual = estrada->Inicio;
    while (atual != NULL) {
        if (atual->Posicao < cidade->Posicao) {
            anterior = atual;
        }
        if (atual->Posicao > cidade->Posicao && proximo == NULL) {
            proximo = atual;
        }
        atual = atual->Proximo;
    }
    
    // Calcular limite esquerdo
    if (anterior == NULL) {
        limiteEsquerdo = 0.0;
    } else {
        // Ponto médio entre anterior e cidade atual
        limiteEsquerdo = (anterior->Posicao + cidade->Posicao) / 2.0;
    }
    
    // Calcular limite direito
    if (proximo == NULL) {
        limiteDireito = estrada->T;
    } else {
        // Ponto médio entre cidade atual e próxima
        limiteDireito = (cidade->Posicao + proximo->Posicao) / 2.0;
    }
    
    vizinhanca = limiteDireito - limiteEsquerdo;
    return vizinhanca;
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }
    
    int T, N;
    
    // Ler comprimento da estrada
    if (fscanf(arquivo, "%d", &T) != 1) {
        fclose(arquivo);
        return NULL;
    }
    
    // Ler número de cidades
    if (fscanf(arquivo, "%d", &N) != 1) {
        fclose(arquivo);
        return NULL;
    }
    
    // Verificar restrições
    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }
    
    // Criar estrutura da estrada
    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }
    
    estrada->T = T;
    estrada->N = N;
    estrada->Inicio = NULL;
    
    // Ler cidades
    for (int i = 0; i < N; i++) {
        int posicao;
        char nome[256];
        
        // Ler posição e nome completo (incluindo espaços)
        if (fscanf(arquivo, "%d %255[^\n]", &posicao, nome) != 2) {
            fclose(arquivo);
            return NULL;
        }
        
        // Remover espaço inicial do nome (se houver)
        char *nomePtr = nome;
        while (*nomePtr == ' ' || *nomePtr == '\t') {
            nomePtr++;
        }
        
        // Verificar restrições: 0 < Xi < T
        if (posicao <= 0 || posicao >= T) {
            fclose(arquivo);
            return NULL;
        }
        
        // Verificar se já existe cidade com mesma posição
        Cidade *atual = estrada->Inicio;
        while (atual != NULL) {
            if (atual->Posicao == posicao) {
                fclose(arquivo);
                return NULL;
            }
            atual = atual->Proximo;
        }
        
        // Inserir cidade na lista ordenada
        inserirCidade(estrada, nomePtr, posicao);
    }
    
    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1.0;
    }
    
    double menorVizinhanca = -1.0;
    Cidade *atual = estrada->Inicio;
    
    while (atual != NULL) {
        double vizinhanca = calcularVizinhanca(estrada, atual);
        
        if (menorVizinhanca < 0 || vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
        
        atual = atual->Proximo;
    }

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }
    
    double menorVizinhanca = -1.0;
    char nomeMenor[256] = "";
    Cidade *atual = estrada->Inicio;
    
    while (atual != NULL) {
        double vizinhanca = calcularVizinhanca(estrada, atual);
        
        if (menorVizinhanca < 0 || vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            strcpy(nomeMenor, atual->Nome);
        }
        
        atual = atual->Proximo;
    }

    
    // Alocar memória para retornar o nome
    char *resultado = (char *)malloc(strlen(nomeMenor) + 1);
    if (resultado != NULL) {
        strcpy(resultado, nomeMenor);
    }
    
    return resultado;
}