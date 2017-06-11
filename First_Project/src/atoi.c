int atoi(char s[]) {
  /* atoi devolve o inteiro correspondente a expressao (numero) introduzida
   * como parametro */

  int i, n;
  n = 0;

  for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
    n = 10 * n + (s[i] - '0');

  return n;
}
