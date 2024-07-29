#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "decoder.h"
#include "tree.h"

int main (int argc, char const *argv[]) {
    
    // Verifica se o arquivo foi fornecido na linha de comando
    if (argc <= 1) {
        printf("Nao foi fornecido arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    clock_t start, end;
    start = clock();

    // Abre o arquivo binario
    FILE* binaryFile = fopen(argv[1], "rb");
    if (binaryFile == NULL) {
        printf("Falha ao abrir arquivo no caminho %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Cria a arvore a partir do arquivo binario
    tTree* root = createTreeFromBinary(binaryFile);

    // Ler a sequencia de bits do arquivo binario
    decodeMessage(binaryFile, root, argv[1]);

    // printTree(root); (teste de impressao)
    freeTree(root);
    
    fclose(binaryFile);

    end = clock();
    printf("Decodificacao Realizada!\n");
    printf("Tempo de execucao: %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
