/*###################################################
  #                                                 #
  #   Program Berat Badan Ideal                     #
  #   Copyright (C) 2008                            #
  #   By: Junian Triajianto 5108100038              #
  #                                                 #
  ###################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char toUpper(char x);

int main(){
  char r;
  do{
    system("cls");
    float TB, IMT;
    int BB;
    printf("Program Berat Badan Ideal\n");
    printf("=========================\n\n");
    printf("BB   : Berat Badan (kg)\n");
    printf("TB   : Tinggi Badan (m)\n");
    printf("IMT  : Indeks Massa Tubuh\n\n");
    printf("BB   : ");
    scanf("%d", &BB);
    printf("TB   : ");
    scanf("%f", &TB);
    IMT = BB / (TB * TB);
    printf("IMT  : %0.2f\n\n", IMT);
    printf("Anda Termasuk "); 
    if(IMT < 18.5)
      printf("KURUS");
    else if(IMT < 23)
      printf("IDEAL");
    else if(IMT < 25)
      printf("AGAK GEMUK");
    else if(IMT < 30)
      printf("GEMUK");
    else
      printf("SANGAT GEMUK");
    printf("\n\nIngin Mengulang [Y/N]? ");
    do{
      r = getch();
      r = toUpper(r);
    }while(r != 'Y' && r != 'N');
  }while(r == 'Y');
  return 0;
}

char toUpper(char x){
  if (x >= 97 && x <= 122) x=x-32;
  return x;
}
