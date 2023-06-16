#include <stdio.h> //I/O
#include <stdbool.h> // 0/1 -> false/true
#include <stdlib.h>  // malloc, sizeof, free

#define TAMANHO 10
#define MAX 100

typedef struct
{
    int vetor[TAMANHO];
    int topo;
} Pilha;

void startStack(Pilha *p)
{
    p->topo = 0;
}

bool isEmpty(Pilha *p)
{
    return(p->topo == 0);
}

bool isFull(Pilha *p)
{
    return(p->topo == TAMANHO);
}

void push(Pilha *p, int x)
{
    if(!isFull(p))
    {
        p->vetor[p->topo] = x;
        p->topo++;
    }
    else
    {
        printf("Pilha cheia!");
    }
}

void printStack(Pilha *p)
{
    printf("Pilha = [");
    int i;
    for(i=0; i<p->topo; i++)
    {
        printf("%d ", p->vetor[i]);
    }
    printf("]\n");
}

void pop(Pilha *p)
{
    if(!isEmpty(p))
    {
        p->topo--;
    }
    else
    {
        printf("Pilha vazia!\n");
    }

}

FILE *abrirArq(char *nomeArq) {
    FILE *arquivo = fopen(nomeArq, "rt");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return NULL;
    }

    return arquivo;
}

int lerDados(FILE *arquivo, int *numeros) {
    int i = 0, num;

    while (fscanf(arquivo, "%d", &num) == 1 && i < MAX) {
        numeros[i] = num;
        i++;
    }

    return i;
}

int main(int argc, char* argv[])
{

    //valida argumentos
    if(argc != 3) {
        printf("ERRO, número de argumentos inválido.");
        return 1;
    }

    //inicia pilha
    Pilha pilha;
    startStack(&pilha);

    //abertura de arquivos
    FILE *arq;
    arq = abrirArq(argv[1]);
    FILE *arqGravar = fopen(argv[2], "r+");
    if(arqGravar == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    //leitura de dados
    int vetorDec[MAX];
    int n;

    n = lerDados(arq, vetorDec);

    //validar erro na leitura
    if(n == 0) {
        printf("Erro na leitura do arquivo.\n");
        printf("O arquivo pode estar com valores incorretos ou pode estar vazio.\n");
        return 1;
    }

    //iteração por n numeros lidos
    printf("Foram lidos %d números do arquivo:\n", n);
    for (int i = 0; i < n; i++) {

        //int contador = 0;

        if(vetorDec[i] == 0) {
            push(&pilha, 0);
        }

        //lógica do binário
        while(vetorDec[i] != 0) {
            push(&pilha, vetorDec[i] % 2);
            vetorDec[i] = vetorDec[i] / 2;
        }

        printStack(&pilha);

        while(!isEmpty(&pilha)) {
            fprintf(arqGravar, "%d", pilha.vetor[pilha.topo - 1]);
            pop(&pilha);
        }

        fprintf(arqGravar, "\n");
    }

    fclose(arqGravar);
    FILE *arqInvertido = fopen(argv[2], "r+");

    int numerosVetor[n];
    for(int i = 0; i < n; i++) {
        fscanf(arqInvertido, "%d", &numerosVetor[i]);
    }

    rewind(arqInvertido);

    for(int i = n - 1; i >= 0; i--) {
        fprintf(arqInvertido, "%d\n", numerosVetor[i]);
    }

    fclose(arq);
    fclose(arqInvertido);

    return 0;
}
