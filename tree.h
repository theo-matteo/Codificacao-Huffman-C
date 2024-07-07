#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include "bitmap.h"

typedef struct tree tTree;

/// @brief Cria uma nova arvore 
/// @return Estrutura da arvore alocada
tTree* createTree();

/// @brief Define qual caractere a estrutura vai armazenar
/// @param arvore 
/// @param caractere
void setChar(tTree* tree, char c);

/// @brief Define qual a frequencia do caractere
/// @param arvore
/// @param inteiro representando a frequencia
void setPeso(tTree* tree, unsigned int f);

/// @brief Obtem a frequencia de um caracter 
/// @param tree 
/// @return frequencia de um caracter
unsigned int getPeso (tTree* tree);


/// @brief Compara duas arvores de acordo com a frequencia de caracteres
/// @param t1 
/// @param t2 
/// @return 1 - se t1 for maior que t2, 0 - caso contrarios
int compareTrees(const void*t1, const void* t2);


/// @brief Obtem o tamanho da arvore 
/// @param tree 
/// @return 
unsigned int getSizeTree(tTree* tree);


/// @brief 
/// @param tree 
void unsetLeafTree(tTree* tree);

/// @brief 
/// @param root 
/// @param node 
void setRightNode(tTree* root, tTree* node);

/// @brief 
/// @param root 
/// @param node 
void setLeftNode(tTree* root, tTree* node);

/// @brief 
/// @param tree 
/// @param file 
void writeTreeBinaryFile(tTree* tree, FILE* file);


/// @brief 
/// @param t 
void printTree(void* t);

void searchTree (tTree* tree, char target, bitmap* b, int* flag);

tTree* createTreeFromBinary (FILE* binaryFile);


/// @brief Libera a memoria da arvore
/// @param arvore
void freeTree(void* tree);

#endif