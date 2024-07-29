#include "decoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define a quantidade de bits de uma mega
#define Mb 1000000

// Define um buffer de 12KB (1024 * 12)
#define BUFFER_SIZE 12288


/// @brief Obtem a extensao do arquivo que sera gerado como saida
/// @param filename nome do arquivo fornecido para o programa
/// @return retorna a extensao (exemplos: .img, .txt)
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

void decodeMessage (FILE* binaryfile, tTree* tree, const char* filenameBinaryFile) {

    // Obtem a quantidade de bits que ha na sequencia
    int sizeMessage = 0;
    fread(&sizeMessage, sizeof(int), 1, binaryfile); 

    // bitmap que ira armazenar a messagem decodificada
    bitmap* message = bitmapInit(Mb);

    // Le cada caracter armazenado no arquivo binarios
    unsigned char c, buffer[BUFFER_SIZE];
    unsigned int bytes = 0;

    // Enquanto a leitura for bem sucedida e nao chegou no pseudocaracter
    while ((bytes = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, binaryfile)) > 0) {
        // Itera sobre os bits do caracter e armazena o codigo binario
        for (unsigned int i = 0; i < bytes; i++) {
            unsigned int c = buffer[i];
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

    // Realiza busca na arvore binaria
    while (true) {
        c = findCharBitmapTree(message, index, sizeMessage, tree);
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

