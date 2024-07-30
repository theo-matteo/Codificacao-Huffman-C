#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "encoder.h"
#include "tree.h"

/* Programa criado por Theo Matteo Ferreira de Sa - ED 2024 */

int main(int argc, char const *argv[])
{
    // Verifica se o arquivo foi fornecido na linha de comando
    if (argc <= 1) {
        printf("Nao foi fornecido arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    clock_t start, end;
    start = clock();
    
    // Abre o arquivo no diretorio fornecido na linha de comando
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Falha ao abrir arquivo no caminho %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    tByteTracker** byteTrackerVector = createbyteTracker();

    // Inicializa vetor contabilizando a frequencia dos caracteres
    vectorFrequencyInit(file, byteTrackerVector);

    // Obtem a quantidade de caracteres nao repetidos 
    unsigned int size = getNumBytes(byteTrackerVector);

    // Vetor de arvores
    tTree* nodes[size];

    // Inicializa vetor de arvores alocando memoria 
    loadVectorTree(nodes, byteTrackerVector);

    // Ordena os nodes
    qsort(nodes, size, sizeof(tTree*), compareTrees);

    // Executa o algoritmo de Huffmann
    executeAlgorithm(nodes, size);

    // Referencia para a raiz da arvore completa
    tTree* root = nodes[0];

    // Obtem o path binario de cada caracter na arvore binaria e armazena no Tracker
    initBinaryPathChars(byteTrackerVector, root);

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

    // Escreve o arquivo compactado no arquivo binario
    encodeFile(file, binaryFile, byteTrackerVector);

    // Imprime arvore (proposito de depuracao)
    // printTree(root);

    // Libera arvore completa
    freeTree(root);
    free(filename);
    freebyteTracker(byteTrackerVector);

    // Fecha o arquivo de entrada
    fclose(file);
    fclose(binaryFile);
    
    
    end = clock();
    printf("Codificacao Realizada!\n");
    printf("Tempo de execucao: %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
