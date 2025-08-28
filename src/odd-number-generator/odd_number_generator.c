// Pencetak Bilangan Ganjil

#include <stdio.h>

#include <stdlib.h>

char toUpper(char);

int main()
{
  char r;
  int n;
  do
  {
    system("clear");
    printf("Odd Number Generator\n");
    printf("====================\n\n");
    printf("Input N : ");
    fflush(stdout);
    scanf("%d", &n);
    printf("\nOdd number less than %d:\n\n", n);
    for (int i = 1; i < n; i += 2)
      printf("%4d ", i);
    printf("\n\nTry again [Y/n]? ");
    do
    {
      fflush(stdout);
      r = getchar();
      r = toUpper(r);
    } while (r != 'Y' && r != 'N');
  } while (r == 'Y');
}

char toUpper(char x)
{
  if (x >= 'a' && x <= 'z')
    x = x - 'a' + 'A';
  return x;
}
