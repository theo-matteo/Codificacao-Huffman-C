#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tree {

  char* character; // Caractere armazenado
  unsigned int frequency; // Frequencia que um caractere aparece
  unsigned int isLeafNode; // 0 - No nao folha 1 - No folha

  struct tree* right;
  struct tree* left;
};

tTree* CreateTree() {

  tTree* tree = (tTree*) malloc(sizeof(tree));
  if (tree == NULL) {
    printf("Falha na alocacao da arvore\n");
    exit(EXIT_FAILURE);
  }

  tree->character = tree->left = tree->right = NULL;
  tree->frequency = 0;

  // Uma nova arvore nao possui filhos, logo eh um no folha
  tree->isLeafNode = 1; // 
}

void insertChar(tTree* t, char c) {
  t->character = strdup(c);
}

void freeTree(tTree* t) {

  if (t == NULL) return;

  freeTree(t->right);
  freeTree(t->left);

  free(t->character);
  free(t);
}