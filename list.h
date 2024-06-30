#ifndef _LIST_H
#define _LIST_H

// Callback para desalocar dado inserido 
typedef void (*freeData)(void*);
typedef void (*printData)(void*);
typedef int (*compareData) (void*, void*);

typedef struct list tList;

/// @brief 
/// @return 
tList* createList();

/// @brief Insere dado no inicio
/// @param list 
/// @param data 
/// @param  free_data - Funcao callback
void insertData(tList* list, void* data, freeData free_data);


/// @brief Orderna a lista de forma crescente
/// @param list 
/// @param compare_data 
void sortList(tList* list, compareData compare_data);

void printList(tList* list, printData print_data);

void* getDatabyIndex(tList* list, unsigned int index);

void removeItem(tList* l, int index);

unsigned int getSizeList(tList* list);

/// @brief Libera memoria da lista 
/// @param list 
void freeList(tList* list);

#endif