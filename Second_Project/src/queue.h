/*
 * queue.h -- definicoes e declaracoes globais de queue.c
 */

#ifndef queue_h
#define queue_h

#include "item.h"

typedef struct {
  link head;
  link tail;
  int size;
} queue;

typedef queue* Qptr;

void deleteQueue(Qptr q);
int queueEmpty(Qptr q);
Item queueGet(Qptr q);
Qptr queueInit();
void printQueue(Qptr q);
void queuePut(Qptr q, Item item);
Item* queueToVector(Qptr q);

#endif
