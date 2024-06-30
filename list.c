#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  void* data;
  freeData free_data;
  struct node* next;
} node;

struct list {
  node* start;
  node* end;
  unsigned int size;
};

static node* createNode (void* data, freeData free_data) {

  node* n = (node*) malloc(sizeof(node));
  n->data = data;
  n->free_data = free_data;
  n->next = NULL;

  return n;
}

static void freeNode(node* n) {
  if (!n) return;
  if (n->free_data) 
    n->free_data(n->data);
  free(n);
}

tList* createList() {

  tList* list = (tList*) malloc(sizeof(tList));
  if (list == NULL) {
    exit(EXIT_FAILURE);
  }

  list->start = list->end = NULL;
  list->size = 0;
  return list;  
} 

void insertData(tList* list, void* data, freeData free_data) {

  // Cria um novo node
  node* n = createNode(data, free_data);

  // Insere no inicio da lista
  n->next = list->start;
  list->start = n;

  if (list->end == NULL)
    list->end = n;

  list->size++;
}

void sortList(tList* list, compareData compare_data) {

  if (list == NULL || list-> size <= 1) return;

  // Inicializa inicialmente com true
  bool swapped = true;

  node* p1 = NULL; // Esse noh sempre comeca no start da lista
  node* p2 = NULL; // Esse noh eh atualizado para o proximo 

  while (swapped == true) {

    swapped = false;  
    p1 = list->start;

    while (p1 != p2 && p1->next != NULL) {

      // Verifica o o dado de p1 eh maior que o p2
      if (compare_data(p1->data, p1->next->data)) {
        swapped = true;
        void* tmp = p1->data;
        p1->data = p1->next->data;
        p1->next->data = tmp;
      }
      p1 = p1->next;
    }
    p2 = p1;
  } 
}

void* getDatabyIndex(tList* list, unsigned int index) {

  if (index < 0) return NULL;
  int count = 0;

  for (node* ptr = list->start; ptr != NULL; ptr = ptr->next) {
    if (count == index) return ptr->data;
    count++;
  }
}

void removeItem(tList* l, int index) {

    if (l->size == 0) {
        printf("Lista vazia!\n");
        return;
    }

    int i = 0;
    node* prev = NULL;

    for (node* cursor = l->start; cursor != NULL; cursor = cursor->next) {

        // Caso encontre o item
        if (index == i) {

            // Verifica se eh o unico item
            if (l->start == cursor && l->end == cursor) {
                free(cursor); // Desaloca o noh
                l->start = l->end = NULL;
                l->size--;
                return;
            }
            
            // Verifica se eh o primeiro item
            if (l->start == cursor) {
                l->start = cursor->next;
                free(cursor);
                l->size--;
                return;
            }

            // Verifica se eh o ultimo item
            if (l->end == cursor) {
                l->end = prev;
                prev->next = NULL;
                free(cursor);
                l->size--;
                return;
            }   

            // Casos gerais
            prev->next = cursor->next;
            free(cursor);
            l->size--;
            return;
        }

        prev = cursor;
        i++;
    }
    
}

void printList(tList* list, printData print_data) {

  if (list == NULL || print_data == NULL) return;

  for (node* ptr = list->start; ptr != NULL; ptr = ptr->next) 
    print_data(ptr->data);

}

unsigned int getSizeList(tList* list) {
  return list->size;
}

void freeList(tList* list) {

  if (list == NULL) return;
  
  node* cursor = list->start;
  while (cursor) {
    node* temp = cursor->next;
    freeNode(cursor);
    cursor = temp;
  }

  free(list);
}