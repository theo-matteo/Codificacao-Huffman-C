#ifndef _UTILS_H
#define _UTILS_H
#define VECTOR_SIZE 128

#include "tree.h"

/// @brief Obtem quantos caracteres diferentes existem no vetor
/// @param vector 
/// @return numero de caracteres
unsigned int getNumCharacters(int* vector);


/// @brief Carrega o vetor de arvores com os caracteres e seus pesos
/// @param nodes vetor das arvores
/// @param vector que contem a frequencia de cada caracter
void loadVectorTree (tTree* nodes [], int* vector);


/// @brief Executa o algoritmo de huffman
/// @param nodes vetor de nos das arvores 
/// @param size tamanho desse vetor
void executeAlgorithm(tTree* nodes [], unsigned int size);

/// @brief Codifica a mensagem (sequencia bits) no arquivo binario (compactacao)
/// @param file arquivo contendo o texto a ser codificado
/// @param binaryFile arquivo binario a ser escrito
/// @param tree arvore de codificacao
void encodeMessage (FILE* file, FILE* binaryFile, tTree* tree);


/// @brief Decodifica mensagem de um arquivo binario
/// @param binaryfile arquivo binario a ser lido
/// @param tree arvore de codificacao 
void decodeMessage (FILE* binaryfile, tTree* tree);


#endif