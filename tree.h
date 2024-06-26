#ifndef _TREE_H
#define _TREE_H

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
void setFrequency(tTree* tree, unsigned int f);

/// @brief Libera a memoria da arvore
/// @param arvore
void freeTree(tTree* tree);

#endif