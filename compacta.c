#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "tree.h"
#define VECTOR_SIZE 128

int main(int argc, char const *argv[])
{
    // Verifica se o arquivo foi fornecido na linha de comando
    if (argc <= 1) {
        printf("Nao foi fornecido arquivo de entrada");
        exit(EXIT_FAILURE);
    }
    
    // Abre o arquivo no diretorio fornecido na linha de comando
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Falha ao abrir arquivo no caminho %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Vetor que ira armazenar as frequencias do caracteres no texto
    int vector[VECTOR_SIZE] = {0};

    // Inicializa vetor contabilizando a frequencia dos caracteres
    vectorFrequencyInit(file, vector);

    // Obtem a quantidade de caracteres nao repetidos 
    unsigned int size = getNumCharacters(vector);

    // Vetor de arvores
    tTree* nodes[size];

    // Inicializa vetor de arvores alocando memoria 
    loadVectorTree(nodes, vector);

    // Ordena os nodes
    qsort(nodes, size, sizeof(tTree*), compareTrees);

    // Executa o algoritmo
    executeAlgorithm(nodes, size);

    // Referencia para a raiz da arvore completa
    tTree* root = nodes[0];

    // Cria um arquivo binario
    char* filename = malloc(strlen(argv[1]) + strlen(".comp") + 1);
    strcpy(filename, argv[1]);
    strcat(filename, ".comp");

    FILE* binaryFile = fopen(filename, "wb");
    if (binaryFile == NULL) {
        printf("Falha ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    
    // Escreve a arvore no arquivo binario
    writeTreeBinaryFile(root, binaryFile);

    // Retorna o ponteiro do arquivo para o inicio
    fseek(file, 0, SEEK_SET);

    // Escreve a mensagem no arquivo binario
    encodeMessage(file, binaryFile, root);

    // Imprime arvore (teste)
    // printTree(root);

    // Libera arvore completa
    freeTree(nodes[0]);
    free(filename);

    // Fecha o arquivo de entrada
    fclose(file);
    fclose(binaryFile);
    return 0;
}
