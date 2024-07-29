#include "encoder.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Define a quantidade de bits de uma mega
#define Mb 1000000

// Define um buffer de 12KB (1024 * 12)
#define BUFFER_SIZE 12288

struct byteTracker_ {
  
  // Frequencia de cada caracter (1 byte) no arquivo
  unsigned int frequency;

  // Bitmap do caminho binario do byte na arvore binaria
  bitmap* b;
};

/// @brief Obtem o numero de itens (nao nulos) dentro do vetor de arvores
/// @param nodes vetor de arvores
/// @param size_nodes tamanho do vetor
/// @return numero de itens (nao nulos)
static int getNumItensVector(tTree* nodes [], unsigned int size_nodes) {
  int counter = 0;
  for (unsigned int i = 0; i < size_nodes; i++) 
      if (nodes[i] != NULL) counter++;
  return counter;
}

unsigned int getNumBytes(tByteTracker* byteTrackerVector[]) {
  int counter = 0;
  for (int i = 0; i < VECTOR_SIZE; i++)
    if (byteTrackerVector[i]->frequency != 0) counter++;
  return counter;
}

tByteTracker** createbyteTracker() {

  tByteTracker** byteTracker = (tByteTracker**) calloc(VECTOR_SIZE, sizeof(tByteTracker*));
  if (byteTracker == NULL) {
    printf("Falha ao alocar o byteTracker\n");
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
    byteTracker[i] = (tByteTracker*) malloc(sizeof(tByteTracker));
    byteTracker[i]->frequency = 0;
    byteTracker[i]->b = NULL;
  }

  return byteTracker;
}

void freebyteTracker (tByteTracker** byteTracker) {

  if (byteTracker == NULL) return;

  for (unsigned int i = 0; i < VECTOR_SIZE; i++) {
    if (byteTracker[i]->b) bitmapLibera(byteTracker[i]->b);
    free(byteTracker[i]);
  }

  free(byteTracker);
}


void vectorFrequencyInit (FILE* file, tByteTracker** byteTrackerVector) {

  unsigned char buffer[BUFFER_SIZE];
  unsigned int bytes = 0;

  while ((bytes = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, file)) > 0) {
    for (unsigned int i = 0; i < bytes; i++) {
      unsigned int c = buffer[i];
      byteTrackerVector[c]->frequency++;
    }
  }
}

void initBinaryPathChars (tByteTracker** byteTrackerVector, tTree* tree) {

  // Flag para indicar se o caractere foi encontrado
  int* flag = (int*) calloc(1, sizeof(int));
  int size_tree = getSizeTree(tree);

  for (unsigned int i = 0; i < VECTOR_SIZE; i++) {

    // Se esse codigo ASCII nao possui no arquivo, continua
    if (byteTrackerVector[i]->frequency == 0) continue;
    
    // Atualiza estado da flag 
    *flag = 0;

    // Cria um bitmap para armazenar o codigo binario do caractere
    bitmap* b = bitmapInit(size_tree - 1);

    // Obtem o codigo binario do caracter realizando a busca na arvore (o qual vem invertido)
    createPathCharInTree(tree, i, b, flag);

    // Atribui o bitmap a estrutura
    byteTrackerVector[i]->b = b;
  }

  free(flag);
}

void loadVectorTree (tTree* nodes [], tByteTracker* byteTrackerVector[]) {

  int index = 0;
  for (int i = 0; i < VECTOR_SIZE; i++) {
    // Se o caractere com codigo ascii 'i' estava presente no arquivo de texto
    if (byteTrackerVector[i]->frequency != 0) {
      // Cria uma nova arvore para esse caractere
      tTree* tree = createTree();
      setChar(tree, i);
      setPeso(tree, byteTrackerVector[i]->frequency);

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

void encodeMessage (FILE* file, FILE* binaryFile, tByteTracker* byteTrackerVector[]) {

  // Criar um bitmap com 1Mb de tamanho
  bitmap* message = bitmapInit(Mb);

  // Cria um buffer para pegar os dados do arquivo
  unsigned char buffer[BUFFER_SIZE];
  unsigned int bytes = 0;

  while ((bytes = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, file)) > 0)  {

    for (int i = 0; i < bytes; i++) {

      unsigned char c = buffer[i];
      bitmap* b = byteTrackerVector[c]->b;

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
    }
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
}