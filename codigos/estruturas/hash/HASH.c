#include <stdio.h>
#include <stdlib.h>
#include "HASH.h"

struct hash{
     int qtd , TABLE_SIZE;
     struct aluno **itens; //atenção aqui ,a hash mora aqui que é um vetor de vetor
};
//vamos fazer uma abordagem de alocar a memoria a cada operação

//IMPLEMENTAÇÃO
Hash* criaHash(int TABLE_SIZE){
    Hash* ha = (Hash*)malloc(sizeof(Hash));
    if(ha != NULL){//ou seja deu certo a alocação de memoria
        int i;
        ha->TABLE_SIZE = TABLE_SIZE ;
        ha->itens = (struct aluno**)malloc(TABLE_SIZE * sizeof(struct aluno*));//estou alocando o vetor de vetores

        if(ha->itens == NULL ){ //a alocação do vetor de vetor nao deu certo
            free(ha);
            return NULL;
        }
        ha->qtd = 0; //eu acabei de criar obviamente ta vazia

        for(i=0;i<ha->TABLE_SIZE;i++){
            ha->itens[i] = NULL ; // setando cada celula como nula
        }}return ha;
    //OBS: para escolher tamanho da hash o ideal é escolher tamanho impar
}

void liberaHash(Hash* ha){
    if(ha!=NULL){
        int i;
        for(i=0;i<ha->TABLE_SIZE;i++){
            if(ha->itens[i]!=NULL){
                free(ha->itens[i]);
            }
        }free(ha->itens);
        free(ha);
    }
}

//vamos utilizar o metodo da congruencia linear para implementar essa função hashing
//esse é conguencia da  divisão mas poderia ser multiplicação por um primo qualquer
int espalhamento(int chave,int TABLE_SIZE){
    return(chave *0.6180339887  )
    return (chave & 0x7FFFFFFF)%TABLE_SIZE;//esse & sinal vai ser um AND
}

//tratando uma string como chave

int main(){
printf("Hello World!\n");
	

return 0;
}
