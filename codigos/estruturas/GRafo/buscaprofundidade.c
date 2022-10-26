#include <stdio.h>
#include "grafosMatrizAdj.h"
void buscaProfI(Grafo G, int origem, int *ordem_chegada,
                int *ordem_saida, int tempo)
{
    int v, w;
    // pilha implementada em vetor
    int *pilha;
    int topo = 0;
    pilha = malloc(G->m * sizeof(int));
    /* colocando a origem na pilha */
    pilha[topo++] = origem;
    /* enquanto a pilha dos ativos (encontrados
    mas não visitados) não estiver vazia */
    while (topo > 0)
    {
        /* remova o mais recente da pilha */
        v = pilha[--topo];
        if (ordem_chegada[v] == -1)
        { // se v não foi visitado
            ordem_chegada[v] = tempo++;
            pilha[topo++] = v; // Quiz2: por que empilhar v aqui?
            /* para cada vizinho de v que ainda não foi visitado */
            for (w = 0; w < G->n; w++)
                if (G->A[v][w] == 1 && ordem_chegada[w] == -1)
                    pilha[topo++] = w; // empilha o vizinho
        }
        else if (ordem_saida[v] == -1)
            ordem_saida[v] = tempo++;
    }
    free(pilha);
}