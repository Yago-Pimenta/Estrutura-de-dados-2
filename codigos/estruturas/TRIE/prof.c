#include <stdio.h>

#include <math.h>

typedef struct noh
{
    int chave;
    int conteudo;
    struct noh *esq;
    struct noh *dir;
} Noh;

Noh *buscaR(Noh* r, int chave, int digito, Noh **ppai)
{
    if (r == NULL)
        return r;
    if (r->esq == NULL && r->dir == NULL)
    { // eh uma folha
        if (r->chave == chave)
            return r;
        return NULL;
    }
    if (pegaDigito(chave, digito) == 0)
    { // desce à esquerda
        *ppai = r;
        return buscaR(r->esq, chave, digito + 1, ppai);
    }
    // pegaDigito(chave, digito) == 1 - desce à direita
    *ppai = r;
    return buscaR(r->dir, chave, digito + 1, ppai);
}

Noh* inserir(Noh* r, int chave, int conteudo)
{
    Noh *novo = novoNoh(chave, conteudo);
    return insereR(r, novo, 0);
}

Noh* insereR(Noh* r, Noh *novo, int digito)
{
    if (r == NULL) // insere folha
        return novo;
    if (r->esq == NULL && r->dir == NULL) // busca terminou em folha
        return ramifique(r, novo, digito);
    if (pegaDigito(novo->chave, digito) == 0) // desce à esquerda
        r->esq = insereR(r->esq, novo, digito + 1);
    else // pegaDigito(novo->chave, digito) == 1 - desce à direita
        r->dir = insereR(r->dir, novo, digito + 1);
    return r;
}

Noh *novoNoh(int chave, int conteudo)
{
    Noh *novo;
    novo = (Noh *)malloc(sizeof(Noh));
    novo->chave = chave;
    novo->conteudo = conteudo;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Noh* ramifique(Noh *p, Noh *q, int digito)
{
    Noh *inter; // apontador para nó intermediário
    inter = (Noh *)malloc(sizeof(Noh));
    inter->chave = -1; // apenas para impressão
    if (pegaDigito(p->chave, digito) == pegaDigito(q->chave,
                                                   digito))
    { // chaves não diferem no dígito atual
        if (pegaDigito(p->chave, digito) == 0)
        {
            // desce à esquerda do nó intermedário
            inter->dir = NULL;
            inter->esq = ramifique(p, q, digito + 1);
        }
        else
        { // pegaDigito(p->chave, digito) == 1
            // desce à direita do nó intermediário
            inter->esq = NULL;
            inter->dir = ramifique(p, q, digito + 1);
        }
    }
    else
    { // chaves diferem no dígito atual
        if (pegaDigito(p->chave, digito) == 0)
        {
            // insere p à esquerda e q à direita do nó intermediário
            inter->esq = p;
            inter->dir = q;
        }
        else
        { // pegaDigito(p->chave, digito) == 1
            // insere q à esquerda e p à direita do nó intermediário
            inter->esq = q;
            inter->dir = p;
        }
    }
    return inter;
}
