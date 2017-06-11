#include "projecto.h"

void dhondt(double res_votos[NUM_PAISES][NUM_PARTIDOS],
            int res_mandatos[NUM_PAISES+TE][NUM_PARTIDOS], int pais, int mandatos)
/* Funcao que aplica o metodo de D'Hondt ao pais fornecido como parametro.
 * Recebe como parametros o resultado dos votos, a tabela onde colocar os
 * mandatos atribuidos, o pais ao qual aplicar o metodo e o numero de
 * mandatos maximo a atribuir a esse pais. */
{
  double votos[NUM_PARTIDOS];
  /* Tabela auxiliar onde se colocam os votos dos partidos e onde se aplicam
   * as sucessivas divisoes do metodo de D'Hondt */

  int partido;

  int max;
  /* Variavel cujo valor sera o indice do partido a atribuir o mandato */

  for (partido = 0; partido < NUM_PARTIDOS; partido++) {
    votos[partido] = res_votos[pais][partido];

    res_mandatos[NUM_PAISES][partido] -= res_mandatos[pais][partido];
    /* Retira os mandatos ja atribuidos aos partidos ao total da Europa,
     * antes de se aplicar de novo o metodo de D'Hondt */

    res_mandatos[pais][partido] = 0;
    /* Reset aos mandatos na tabela de resultados */
  }

  while (mandatos > 0) {
    max = 0;
    /* Por omissao, max corresponde ao primeiro partido, ou seja, aquele
     * que tem id mais pequeno */

    for (partido = 1; partido < NUM_PARTIDOS; partido++) {

      if (votos[max] < votos[partido])
        max = partido;

      else if ((votos[max] == votos[partido]) &&
               (res_votos[pais][partido] < res_votos[pais][max]))
        max = partido;
      /* Se tiverem os mesmos votos, atribuir a quem tem menos votos
       * totais */

      /* Se os partidos tiverem os mesmos votos e os mesmos votos totais,
       * atribuir ao que tiver menor id. Note-se que "max" e sempre menor
       * que "partido". */
    }
    /* Ve a quem deve ser atribuido o mandato */

    if (votos[max] == 0)
      break;
    /* Se o numero de votos em todos os partidos for zero, nao se prossegue
     * o algoritmo. */

    votos[max] = res_votos[pais][max]/(++res_mandatos[pais][max] + 1);

    mandatos--;

    res_mandatos[NUM_PAISES][max]++;
    /* Soma ao TE o mandato adicionado ao partido */
  }
}
