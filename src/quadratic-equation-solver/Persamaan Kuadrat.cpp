/*###################################################
  #                                                 #
  #   Program Pencari Akar-Akar Persamaan Kuadrat   #
  #   Copyright (C) 2008                            #
  #   By: Junian Triajianto (5108100038)            #
  #                                                 #
  ###################################################*/

#include <stdio.h>

#include <stdlib.h>
#include <math.h>

char toUpper(char x);

int main(){
  char r;
  do{
    float a=0, b, c, D, Xp, Xd;
    system("clear");
    printf("Pencari Akar-Akar Persamaan Kuadrat\n");
    printf("===================================\n\n");
    printf("ax^2 + bx + c = 0, a != 0\n\n");
    while(a == 0){
      printf("a = ");
      scanf("%f", &a);
      if (a==0)
        printf("Nilai a tidak boleh NOL!\n");
    }
    printf("b = ");
    scanf("%f", &b);
    printf("c = ");
    scanf("%f", &c);
    D = b*b - 4*a*c;
    Xp = -b / (2*a);
    if(D<0)
      Xd = sqrt(-D) / (2*a);
    else 
      Xd = sqrt(D) / (2*a); 
    printf("D = %0.0f\n\n", D);
    if(D == 0)
      printf("X1 = X2 = %0.3f", Xp);
    else if(D > 0)
      printf("X1 = %0.3f\nX2 = %0.3f", Xp + Xd, Xp - Xd);
    else if(b == 0 && D<0)
      printf("X1 = %0.3fi\nX2 = -%0.3fi", Xd, Xd);
    else
      printf("X1 = %0.3f + %0.3fi\nX2 = %0.3f - %0.3fi", Xp, Xd, Xp, Xd);
    printf("\n\nIngin Mengulang [Y/N]? ");
    do{
      r = getchar();
      r = toUpper(r);
    }while(r != 'Y' && r != 'N');
  }while(r == 'Y');
  return 0;
}

char toUpper(char x){
  if (x >= 97 && x <= 122) x=x-32;
  return x;
}
