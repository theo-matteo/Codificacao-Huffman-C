#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

struct tree {

  char character; // Caractere armazenado
  unsigned int peso; // Frequencia que um caractere aparece
  unsigned int isLeafNode; // 0 - No nao folha 1 - No folha

  struct tree* right;
  struct tree* left;
};

tTree* createTree() {

  tTree* tree = (tTree*) malloc(sizeof(tTree));
  if (tree == NULL) {
    printf("Falha na alocacao da arvore\n");
    exit(EXIT_FAILURE);
  }

  tree->left = tree->right = NULL;
  tree->character = '\0';
  tree->peso = 0;

  // Uma nova arvore nao possui filhos, logo eh um no folha
  tree->isLeafNode = 1; // 

  return tree;
}

void setChar(tTree* t, char c) {
  t->character = c;
}

void setPeso(tTree* tree, unsigned int f) {
  tree->peso = f;
}

void setRightNode(tTree* root, tTree* node) {
  root->right = node;
}

void setLeftNode(tTree* root, tTree* node) {
  root->left = node;
}

void unsetLeafTree(tTree* tree) {
  tree->isLeafNode = 0;
}

unsigned int getPeso (tTree* tree) {
  return tree->peso;
}

int compareTrees(void* t1, void* t2) {

  tTree* tree1 = (tTree*) t1;
  tTree* tree2 = (tTree*) t2;

  return getPeso(tree1) > getPeso(tree2);
}

void printTree(void* t) {

  if (t == NULL) return;

  tTree* tree = (tTree*) t;
  printf("%d ", tree->peso);
  return;

  printTree(tree->right);
  printTree(tree->left);

}

void freeTree(void* tree) {

  tTree* t = (tTree*) tree;
  if (t == NULL) return;

  freeTree(t->right);
  freeTree(t->left);
  free(t);
}