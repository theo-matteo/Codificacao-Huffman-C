#ifndef _ENCODER_H
#define _ENCODER_H

#include "bitmap.h"
#include "tree.h"

// Define o tamanho do vetor
#define VECTOR_SIZE 256

// Estrutura ira armazenar a frequencia de cada caracter/byte e seu respectivo bitmap
typedef struct byteTracker_ tByteTracker;


/// @brief Cria um vetor de tamanho VECTOR_SIZE do tipo byteTracker
/// @return vetor byteTracker
tByteTracker** createbyteTracker();


/// @brief Libera memoria do byteTracker
/// @param byteTracker 
void freebyteTracker (tByteTracker** byteTracker);


/// @brief Faz a contablizacao de cada byte/caracter presente no arquivo
/// @param file arquivo fornecido na entrada
/// @param byteTrackerVector vetor byteTracker
void vectorFrequencyInit (FILE* file, tByteTracker** byteTrackerVector);


/// @brief Cria um bitmap para cada caracter/byte presente no arquivo
/// @param byteTrackerVector vetor byteTracker
/// @param tree arvore binaria de codificacao
void initBinaryPathChars (tByteTracker** byteTrackerVector, tTree* tree);


/// @brief Inicializa o vetor de no de arvores (criando um no para cada byte/caracter)
/// @param nodes vetor de arvores necessario para algoritmo de huffmann
/// @param byteTrackerVector vetor byteTracker
void loadVectorTree (tTree* nodes [], tByteTracker** byteTrackerVector);


/// @brief Executa o algoritmo de Huffmann, ate chegar em um unico no de arvore (a root)
/// @param nodes vetor de arvores
/// @param size tamanho total do vetor
void executeAlgorithm(tTree* nodes [], unsigned int size);


/// @brief Codifica a mensagem no arquivo binario de saida
/// @param file arquivo fornecido de entrada
/// @param binaryFile arquivo binario de saida
/// @param byteTrackerVector vetor byteTracker
void encodeMessage (FILE* file, FILE* binaryFile, tByteTracker** byteTrackerVector);


/// @brief Obtem o numero de caracteres/bytes nao repetidos 
/// @param byteTrackerVector vetor byteTracker
/// @return numero de caracteres/bytes nao repetidos 
unsigned int getNumBytes(tByteTracker** byteTrackerVector);



#endif