// Yago David Pimenta
// Bacharelado em Ciências da Computação
// 800273

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
// funcao que imprime , dada pelo professor
void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}
// funcao que vai contar as inversoes , tirada do material do professor

/*unsigned long long intercalaContando(int v[], int p, int q, int r)
{
    int i, j, k, tam;
    unsigned long long num_inv = 0;
    i = p;
    j = q;
    k = 0;
    tam = r - p;
    int *w = malloc(tam * sizeof(int));
    while (i < q && j < r)
    {
        if (v[i] <= v[j])
            w[k++] = v[i++];
        else
        { // v[i] > v[j]
            w[k++] = v[j++];
            num_inv += q - i;
        }
    }
    while (i < q)
        w[k++] = v[i++];
    while (j < r)
        w[k++] = v[j++];
    for (k = 0; k < tam; k++)
        v[p + k] = w[k];
    free(w);
    return num_inv;
}
*/

// funcao que tem complexidade O(n*n) , por isso nao vai rodar para casos muito grandes

/*unsigned long long getInvCount(int arr[], int n)
{
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;

    return inv_count;
}*/

//-----FUNCAO USADA -------
unsigned long long __mergeSort(int v[], int temp[], int esq, int dir);
unsigned long long merge(int v[], int temp[], int esq, int mid,
                         int dir);

/* Essa funcao vai ordenar o vetor de entrada e retornar o número de
inversoes no array , vai estar na funcao main e vai chamar funcoes intermediarias */
unsigned long long merge_Sort(int v[], int tam_vetor)
{
    int *temp = (int *)malloc(sizeof(int) * tam_vetor);
    return __mergeSort(v, temp, 0, tam_vetor - 1);
}

/*
funcao auxiliar que vai retornar o numero de inv
*/
unsigned long long __mergeSort(int v[], int temp[], int esq, int dir)
{
    unsigned long long meio, inv_count = 0;

    if (dir > esq)
    {

        // divide o array em duas partes e chama a funcao para contar
        meio = (dir + esq) / 2;

        // as inversoes será a soma das inversoes da parte esquerda e da direita e o numero de inversoes
        // na juncao
        // lado esquerdo(funcao recursiva)
        inv_count += __mergeSort(v, temp, esq, meio);
        // direito
        inv_count += __mergeSort(v, temp, meio + 1, dir);

        // fazendo um merge
        inv_count += merge(v, temp, esq, meio + 1, dir);
    }
    return inv_count;
}

// essa funcao vai juntar dois arrays ordenados e retornar a inversão deles
unsigned long long merge(int v[], int temp[], int esq, int mid,
                         int dir)
{
    int i, j, k;
    unsigned long long inv_count = 0;

    i = esq; /*  i é o index do lado esquerdo do subarray*/
    j = mid; /* i é o index do lado direito do subarray*/
    k = esq; /* i é o index da junção  dos subarrays*/
    while ((i <= mid - 1) && (j <= dir))
    {
        if (v[i] <= v[j])
        {

            temp[k++] = v[i++];
        }
        else
        {

            temp[k++] = v[j++];

            /*contando as inversões*/
            inv_count = inv_count + (mid - i);
        }
    }

    // copiando os elementos restantes do lado esquerdo do subarray para o vetor temporario
    while (i <= mid - 1)
        temp[k++] = v[i++];

    // copiando os elementos restantes do lado direito do subarray para o vetor temporario
    while (j <= dir)
        temp[k++] = v[j++];

    // copiando de volta a junção dos elementos para o array original
    for (i = esq; i <= dir; i++)
        v[i] = temp[i];

    return inv_count;
}

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;
    int i, n;
    unsigned long long num_inv = 0;

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
    // lendo do arquivo da instância
    fscanf(entrada, "%d", &n);
    //  printf("Cheguei ate aqui , o valor de n eh %d \n ", n);
    int *v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v[i]);
    // imprime(v, n);
    num_inv = 0;

    num_inv = merge_Sort(v, n);
    // num_inv = getInvCount(v, n);
    //  printf("%I64u\n", num_inv);
    printf("%llu\n", num_inv);

    fclose(entrada);
    return 0;
}