#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "list.h"
#define VECTOR_SIZE 128



int main(int argc, char const *argv[]) {
  
  // Verifica se o arquivo foi fornecido na linha de comando
  if (argc <= 1) {
    printf("Nao foi fornecido arquivo de entrada");
    exit(EXIT_FAILURE);
  }
  
  // Abre o arquivo no diretorio fornecido
  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Falha ao abrir arquivo no caminho %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // Inicializa todas as posicoes do array com 0
  int vector[VECTOR_SIZE] = {0};

  // Le cada caractere do arquivo e armazena frequencia no vetor
  int c;
  while ( (c = getc(file)) != EOF) 
    vector[c]++;

  // Fecha o arquivo de entrada
  fclose(file);

  // Cria uma lista de nodes de arvore
  tList* list = createList();
  for (int i = 0; i < VECTOR_SIZE; i++) {
    if (vector[i] != 0) {
      tTree* tree = createTree();
      setChar(tree, i);
      setPeso(tree, vector[i]);
      insertData(list, tree, freeTree);
    }
  }

  // Ordena a lista
  sortList(list, compareTrees);

  // Executa o algoritmo
  while (getSizeList(list) > 1) {

    tTree* new = createTree();
    tTree* t1 = getDatabyIndex(list, 0);
    tTree* t2 = getDatabyIndex(list, 1);
    
    // Remove os dois primeiros itens da lista
    removeItem(list, 0);
    removeItem(list, 0);

    // Configura atributos
    setLeftNode(new, t1);
    setRightNode(new, t2);
    setPeso(new, getPeso(t1) + getPeso(t2));
    unsetLeafTree(new);
     
    // Insere na lista e ordena novamente
    insertData(list, new, freeTree);
    sortList(list, compareTrees);
  }
 
  
  freeList(list);
  return EXIT_SUCCESS;
}

