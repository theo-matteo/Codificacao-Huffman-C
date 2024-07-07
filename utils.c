#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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

    // Bitmap que contera a messagem completa
    bitmap* message = NULL;


    char c;
    while ( (c = getc(file)) != EOF) {

        // Atualiza flag
        *flag = 0;

        // Obtem o codigo binario do caracter realizando a busca na arvore
        bitmap* b = bitmapInit(size_tree - 1);
        searchTree(root, c, b, flag);

        // Inverte os bits
        bitmap* b_inverted = bitmapInit(size_tree - 1);
        for (int i = bitmapGetLength(b) - 1; i >= 0; i--) 
            bitmapAppendLeastSignificantBit(b_inverted, bitmapGetBit(b, i));
        bitmapLibera(b);

        // Imprime o codigo binario do caracter
        /* 
        printf("%c ", c);
        for (int i = 0; i < bitmapGetLength(b_inverted); i++) {
            printf("%d", bitmapGetBit(b_inverted, i));
        }
        printf("\n");
        */

        // Adiciona o codigo binario no bitmap da mensagem 
        if (message == NULL) {
            message = b_inverted;
        }
        else {

            // Aumenta espaco do message
            // bitmap* new_message = bitmapInit(bitmapGetMaxSize(message) + bitmapGetMaxSize(b_inverted));
            bitmap* new_message = bitmapInit(bitmapGetLength(message) + bitmapGetLength(b_inverted));

            // Copia o conteudo do message para o new_message
            for (int i = 0; i < bitmapGetLength(message); i++) 
                bitmapAppendLeastSignificantBit(new_message, bitmapGetBit(message, i));
            
            // Copia o conteudo do b_inverted para o new_message
            for (int i = 0; i < bitmapGetLength(b_inverted); i++) 
                bitmapAppendLeastSignificantBit(new_message, bitmapGetBit(b_inverted, i));

        
            bitmapLibera(message);
            bitmapLibera(b_inverted);

            // Atualiza message
            message = new_message;
        }
    }

    // Salva mensagem no arquivo binario 
    unsigned char* conteudo = bitmapGetContents(message);

    // Arredonda o numero de bits da mensagem
    int bits = bitmapGetLength(message);
    while (bits % 8 != 0) bits++;

    // Escreve o conteudo do bitmap no arquivo binario
    for (int i = 0; i < bits / 8; i++)
        fwrite(&conteudo[i], sizeof(unsigned char), 1, binaryFile);

    // Adiciona o pseudocaracter no fim do arquivo binario
    char pseudocaracter = '\0';
    fwrite(&pseudocaracter, sizeof(char), 1, binaryFile);

    /* 
    printf("Bitmap length: %d\n", bitmapGetLength(message));
    for (int i = 0; i < bitmapGetLength(message); i++) {
        printf("%d", bitmapGetBit(message, i));
    }
    printf("\n");	
    */



    bitmapLibera(message);
    free(flag);
}

void decodeMessage (FILE* binaryfile, tTree* root) {

    // Le cada caracter armazenado no arquivo binario
    unsigned char c;

    // Mensagem que sera decodificada
    bitmap* message = NULL;

    // Enquanto a leitura for bem sucedida e nao chegou no pseudocaracter
    while (fread(&c, sizeof(unsigned char), 1, binaryfile) && c != '\0') {
        
        // Armazena os bits do primeiro caracter
        bitmap* b = bitmapInit(8);

        // Itera sobre os bits do caracter
        for (int i = 7; i >= 0; i--) {
            int bit = (c>>i) & 0x01;
            bitmapAppendLeastSignificantBit(b, bit);
        }

        // Coloca esse bitmap na mensagem
        if (message == NULL) message = b;    
        else {
            // Cria um novo bitmap
            bitmap* new = bitmapInit(bitmapGetLength(message) + bitmapGetLength(b));

            // Copia o conteudo do message para a nova mensagem
            for (int i = 0; i < bitmapGetLength(message); i++) 
                bitmapAppendLeastSignificantBit(new, bitmapGetBit(message, i));

            // Copia o conteudo do b para a nova mensagem
            for (int i = 0; i < bitmapGetLength(b); i++) 
                bitmapAppendLeastSignificantBit(new, bitmapGetBit(b, i));

            bitmapLibera(message);
            bitmapLibera(b);
            message = new;
        }
    } 

    // Logica para encontrar o caracter na arvore
    int* index = (int*) malloc(sizeof(int));
    *index = 0;

    while (*index <= bitmapGetLength(message) - 1) {
        char c = searchCharTree(message, index, root);
        printf("%c", c);
    }
    printf("\n");
    

    free(index);
    bitmapLibera(message);
}

