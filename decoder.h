#ifndef _DECODER_H
#define _DECODER_H

#include "tree.h"

/// @brief Decodifica a mensagem dado um arquivo binario e a arvore de codificacao
/// @param binaryfile arquivo binario que contem a sequencia de bits a ser decodificada
/// @param tree arvore binaria de codificacao
/// @param filenameBinaryFile nome do arquivo binario
void decodeMessage (FILE* binaryfile, tTree* tree, const char* filenameBinaryFile);


#endif