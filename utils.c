#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


static int getNumItensVector(tTree* nodes [], unsigned int size_nodes) {
    int counter = 0;
    for (int i = 0; i < size_nodes; i++) 
        if (nodes[i] != NULL) counter++;
    return counter;
}

unsigned int getNumCharacters(int* vector) {
    int counter = 0;
    for (int i = 0; i < VECTOR_SIZE; i++)
        if (vector[i] != 0) counter++;
    return counter;
}

void loadVectorTree (tTree* nodes [], int* vector) {

    int index = 0;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        if (vector[i] != 0) {
            // Cria uma nova arvore
            tTree* tree = createTree();
            setChar(tree, i);
            setPeso(tree, vector[i]);

            // Adiciona no vetor de arvores
            nodes[index] = tree;
            index++;
        }
    }
}

void executeAlgorithm(tTree* nodes [], unsigned int size) {

    while (getNumItensVector(nodes, size) >= 2) {

        // Cria uma nova arvore
        tTree* new = createTree();
        tTree* tree1 = nodes[0];
        tTree* tree2 = nodes[1];

        // Remove os dois primeiros itens da lista
        nodes[0] = NULL;
        nodes[1] = NULL;

        // Adiciona os dois novos nos na nova arvore
        setLeftNode(new, tree1);
        setRightNode(new, tree2);

        // Configura atributos
        setPeso(new, getPeso(tree1) + getPeso(tree2));
        unsetLeafTree(new);

        // Adiciona a nova arvore no array
        nodes[0] = new;

        qsort(nodes, size, sizeof(tTree*), compareTrees);
    }
}

void encodeMessage (FILE* file, FILE* binaryFile, tTree* root) {

    // Flag para indicar se o caractere foi encontrado
    int* flag = (int*) calloc(1, sizeof(int));

    int size_tree = getSizeTree(root);
    bitmap* b = bitmapInit(size_tree - 1);
    searchTree(root, 'o', b, flag);

    // Inverte bits do bitmap criando um novo mapa de bits
    bitmap* new = bitmapInit(size_tree - 1);

    for (int i = bitmapGetLength(b) - 1; i >= 0; i--) 
        bitmapAppendLeastSignificantBit(new, bitmapGetBit(b, i));
    bitmapLibera(b);

    for (int i = 0; i < bitmapGetLength(new); i++) 
        printf("%d ", bitmapGetBit(new, i));
    
    
    
    bitmapLibera(new);
    free(flag);

    /* 
    int size_tree = getSizeTree(root);

    char c;
    while ( (c = getc(file)) != EOF) {
        bitmap* b = bitmapInit(size_tree - 1);
        bitmapLibera(b);
    }
    */
        

}

