#ifndef _UTILS_H
#define _UTILS_H

#define VECTOR_SIZE 128
#include "tree.h"

/// @brief Obtem quantos caracteres diferentes existem no vetor
/// @param vector 
/// @return numero de caracteres
unsigned int getNumCharacters(int* vector);


/// @brief Carrega o vetor de arvores com os caracteres e seus pesos
/// @param nodes 
/// @param vector 
void loadVectorTree (tTree* nodes [], int* vector);


/// @brief Executa o algoritmo de Huffman
/// @param nodes 
/// @param vector 
void executeAlgorithm(tTree* nodes [], unsigned int size);


void encodeMessage (FILE* file, FILE* binaryFile, tTree* root);

void decodeMessage (FILE* binaryfile, tTree* root);


#endif