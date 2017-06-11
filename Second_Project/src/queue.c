#include <stdlib.h>
#include "queue.h"
#include "item.h"

Qptr queueInit() { /* Inicializa e devolve uma fila vazia (q). */
  Qptr q = (Qptr) malloc(sizeof(queue));

  q->head = NULL;
  q->tail = NULL;
  q->size = 0;

  return q;
}

int queueEmpty(Qptr q) { /* Teste para verificar se a fila (q) esta vazia. */
  return q->head == NULL;
}

void queuePut(Qptr q, Item item) {/* Coloca o item (item) no fim da fila (q). */
  if (q->head == NULL)
    {
      q->tail = newItem(NULL, item);
      q->head = q->tail;
    }
  else
    {
      q->tail->next = newItem(q->tail->next, item);
      q->tail = q->tail->next;
    }
  (q->size)++;
}

Item queueGet(Qptr q) {/*Retira o item (item) a cabeca da fila (q) e retorna-o*/
  Item item = q->head->item;
  link new_head = q->head->next;

  free(q->head);
  q->head = new_head;

  (q->size)--;

  return item;
}

void printQueue(Qptr q) { /* Imprime no stdout todos os items da fila (q). */
  link x = q->head;

  while(x != NULL)
    {
      printItem(x->item);
      x = x->next;
    }
}

void deleteQueue(Qptr q) { /* Elimina todos os items da fila (q). */
  while(!queueEmpty(q))
    {
      Item item = queueGet(q);
      freeItem(item);
    }
}

Item* queueToVector(Qptr q) {
  /* Devolve um vector com todos os items da fila (q), pela mesma ordem. */
  int i;
  link x = q->head;
  Item* v = (Item*) malloc(sizeof(Item) * q->size);

  for(i=0; i < q->size; i++, x = x->next)
    v[i] = x->item;

  return v;
}
