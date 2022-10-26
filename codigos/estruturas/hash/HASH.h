struct aluno
{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};
typedef struct hash Hash;
Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);
int valorString(char *str);
int insereHash_SemColisao(Hash *ha, struct aluno a1);
int buscaHash_SemColisao(Hash *ha, int mat, struct aluno *a1);
int insereHash_EnderAberto(Hash *ha, struct aluno a1);
int buscaHash_EnderAberto(Hash *ha, int mat, struct aluno *a1); // a diferença que se pode observar de cara
//é que quando vamos pegar o endereço precisamos referenciar a struct aluno como endereço