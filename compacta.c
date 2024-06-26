#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


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
  int vector[128] = {0};

  // Le cada caractere do arquivo e armazena frequencia no vetor
  int c;
  while ( (c = getc(file)) != EOF) 
    vector[c]++;
  
  


  fclose(file);
  return EXIT_SUCCESS;
}
