#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define a quantidade de bits de uma mega
#define Mb 1000000


static int getNumItensVector(tTree* nodes [], unsigned int size_nodes) {
    int counter = 0;
    for (unsigned int i = 0; i < size_nodes; i++) 
        if (nodes[i] != NULL) counter++;
    return counter;
}

unsigned int getNumCharacters(int* vector) {
    int counter = 0;
    for (int i = 0; i < VECTOR_SIZE; i++)
        if (vector[i] != 0) counter++;
    return counter;
}

static char* getExtensionFile (const char* filename) {

    char* extension = calloc(16, sizeof(char));
    int j = 0;
    bool flag = false;

    for (int i = 0, n = strlen(filename); i < n; i++) {
        if (filename[i] == '.') flag = !flag;
        if (flag) extension[j++] = filename[i];
    }


    return extension;
}

void vectorFrequencyInit (FILE* file, int* vector) {

    // Le sequencia de 8 bits (caracter) do arquivo fornecido e armazena frequencia no vetor
    unsigned char c;
    while (fread(&c, sizeof(unsigned char), 1, file) == 1) 
        vector[c]++;
}

void loadVectorTree (tTree* nodes [], int* vector) {

    int index = 0;
    for (int i = 0; i < VECTOR_SIZE; i++) {

        // Se o caractere com codigo ascii 'i' estava presente no arquivo de texto
        if (vector[i] != 0) {

            // Cria uma nova arvore para esse caractere
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

    // Realiza operacoes ate ter apenas um node de arvore no vetor
    while (getNumItensVector(nodes, size) >= 2) {

        // Cria uma nova arvore tendo como filhos os dois primeiros nodes do vetor
        tTree* new = createTree();
        tTree* tree1 = nodes[0];
        tTree* tree2 = nodes[1];

        // 'Remove' os dois primeiros itens da lista
        nodes[0] = NULL;
        nodes[1] = NULL;

        // Adiciona os dois novos nos na nova arvore
        setLeftNode(new, tree1);
        setRightNode(new, tree2);

        // Configura atributos da nova arvore (peso + setar que nao eh folha mais)
        setPeso(new, getPeso(tree1) + getPeso(tree2));
        unsetLeafTree(new);

        // Adiciona a nova arvore na primeira posicao do array
        nodes[0] = new;

        // Realiza ordernacao do vetor de acordo com a peso de cada arvore
        qsort(nodes, size, sizeof(tTree*), compareTrees);
    }
}

void encodeMessage (FILE* file, FILE* binaryFile, tTree* tree) {

    // Flag para indicar se o caractere foi encontrado
    int* flag = (int*) calloc(1, sizeof(int));
    int size_tree = getSizeTree(tree); 

    // Criar um bitmap com 1Mb de tamanho
    bitmap* message = bitmapInit(Mb);

    unsigned char c;
    while (fread(&c, sizeof(unsigned char), 1, file) > 0)  {

        // Atualiza flag
        *flag = 0;

        // Cria um bitmap para armazenar o codigo binario do caractere
        bitmap* b = bitmapInit(size_tree - 1);

        // Obtem o codigo binario do caracter realizando a busca na arvore (o qual vem invertido)
        searchTree(tree, c, b, flag);

        // Imprime o codigo binario do caracter (propositos de depuracao)
        /* 
        printf("%c ", c);
        for (int i = bitmapGetLength(b) - 1; i >= 0; i--) {
            printf("%d", bitmapGetBit(b, i));
        }
        printf("\n");
       */


        // Como os bits vem invertidos, usamos o loop ao contrario
        for (int i = bitmapGetLength(b) - 1; i >= 0; i--) {

            // Verifica se nao execedeu a quantidade bits do message
            if (bitmapGetLength(message) == bitmapGetMaxSize(message)) {

                // Aloca outro bitmap com o dobro do tamanho
                bitmap* temp = bitmapInit(bitmapGetMaxSize(message) * 2);

                // Copia dados pra outro bitmap
                for (int i = 0; i < bitmapGetLength(message); i++)   
                    bitmapAppendLeastSignificantBit(temp, bitmapGetBit(message, i));
                
                // Desaloca message
                bitmapLibera(message);

                // Atualiza referencia
                message = temp;
            }

            bitmapAppendLeastSignificantBit(message, bitmapGetBit(b, i));
        }

        // Libera o bitmap auxiliar
        bitmapLibera(b);
    }

    // Salva a quantidade de bits presente na sequencia
    int sizeMessage = bitmapGetLength(message);
    fwrite(&sizeMessage, sizeof(int), 1, binaryFile);

    // Salva mensagem no arquivo binario 
    unsigned char* conteudo = bitmapGetContents(message);

    // Arredonda o numero de bits da mensagem
    int bits = bitmapGetLength(message);
    while (bits % 8 != 0) bits++;

    // Escreve o conteudo do bitmap no arquivo binario (byte a byte)
    for (int i = 0; i < bits / 8; i++)
        fwrite(&conteudo[i], sizeof(unsigned char), 1, binaryFile);

    bitmapLibera(message);
    free(flag);
}

void decodeMessage (FILE* binaryfile, tTree* tree, const char* filenameBinaryFile) {

    // Obtem a quantidade de bits que ha na sequencia
    int sizeMessage = 0;
    fread(&sizeMessage, sizeof(int), 1, binaryfile); 

    // bitmap que ira armazenar a messagem decodificada
    bitmap* message = bitmapInit(Mb);

    // Le cada caracter armazenado no arquivo binario
    unsigned char c;

    // Enquanto a leitura for bem sucedida e nao chegou no pseudocaracter
    while (fread(&c, sizeof(unsigned char), 1, binaryfile) > 0) {

        // Itera sobre os bits do caracter e armazena o codigo binario
        for (int i = 7; i >= 0; i--) {

            int bit = (c>>i) & 0x01;

            // Verifica se nao execedeu a quantidade bits do message
            if (bitmapGetLength(message) == bitmapGetMaxSize(message)) {

                // Aloca outro bitmap com o dobro do tamanho
                bitmap* temp = bitmapInit(bitmapGetMaxSize(message) * 2);

                // Copia dados pra outro bitmap
                for (int i = 0; i < bitmapGetLength(message); i++)  
                    bitmapAppendLeastSignificantBit(temp, bitmapGetBit(message, i));
                
                // Desaloca message
                bitmapLibera(message);

                // Atualiza referencia
                message = temp;
            }

            bitmapAppendLeastSignificantBit(message, bit);
        }
    }  


    // Concatena extensao do arquivo com o nome dele
    char* extension = getExtensionFile(filenameBinaryFile);
    char* filenameOutput = calloc(strlen("output") + strlen(extension) + 1, sizeof(char));
    strcpy(filenameOutput, "output");
    strcat(filenameOutput, extension);

    FILE* output = fopen(filenameOutput, "wb");
    if (output == NULL) {
        printf("Falha ao abrir arquivo\n");
        exit(EXIT_FAILURE);
    }

    // Index para percorrer no bitmap (como se fosse um ponteiro pra cada bit)
    unsigned int* index = (unsigned int*) malloc(sizeof(unsigned int));
    *index = 0;

    while (true) {
        c = searchCharTree(message, index, sizeMessage, tree);
        if (*index <= sizeMessage) 
            fwrite(&c, sizeof(unsigned char), 1, output);
        else
            break;
    }

    free(filenameOutput);
    free(extension);
    free(index);
    fclose(output);
    bitmapLibera(message);
}

