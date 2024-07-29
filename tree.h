#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include "bitmap.h"

typedef struct tree tTree;

/// @brief Cria uma nova arvore 
/// @return Estrutura da arvore alocada
tTree* createTree();

/// @brief Cria uma arvore completa a partir de um arquivo binario
/// @param binaryFile 
/// @return arvore alocada e inicializada
tTree* createTreeFromBinary (FILE* binaryFile);

/// @brief Escreve uma arvore binaria em um arquivo binario
/// @param tree arvore de codificacao
/// @param binaryFile arquivo binario
void writeTreeBinaryFile(tTree* tree, FILE* binaryFile);


/// @brief Cria o caminho binario do bitmap realizando busca de caracter na arvore binaria
/// @param tree arvore binaria
/// @param target caractere a ser buscado
/// @param b bitmap que ira mapear o caminho ateh o caracter
/// @param flag para indicar fim da busca
void createPathCharInTree (tTree* tree, unsigned char target, bitmap* b, int* flag);


/// @brief Encontra caractere em uma arvore binaria dado um bitmap contendo a sequencia de bits 
/// @param b bitmap da mensagem
/// @param index index atual do bitmap 
/// @param limitBits limit de bits a serem lidos
/// @param tree arvore binaria de codificacao
/// @return caracter/byte encontrado
unsigned char findCharBitmapTree (bitmap* b, unsigned int* index, unsigned int limitBits, tTree* tree);

/// @brief Compara duas arvores de acordo com a frequencia de caracteres
/// @param t1 primeira arvore
/// @param t2 segunda arvore
/// @return 1 se t1 for maior, 0 se for igual, -1 se for menor
int compareTrees(const void*t1, const void* t2);

/// @brief Obtem o tamanho da arvore 
/// @param tree 
/// @return tamanho da arvore
unsigned int getSizeTree(tTree* tree);

/// @brief Define qual caractere a estrutura vai armazenar
/// @param arvore 
/// @param caractere
void setChar(tTree* tree, unsigned char c);

/// @brief Define qual a frequencia do caractere
/// @param arvore
/// @param inteiro representando a frequencia
void setPeso(tTree* tree, unsigned int f);

/// @brief Obtem a frequencia de um caracter 
/// @param tree 
/// @return frequencia de um caracter
unsigned int getPeso (tTree* tree);

/// @brief Atualiza flag da arvore, indicando que ela nao eh mais uma folha
/// @param tree 
void unsetLeafTree(tTree* tree);

/// @brief Adiciona uma arvore a direita da outra
/// @param root arvore pelo qual vai ser adicionado um novo no
/// @param node no a ser adicionado
void setRightNode(tTree* root, tTree* node);

/// @brief Adiciona uma arvore a esquerda da outra
/// @param root arvore pelo qual vai ser adicionado um novo no
/// @param node no a ser adicionado
void setLeftNode(tTree* root, tTree* node);

/// @brief Imprime a arvore 
/// @param t void pointer da arvore
void printTree(void* t);

/// @brief Libera a memoria da arvore
/// @param tree arvore 
void freeTree(void* tree);

#endif