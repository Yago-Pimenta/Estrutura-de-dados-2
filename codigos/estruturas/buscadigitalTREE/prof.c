#include <stdio.h>
#include <math.h>
//esse código é apenaas se a busca for binaria nao vale para qualquer situação
typedef int Item;
typedef int Chave;
const int bitsPalavra = 32; //altura da arvore int32
const int bitsDigito = 1; //;vamos pegar um por vez 
const int digitosPalavra = bitsPalavra / bitsDigito;
const int Base = 1 << bitsDigito; // Base = 2^bitsDigito
int pegaDigito(int chave, int digito)
{
    return (int)((chave >>
                  (bitsDigito * (digitosPalavra - 1 - digito))) &
                 (Base - 1));
}
typedef struct noh
{
    Chave chave;
    Item conteudo;
    struct noh *esq;
    struct noh *dir;
} Noh;
typedef Noh *Arvore;
Noh *buscaR(Arvore r, Chave chave, int digito, Noh **ppai)
{
    if (r == NULL)
        return r;
    if (r->chave == chave)
        return r;
    if (pegaDigito(chave, digito) == 0)
    {
        *ppai = r;
        return buscaR(r->esq, chave, digito + 1, ppai);
    }
    // pegaDigito(chave, digito) == 1
    *ppai = r;
    return buscaR(r->dir, chave, digito + 1, ppai);
}
Noh *novoNoh(Chave chave, Item conteudo)
{
    Noh *novo;
    novo = (Noh *)malloc(sizeof(Noh));
    novo->chave = chave;
    novo->conteudo = conteudo;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
Arvore insereR(Arvore r, Noh *novo, int digito)
{
    if (r == NULL)
        return novo;
    if (pegaDigito(novo->chave, digito) == 0)
        r->esq = insereR(r->esq, novo, digito + 1);
    else // pegaDigito(novo->chave, digito) == 1
        r->dir = insereR(r->dir, novo, digito + 1);
    return r;
}
Arvore inserir(Arvore r, Chave chave, Item conteudo)
{
    Noh *novo = novoNoh(chave, conteudo);
    return insereR(r, novo, 0);
}
Arvore removeRaiz(Arvore alvo)
{
    Noh *aux = NULL, *pai = NULL;
    if (alvo->esq == NULL && alvo->dir == NULL)
    { // se eh folha
        free(alvo);
        return NULL;
    }
    // se nao eh folha
    aux = alvo;
    while (aux->dir != NULL || aux->esq != NULL)
    {
        pai = aux;
        if (aux->dir != NULL)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    // aux chegou numa folha
    alvo->chave = aux->chave;
    alvo->conteudo = aux->conteudo;
    if (pai->esq == aux)
        pai->esq = removeRaiz(aux);
    else // pai->dir == aux
        pai->dir = removeRaiz(aux);
    return alvo;
}
Arvore remover(Arvore r, Chave chave)
{
    Noh *alvo, *aux, *pai = NULL;
    alvo = buscaR(r, chave, 0, &pai);
    if (alvo == NULL) // não achou
        return r;
    aux = removeRaiz(alvo);
    if (alvo == r) // removeu a raiz da árvore
        return aux;
    if (pai->esq == alvo)
        pai->esq = aux;
    if (pai->dir == alvo)
        pai->dir = aux;
    return r;
}