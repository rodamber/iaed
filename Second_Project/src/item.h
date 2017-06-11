/*
 * item.h -- definicoes e declaracoes globais de item.c
 */

#ifndef item_h
#define item_h

typedef struct {
  int sender;
  int receiver;
  char* text;
} message;

typedef message* Item;

typedef struct node {
  Item item;
  struct node* next;
} node;

typedef node* link;

link newItem(link next, Item item);
Item itemInit(int sender, int receiver, char* text);
void freeItem(Item item);
void printItem(Item item);
int cmpItem(const void* i1, const void* i2);

#endif
