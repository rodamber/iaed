/*
 * projecto.h -- definicoes e declaracoes globais para o primeiro projecto de
 * IAED, 2o semestre, 2013/2014
 */

#define NUM_PAISES 28
#define NUM_PARTIDOS 12
#define TE   1
/* TE corresponde ao total da Europa*/

int atoi(char s[]);
void dhondt(double res_votos[NUM_PAISES+TE][NUM_PARTIDOS],
  int res_mandatos[NUM_PAISES+TE][NUM_PARTIDOS], int pais, int mandatos);
