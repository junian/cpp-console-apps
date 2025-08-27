// Pencetak Deret Fibonacci

#include <stdio.h>
#include <stdlib.h>

char toUpper(char);

int main()
{
  char r;
  do
  {
    int n, x = 0, y = 1, z = 1;
    system("clear");
    printf("Pencetak Deret Fibonacci\n");
    printf("========================\n\n");
    printf("Input N : ");
    scanf("%d", &n);
    printf("\nDeret Fibonacci Kurang dari %d:\n\n", n);
    while (z < n)
    {
      printf("%5d", z);
      z = x + y;
      x = y;
      y = z;
    }
    printf("\n\nIngin Mengulang [Y/N]? ");
    do
    {
      r = getchar();
      r = toUpper(r);
    } while (r != 'Y' && r != 'N');
  } while (r == 'Y');

  return 0;
}


/**
 * Converts a lowercase alphabetic character to its uppercase equivalent.
 *
 * @param x The character to convert.
 * @return The uppercase version of the character if it is a lowercase letter;
 *         otherwise, returns the character unchanged.
 */
char toUpper(char x)
{
  if (x >= 'a' && x <= 'z')
    x = x - 'a' + 'A';
  return x;
}
