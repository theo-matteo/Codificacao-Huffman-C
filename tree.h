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
void setPeso(tTree* tree, unsigned int f);

/// @brief Obtem a frequencia de um caracter 
/// @param tree 
/// @return frequencia de um caracter
unsigned int getPeso (tTree* tree);


/// @brief Compara duas arvores de acordo com a frequencia de caracteres
/// @param t1 
/// @param t2 
/// @return 1 - se t1 for maior que t2, 0 - caso contrarios
int compareTrees(void* t1, void* t2);

void unsetLeafTree(tTree* tree);

void setRightNode(tTree* root, tTree* node);

void setLeftNode(tTree* root, tTree* node);

void printTree(void* t);

/// @brief Libera a memoria da arvore
/// @param arvore
void freeTree(void* tree);

#endif