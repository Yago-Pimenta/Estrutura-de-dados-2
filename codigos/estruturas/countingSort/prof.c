void countingSort2(int v[], int n, int R)
{
    int valor, i;
    int *ocorr_pred, *aux;
    ocorr_pred = malloc((R + 1) * sizeof(int));
    aux = malloc(n * sizeof(int));
    for (valor = 0; valor <= R; valor++)
        ocorr_pred[valor] = 0;
    for (i = 0; i < n; i++)
    {
        valor = v[i];
        ocorr_pred[valor + 1] += 1;
    }
    // ocorr_pred[valor] é o núm. de ocorrências de valor - 1
    for (valor = 1; valor <= R; valor++)
        ocorr_pred[valor] += ocorr_pred[valor - 1];
    // ocorr_pred[valor] é o núm. de ocorrs dos predecessores de
    // valor. Logo, a cadeia de elementos iguais a valor deve
    // começar no índice ocorr_pred[valor] no vetor ordenado.
    for (i = 0; i < n; i++)
    {
        valor = v[i];
        aux[ocorr_pred[valor]] = v[i];
        ocorr_pred[valor]++; // atualiza o número de predecessores
    }
    // aux[0 .. n-1] está em ordem crescente
    for (i = 0; i < n; ++i)
        v[i] = aux[i];
    free(ocorr_pred);
    free(aux);
}