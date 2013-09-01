//Program Penebak kartu pilihan user

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

char card[9][3][4]  =  {"1\3", "2\4", "9\6", 
                        "J\5", "6\6", "5\4",
                        "1\4", "3\5", "9\3",
                        "3\6", "4\4", "2\3",
                        "8\3", "9\5", "7\4",
                        "10\6", "Q\5", "4\3",
                        "2\5", "K\3", "10\5",
                        "J\6", "7\5", "K\4",
                        "Q\3", "3\4", "7\6"};

void arrangeCard(){
  char cardTmp[9][3][4], x, y;
  char i = -1, j = 0;
  for(x = 0; x < 9; x++)
    for(y = 0; y < 3; y++){
      if(i == 8){
        i = -1; 
        j++;
      }
      i++;
      strcpy(cardTmp[x][y], card[i][j]);
    }
  for(x = 0; x < 9; x++)
    for(y = 0; y < 3; y++)
      strcpy(card[x][y], cardTmp[x][y]);       
}

void read(char *chr){
  for(;;){
    *chr=getch();
    if(*chr != '1' && *chr != '2' && *chr != '3') continue;
    printf("%d\n", *chr-=48);
    return;
  }
}

void viewCard(){
  printf("\n 1   2   3");
  printf("\n=== === ===\n");
  for(char x = 0; x < 9; x++){
    for(char y = 0; y < 3; y++){
      printf("%3s ", card[x][y]);
    }
    printf("\n");
  }
  printf("\nWhere is your Card [1/2/3]? ");
}

int main(){
  char r;
  do{
    char x;
    system("cls");
    printf("Guess the Card\n");
    printf("==============\n\n");
    printf("Please choose a card in your mind...\n");
    viewCard();
    read(&r);
    arrangeCard();
    viewCard();
    read(&x);
    x += 2*(x - 1) + r;
    arrangeCard();
    viewCard();
    read(&r);
    printf("\nYour Card is %s, right? ^_^", card[x-2][r-1]);
    printf("\n\nWanna try again? [Y/N] ");
    do{
      r=getch();
    }while(r!='Y' && r!='y' && r!='n' && r!='N');
  }while(r=='Y' || r=='y');
  return 0;
}
