// Aluno:Yago David Pimenta
// RA:800273
// Curso:Ciência da Computação
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct grafo *Grafo;
struct grafo
{
    int **A;
    int n; // número de vértices
    int m; // número de arestas/arcos
};
Grafo inicializaGrafo(int n);
void insereArcoGrafo(Grafo G, int v, int w);
void insereArcoNaoSeguraGrafo(Grafo G, int v, int w);
void removeArcoGrafo(Grafo G, int v, int w);
void mostraGrafo(Grafo G);
void imprimeGrafo(Grafo G);
Grafo liberaGrafo(Grafo G);

Grafo inicializaGrafo(int n)
{
    int i, j;
    Grafo G = malloc(sizeof *G);
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        G->A[i] = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            G->A[i][j] = 0;
    return G;
}
/* Insere arco v-w no grafo G, supondo que v e w são inteiros
distintos entre 0 e n-1. Se grafo já tem arco v-w, não faz nada. */
void insereArcoGrafo(Grafo G, int v, int w)
{
    if (G->A[v][w] == 0)
    {
        G->A[v][w] = 1;
        G->m++;
    }
}
// Versão da insereArcoGrafo() que não testa se v-w já está presente
void insereArcoNaoSeguraGrafo(Grafo G, int v, int w)
{
    G->A[v][w] = 1;
    G->m++;
}
/* Remove arco v-w do grafo G, supondo que v e w são inteiros
distintos entre 0 e n-1. Se não existe arco v-w, não faz nada. */
void removeArcoGrafo(Grafo G, int v, int w)
{
    if (G->A[v][w] == 1)
    {
        G->A[v][w] = 0;
        G->m--;
    }
}
// Imprime, para cada vértice v, os vértices adjacentes a v.
void mostraGrafo(Grafo G)
{
    int i, j;
    for (i = 0; i < G->n; i++)
    {
        printf(" %2d : ", i);
        for (j = 0; j < G->n; j++)
            if (G->A[i][j] == 1)
                printf(" %2d ", j);
        printf("\n");
    }
}
// Versão da mostraGrafo() com impressão mais limpa
void imprimeGrafo(Grafo G)
{
    int i, j;
    for (i = 0; i < G->n; i++)
    {
        for (j = 0; j < G->n; j++)
            if (G->A[i][j] == 1)
                printf(" %2d ", j);
        printf(" -1 "); // sentinela para marcar fim de lista
        printf("\n");
    }
}
// Libera a memória alocada para o grafo G e devolve NULL.
Grafo liberaGrafo(Grafo G)
{
    int i;
    for (i = 0; i < G->n; i++)
    {
        free(G->A[i]);
        G->A[i] = NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;
}
int repetido(int *v, int size, int n)
{
    if (size == 0)
    {
        return 0;
    }
    for (int i = 0; i < size; i++)
    {
        if (v[i] == n)
            return 1;
    }
    return 0;
}
// int eseta outro grupo basta usar a rotina do repetido e passar o arr2
int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }

    /* implementar aqui */
    int n;
    fscanf(entrada, "%d", &n);

    int n2;

    for (int t = 0; t < n; t++)
    {

        fscanf(entrada, "%d", &n2);
        Grafo X = inicializaGrafo(n2);
        for (int j = 0; j < n2; j++)
        {
            int primeira;
            fscanf(entrada, "%d", &primeira);
            for (int h = 0; h < primeira; h++)
            {
                int valor;
                fscanf(entrada, "%d", &valor);
                insereArcoGrafo(X, j, valor);
            }
        }

        int zero = 0;
        //  int um = 1;
        int grupoA[X->n];
        int grupoB[X->n];
        int controle = 0;
        int controle2 = 0;
        int aux = 0;
        int aux2 = 0;
        int rejeitei = 0;
        int rejeitei2 = 0;
        //   int adicionei = 0;
        // vou tentar fazer minha solução
        for (int i = 0; i < X->n; i++)
        {

            for (int j = 0; j < X->n; j++)
            {

                if (i < j)
                {
                    if (X->A[i][j] == zero)
                    {
                        // eu tenho que comparar com todos elementos do grupo
                        if (X->A[j][i] == zero)
                        {

                            for (int t = 0; t < controle; t++)
                            {
                                int x = grupoA[t];
                                if (X->A[i][x] != zero)
                                {
                                    aux = 1;
                                    rejeitei = i;
                                }
                                if (X->A[x][i] != zero)
                                {
                                    aux = 1;
                                    rejeitei = i;
                                }
                            }
                            for (int t = 0; t < controle; t++)
                            {
                                int x = grupoA[t];
                                if (X->A[x][j] != zero)
                                {
                                    aux = 1;
                                    rejeitei2 = i;
                                }
                                if (X->A[j][x] != zero)
                                {
                                    aux = 1;
                                    rejeitei2 = i;
                                }
                            }
                            if (aux == 0)
                            {
                                if (repetido(grupoA, controle, i) == 0)
                                {
                                    grupoA[controle] = i;
                                    controle++;
                                }
                                if (repetido(grupoA, controle, j) == 0)
                                {
                                    grupoA[controle] = j;
                                    controle++;
                                }
                            }
                            // vamos fazer o seguinte colocar o rejeitei em B desde que ele nao esteja em A
                            int auxiliar = 0;
                            for (int i = 0; i < controle; i++)
                            {
                                if (rejeitei == grupoA[i] || rejeitei2 == grupoA[i])
                                {
                                    auxiliar = 1;
                                }
                            }
                            for (int t = 0; t < controle2; t++)
                            {
                                int x = grupoB[t];
                                if (X->A[i][x] != zero)
                                {
                                    auxiliar = 1;
                                }
                                if (X->A[x][i] != zero)
                                {
                                    auxiliar = 1;
                                }
                            }
                            for (int t = 0; t < controle2; t++)
                            {
                                int x = grupoB[t];
                                if (X->A[x][j] != zero)
                                {
                                    auxiliar = 1;
                                }
                                if (X->A[j][x] != zero)
                                {
                                    auxiliar = 1;
                                }
                            }
                            if (auxiliar == 0)
                            {
                                if (repetido(grupoB, controle2, rejeitei) == 0)
                                {
                                    grupoB[controle2] = rejeitei;
                                    controle2++;
                                }
                                if (repetido(grupoB, controle2, rejeitei2) == 0)
                                {
                                    grupoB[controle2] = rejeitei2;
                                    controle2++;
                                }
                            }
                        }
                    }
                }
            }
        }
        int auxiliar = 0;
        for (int t = 0; t < controle2; t++)
        {
            int x = grupoB[t];
            if (X->A[x][X->n - 1] != zero)
            {
                auxiliar = 1;
            }
            if (X->A[X->n - 1][x] != zero)
            {
                auxiliar = 1;
            }
        }
        if (auxiliar == 0)
        {
            if (repetido(grupoB, controle2, X->n - 1) == 0)
            {
                grupoB[controle2] = X->n - 1;
                controle2++;
            }
        }
        int impossivel = 0;
        int alunos[controle + controle2];

        memcpy(alunos, grupoA, sizeof(grupoA));
        memcpy(alunos + controle, grupoB, sizeof(grupoB));
        // vou ordenar em ordem crescente agora
        int auxx;
        for (int i = 0; i < controle + controle2; i++)
        {
            for (int j = 0; j < controle + controle2; j++)
            {
                if (alunos[i] < alunos[j])
                {
                    // nesta parte que ocorre a troca e ordenação de varíaveis
                    auxx = alunos[i];      // recebe o menor valor, na varável temporária aux
                    alunos[i] = alunos[j]; // repete com todos os valores no loop
                    alunos[j] = auxx;      // recebe em ordem crescente no vetor c[j]
                }
            }
        }
        for (int contagem = 0; contagem < X->n; contagem++)
        {
            if (contagem != alunos[contagem])
            {
                impossivel = 1;
            }
        }
        if (impossivel == 1)
        {
            printf("Impossivel\n");
        }
        else
        {
            printf("Vai ter debate\n");
        }

        fclose(entrada);
        return 0;
    }
