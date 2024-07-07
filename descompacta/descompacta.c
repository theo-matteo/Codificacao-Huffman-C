#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tree.h"

int main (int argc, char const *argv[]) {
    
    // Verifica se o arquivo foi fornecido na linha de comando
    if (argc <= 1) {
        printf("Nao foi fornecido arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Abre o arquivo binario
    FILE* binaryFile = fopen(argv[1], "rb");
    if (binaryFile == NULL) {
        printf("Falha ao abrir arquivo no caminho %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    tTree* root = createTreeFromBinary(binaryFile);
    printTree(root);

    freeTree(root);

    
    fclose(binaryFile);
    return EXIT_SUCCESS;
}
