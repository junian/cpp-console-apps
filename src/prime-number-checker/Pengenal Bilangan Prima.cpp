//Pengenal Bilangan Prima

#include <stdio.h>

#include <stdlib.h>
#include <math.h>

char toUpper(char);

main(){
  char r, isPrime;
  int n;
  do{
    system("clear");
    isPrime = 1;
    printf("Pengenal Bilangan Prima\n");
    printf("=======================\n\n");
    printf("Input N : ");
    scanf("%d", &n);
    for(int i=2; i<=sqrt(n); i++){
      if(n % i == 0)
        isPrime = 0;
    }
    if(isPrime && n >= 2)
      printf("\n%d adalah BILANGAN PRIMA", n);
    else
      printf("\n%d adalah BUKAN BILANGAN PRIMA", n);
    printf("\n\nIngin Mengulang [Y/N]? ");
    do{
      r = getchar();
      r = toUpper(r);
    }while(r != 'Y' && r != 'N');
  }while(r == 'Y');
}

char toUpper(char x){
  if (x >= 97 && x <= 122) x = x - 32;
  return x;
}
