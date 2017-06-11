/*	IDENTIFICACAO
 *
 *	IAED, 2o semestre, 2013/2014
 *
 *	Grupo al047
 *
 *	Miguel Ribeiro, 79085
 *	Rodrigo Bernardo, 78942
 *	George Uzonj, 79338
 *
 */

#include <stdio.h>
#include "projecto.h"

#define INPUT_FORMAT 3
#define INPUT_LENGTH 20

int main()
{
  char command;
  /* Variavel onde e guardado o comando introduzido pelo utilizador */

  char input[INPUT_LENGTH];
  /* Tabela que guarda o input introduzido pelo utilizador logo a seguir a
   * introducao do comando */

  char nomesPaises[NUM_PAISES+TE][3] = {"DE", "AT", "BE", "BG", "CY",
                                        "HR", "DK", "SK", "SI", "ES", "EE", "FI", "FR", "GR",
                                        "HU", "IE", "IT", "LV", "LT", "LU", "MT", "NL", "PL",
                                        "PT", "GB", "CZ", "RO", "SE","TE"};

  char nomesPartidos[NUM_PARTIDOS][4] = {"EPP", "PES", "LDE", "EGP", "ECR",
                                         "ELP", "ELD", "EDP","EAF", "EMN", "ECP", "AED"};

  double res_votos[NUM_PAISES][NUM_PARTIDOS] = {{0}};
  /* Tabela com onde sao colocados os votos de cada partido por pais */

  int i, partido, pais;

  int dados[INPUT_FORMAT];
  /* Tabela que guarda o input introduzido pelo utilizador, ja convertido para
   * inteiros */

  int mandatos[NUM_PAISES] = {96, 18, 21, 17, 6, 11, 13, 13, 8, 54, 6, 13,
                              74, 21, 21, 11, 73, 8, 11, 6, 6, 26, 51, 21, 73,
                              21, 32, 20};
  /* Tabela que faz a correspondencia entre os paises e o numero de mandatos a
   * atribuir por pais */

  int res_mandatos[NUM_PAISES+TE][NUM_PARTIDOS] = {{0}};
  /*Tabela onde sao colocados os mandatos atribuidos a cada partido por pais*/

  /* Notar que, nas tabelas, ao pais n corresponde a entrada n-1 */


  while ((command = getchar()) != 'x') { /* le o comando introduzido*/
    switch (command)
      {
      case '+':
        /* Execucao do comando +. Adiciona votos a um PPE de um determinado
         * Estado-membro */

        for (i = 0; i < INPUT_FORMAT; i++) {
          scanf("%s", input);
          dados[i] = atoi(input);
        }
        /* Converte os dados introduzidos no comando para inteiros e
         * guarda-os */

        res_votos[dados[0] - 1][dados[1] - 1] += dados[2];
        /* Coloca os votos introduzidos na tabela respectiva */

        break;

      case 'm':
        /* Execucao do comando m. Faz o output da informacao sobre deputados
         * ja eleitos por PPE num dado Estado-membro */

        scanf("%s", input);
        pais = atoi(input) - 1;
        dhondt(res_votos, res_mandatos, pais, mandatos[pais]);
        /* Obtem o numero do pais sobre qual fazer output da informacao e
         * aplica-lhe o metodo de D'Hondt */

        printf("  ");
        for (partido = 0; partido < NUM_PARTIDOS; partido++)
          printf(" %s", nomesPartidos[partido]);

        printf("\n%s", nomesPaises[pais]);
        for (partido = 0; partido < NUM_PARTIDOS; partido++)
          printf(" %3d", res_mandatos[pais][partido]);

        printf("\n");

        break;

      case 'e':
        /* Execucao do comando e. Faz o output da informacao sobre deputados
         * ja eleitos por PPE no total Uniao Europeia */

        for (pais = 0; pais < NUM_PAISES; pais++)
          dhondt(res_votos, res_mandatos, pais, mandatos[pais]);
        /* Aplica o metodo de D'Hondt a todos os paises da UE */

        printf("  ");
        for (partido = 0; partido < NUM_PARTIDOS; partido++)
          printf(" %s", nomesPartidos[partido]);

        for (pais = 0; pais < NUM_PAISES+TE; pais++) {
          printf("\n%s", nomesPaises[pais]);
          for (partido = 0; partido < NUM_PARTIDOS; partido++)
            printf(" %3d", res_mandatos[pais][partido]);
        }

        printf("\n");

        break;

      default:
        printf("ERRO: Comando desconhecido\n");
      }
    getchar(); /* le o caracter '\n' introduzido pelo utilizador */
  }

  return 0;
}
