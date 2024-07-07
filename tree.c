#include "tree.h"
#include <stdlib.h>


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

tTree* createTreeFromBinary (FILE* binaryFile) {

    char flag;
    fread(&flag, sizeof(char), 1, binaryFile);

    tTree* tree = createTree();

    // Se for uma folha, le o caracter e a frequencia
    if (flag == 'F') {
        tree->isLeafNode = 1;
        fread(&tree->character, sizeof(char), 1, binaryFile);
        fread(&tree->peso, sizeof(int), 1, binaryFile);
    } else {
        tree->isLeafNode = 0;
        fread(&tree->peso, sizeof(int), 1, binaryFile);
        tree->left = createTreeFromBinary(binaryFile);
        tree->right = createTreeFromBinary(binaryFile);
    }
  
    return tree;
}

void writeTreeBinaryFile(tTree* tree, FILE* binaryFile) {

    if (tree == NULL) return;

    // Flag que indica se uma arvore eh folha ou nao
    char c = tree->isLeafNode ? 'F' : 'N';
    fwrite(&c, sizeof(char), 1, binaryFile);

    // Verifica se a arvore eh uma folha e escreve seu caracter
    if (tree->isLeafNode) {
        fwrite(&tree->character, sizeof(char), 1, binaryFile);
        fwrite(&tree->peso, sizeof(int), 1, binaryFile);
    } else {
        fwrite(&tree->peso, sizeof(int), 1, binaryFile);
        writeTreeBinaryFile(tree->left, binaryFile);
        writeTreeBinaryFile(tree->right, binaryFile);
    }
}

void searchTree (tTree* tree, char target, bitmap* b, int* flag) {

  if (tree == NULL) return;

  // Caso tenha encontrado o caracter atualiza estado da flag
  if (tree->character == target) {
    *flag = 1;
    return;
  }

  searchTree(tree->right, target, b, flag);
  if (*flag == 1) {
    bitmapAppendLeastSignificantBit(b, 1);
    return;
  }

  searchTree(tree->left, target, b, flag);
  if (*flag == 1) {
    bitmapAppendLeastSignificantBit(b, 0);
    return;
  }
}

char searchCharTree (bitmap* b, int* index, tTree* tree) {

  // Caso nao encontre o caracter ou ultrapassou o tamanho do bitmap
  if (tree == NULL || *index >= bitmapGetLength(b)) return '\0';

  // Caso encontre a folha de arvore retorna seu caracter
  if (tree->isLeafNode) return tree->character;

  if (bitmapGetBit(b, *index) == 1) {
    (*index)++;
    return searchCharTree(b, index, tree->right);
  } 
  else {
    (*index)++;
    return searchCharTree(b, index, tree->left);
  }
}

int compareTrees(const void* t1, const void* t2) {

    tTree* tree1 = *((tTree**) t1);
    tTree* tree2 = *((tTree**) t2);

    if (tree1 == NULL) return 1;
    else if (tree2 == NULL) return -1;
    else if (tree1 == NULL && tree2 == NULL) return 0;

    return getPeso(tree1) - getPeso(tree2);
}

unsigned int getSizeTree(tTree* tree) {

  if (tree == NULL) return 0;

  int right = getSizeTree(tree->right) + 1;
  int left = getSizeTree(tree->left) + 1;

  return (right > left ? right : left);
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

void printTree(void* t) {

  if (t == NULL) return;

  tTree* tree = (tTree*) t;

  if (tree->isLeafNode)
    printf("Peso: %d Caracter: %c\n", tree->peso, tree->character);
  
  printTree(tree->left);
  printTree(tree->right);
}

void freeTree(void* tree) {

  if (tree == NULL) return;
  tTree* t = (tTree*) tree;

  freeTree(t->right);
  freeTree(t->left);
  free(t);
}