/*
 *  IDENTIFICACAO
 *
 *	IAED, 2o semestre, 2013/2014
 *
 *	Grupo al047
 *
 *	Rodrigo Bernardo, 78942
 *	Miguel Ribeiro, 79085
 *	George Uzonj, 79338
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "item.h"

#define STRMAXLEN 500
#define COMMAND_MAX_LEN 20
#define eq(A,B) (!strcmp(A,B))

int main()
{
  char command[COMMAND_MAX_LEN+1];
  int i, n;
  Qptr* users = NULL;

  /*
   * Obtem numero de utilizadores e inicializa vector de utilizadores (vector
   * de filas).
   */
  scanf("%d", &n);
  users = (Qptr*) malloc(sizeof(Qptr) * n);
  for(i = 0; i < n; i++)
    users[i] = queueInit();

  scanf("%s", command);

  while (!eq(command, "quit"))
    {
      if (eq(command, "send"))
        {
          char* text = (char*) malloc(sizeof(char) * (STRMAXLEN + 1));
          int sender, receiver, length;
          Item new_message = NULL;

          /* Guarda o emissor e o receptor da mensagem. */
          scanf("%d%d", &sender, &receiver);

          /* Capta o caracter '\n' introduzido pelo utilizador. */
          getchar();

          /* Le do stdin o texto a ser enviado. */
          fgets(text, STRMAXLEN + 1, stdin);

          /*
           * Se o comprimento da string for menor que o maximo (definido em
           * STRMAXLEN), realoca memoria para ocupar menos espaco.
           */
          if ((length = strlen(text)) < STRMAXLEN + 1)
            text = (char*) realloc(text, sizeof(char) * (length + 1));

          /* Inicializa a mensagem. */
          new_message = itemInit(sender, receiver, text);

          /* Coloca a nova mensagem na fila do receptor. */
          queuePut(users[receiver], new_message);
        }
      else if (eq(command, "process"))
        {
          int u;

          /*
           * Obtem o indice do utilizador. Depois, se o utilizador tiver
           * mensagens por ler, imprime a proxima mensagem que lhe e
           * destinada, se nao, imprime NULL.
           */
          scanf("%d", &u);
          if(!queueEmpty(users[u]))
            {
              Item item = queueGet(users[u]);
              printItem(item);
              freeItem(item);
            }
          else puts("NULL");
        }
      else if (eq(command, "list"))
        {
          int u;

          /*
           * Obtem o indice do utilizador. Depois, se o utilizador tiver
           * mensagens por ler, imprime-as, se nao, imprime NULL.
           */
          scanf("%d", &u);
          if(!queueEmpty(users[u]))
            printQueue(users[u]);
          else puts("NULL");
        }
      else if (eq(command, "listsorted"))
        {
          int u;

          /*
           * Obtem o indice do utilizador. Depois, se o utilizador tiver
           * mensagens por ler, imprime-as por ordem alfabetica (caso hajam
           * duas mensagens iguais, a ordenacao segue o indice do emissor das
           * mensagens por ordem crescente), se nao, imprime NULL.
           */
          scanf("%d", &u);
          if(!queueEmpty(users[u]))
            {
              int i, size = users[u]->size;

              /*
               * Transforma fila do utilizador num vector, para poder ser
               * ordenado usando qsort.
               */
              Item* messages = queueToVector(users[u]);

              qsort(messages, size, sizeof(Item), cmpItem);

              for(i = 0; i < size; i++)
                printItem(messages[i]);

              free(messages);
            }
          else puts("NULL");

        }
      else if (eq(command, "kill"))
        {
          int u;

          /*
           * Obtem o indice do utilizador e apaga todas as mensagens em
           * espera.
           */
          scanf("%d", &u);
          deleteQueue(users[u]);
        }
      else printf("ERRO: comando desconhecido\n");

      scanf("%s", command);
    }

  /* Apaga todas as mensagens em espera e elimina as filas. */
  for(i = 0; i < n; i++)
    {
      deleteQueue(users[i]);
      free(users[i]);
    }

  free(users);

  return EXIT_SUCCESS;
}
