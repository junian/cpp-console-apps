/*###################################################
  #                                                 #
  #   Game Gajah, Manusia, dan Semut                #
  #   Copyright (C) 2008                            #
  #   By: Junian Triajianto (5108100038)            #
  #                                                 #
  ###################################################*/

#include <stdio.h>

#include <stdlib.h>

char toUpper(char x);

int main(){
  char r, p, s;
  do{
    char a[4]="GMS", k[4]="GMS";
    int i;
    system("clear");
    printf("Game Gajah, Manusia, dan Semut\n");
    printf("==============================\n\n");
    printf("G: Gajah\nM: Manusia\nS: Semut");
    for(i=1;i<=2;i++){
      printf("\n\nAnda: %s\nKomp: %s\n", a, k);
      printf("\nAnda memilih ");
      do{
        p = getchar();
        p = toUpper(p);
      }while(p != 'G' && p != 'M' && p != 'S' || p == s);
      s = p;
      printf("%c\nKomp memilih ", p);
      if(p == 'G'){
        printf("M");
        k[0] = ' ';
        a[1] = ' ';
      }else if(p == 'M'){
        printf("S");
        k[1] = ' ';
        a[2] = ' ';
      }else if(p == 'S'){
        printf("G");
        k[2] = ' ';
        a[0] = ' ';
      }
    }
    printf("\n\nAnda: %s\nKomp: %s\n", a, k);
    printf("\nAnda KALAH!\n");
    printf("\nIngin Mengulang [Y/N]? ");
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
