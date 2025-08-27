//Pencetak Bilangan Ganjil

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

char toUpper(char);

main(){
  char r;
  int n;
  do{
    system("cls");
    printf("Pencetak Bilangan Ganjil\n");
    printf("========================\n\n");
    printf("Input N : ");
    scanf("%d", &n);
    printf("\nBilangan Ganjil Kurang dari %d:\n\n", n);
    for(int i=1;i<n;i+=2)
      printf("%4d ", i);
    printf("\n\nIngin Mengulang [Y/N]? ");
    do{
      r = getch();
      r = toUpper(r);
    }while(r != 'Y' && r != 'N');
  }while(r == 'Y');
}

char toUpper(char x){
  if (x >= 97 && x <= 122) x = x - 32;
  return x;
}
