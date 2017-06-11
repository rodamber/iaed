#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

link newItem(link next, Item item) {
  /*
   * Cria e devolve um novo link (new) cujos membros do node para o qual aponta
   * sao item e next.
   */
  link new = (link) malloc(sizeof(node));

  new->item = item;
  new->next = next;

  return new;
}

Item itemInit(int sender, int receiver, char* text) {
  /*
   * Inicializa e devolve um novo item cujos membros sao sender, receiver e text,
   * passados como argumentos.
   */
  Item item = (Item) malloc(sizeof(message));

  item->sender = sender;
  item->receiver = receiver;
  item->text = text;

  return item;
}

void printItem(Item item) { /* Imprime item. */
  printf("%d %d %s", item->receiver, item->sender, item->text);
}

void freeItem(Item item) {
  /*Liberta os membros que e necessario libertar de item e depois liberta item.*/
  free(item->text);
  free(item);
}

int cmpItem(const void* item1, const void* item2) {
  /*
   * Compara dois items (item1 e item2). A funcao recebe dois void* (em vez de
   * dois Item) para poder ser passada como argumento a qsort.
   */
  Item* i1 = (Item*) item1;
  Item* i2 = (Item*) item2;
  int equal = strcmp((*i1)->text, (*i2)->text);

  if (equal != 0)
    return equal;
  else return (*i1)->sender - (*i2)->sender;
}
