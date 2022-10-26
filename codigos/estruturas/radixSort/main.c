// LSD
#include <stdio.h>
#include <stdlib.h>
// para string
void ordenacaoDigital(char *v[], int n, int W)
{
    int *ocorr_pred, digito, valor, i, R = 256;
    char **aux;
    ocorr_pred = malloc((R + 1) * sizeof(int));
    aux = malloc(n * sizeof(char *));
    for (digito = W - 1; digito >= 0; digito--)
    {
        // basicamente o algoritmo do couting sort
        for (valor = 0; valor <= R; valor++)
            ocorr_pred[valor] = 0;
        for (i = 0; i < n; i++)
        {
            valor = v[i][digito];
            ocorr_pred[valor + 1] += 1;
        } // ocorr_pred[valor] é o # de ocorrências de valor - 1
        for (valor = 1; valor <= R; valor++)
            ocorr_pred[valor] += ocorr_pred[valor - 1];
        // ocorr_pred[valor] é o # de ocor. dos pred. de valor
        for (i = 0; i < n; i++)
        {
            valor = v[i][digito];
            aux[ocorr_pred[valor]] = v[i];
            ocorr_pred[valor]++; // atualiza número de predecessores
        }
        // aux[0..n-1] está em ordem crescente considerando
        // apenas os digitos entre digito e W - 1
        for (i = 0; i < n; i++)
            v[i] = aux[i];
    }
    free(ocorr_pred);
    free(aux);
    // para inteiros
}
const int bitsPalavra = 32;
const int bitsDigito = 8;
const int digitosPalavra = bitsPalavra / bitsDigito;
const int Base = 1 << bitsDigito;
int pegaDigito2(int chave, int digito)
{

    return (int)(chave /
                 exp2(bitsDigito * (digitosPalavra - 1 - digito))) %
           Base;
}
void LSDradixSort(int v[], int n)
{
    int digito, valor, i;
    int *ocorr_pred, *aux;
    ocorr_pred = malloc((Base + 1) * sizeof(int));
    aux = malloc(n * sizeof(int));
    for (digito = digitosPalavra - 1; digito >= 0; digito--)
    {
        for (valor = 0; valor <= Base; valor++)
            ocorr_pred[valor] = 0;
        for (i = 0; i < n; i++)
        {
            valor = pegaDigito(v[i], digito);
            ocorr_pred[valor + 1] += 1;
        }
        // agora ocorr_pred[valor] é o # de ocorrências de valor - 1
        for (valor = 1; valor <= Base; valor++)
            ocorr_pred[valor] += ocorr_pred[valor - 1];
        // agora ocorr_pred[valor] é o número de
        // ocorrências dos predecessores de valor.
        // Logo, a sequência de elementos iguais a valor
        // deve começar no índice ocorr_pred[valor].
        for (i = 0; i < n; ++i)
        {
            // note a diferença entre o valor analisado e copiado
            valor = pegaDigito(v[i], digito);
            aux[ocorr_pred[valor]] = v[i];
            ocorr_pred[valor]++; // atualiza o # de predecessores
        }
        // aux[0..n-1] está em ordem crescente considerando
        // apenas os digitos entre digito .. digitosPalavra - 1
        for (i = 0; i < n; i++)
            v[i] = aux[i];
    }
}
free(ocorr_pred);
free(aux);
