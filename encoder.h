#ifndef _ENCODER_H
#define _ENCODER_H

#include "bitmap.h"
#include "tree.h"

// Define o tamanho do vetor
#define VECTOR_SIZE 256

// Estrutura ira armazenar a frequencia de cada caracter
typedef struct charTracker_ tCharTracker;


tCharTracker* createCharTracker();

void freeCharTracker (tCharTracker* charTracker);

void vectorFrequencyInit (FILE* file, tCharTracker* charTrackerVector[]);

void initBinaryPathChars (tCharTracker* charTrackerVector[], tTree* tree);

void loadVectorTree (tTree* nodes [], tCharTracker* charTrackerVector[]);

void executeAlgorithm(tTree* nodes [], unsigned int size);

void encodeMessage (FILE* file, FILE* binaryFile, tCharTracker* charTrackerVector[]);

unsigned int getNumCharacters(tCharTracker* charTrackerVector[]);





#endif