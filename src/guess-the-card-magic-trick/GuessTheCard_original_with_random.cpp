#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <time.h>

char card[9][3][4];

void generateCard(){
  char random;
  char deck[52][4] = {"1\3", "2\3", "3\3", "4\3", "5\3", "6\3", "7\3", "8\3",
                      "9\3", "10\3", "J\3", "Q\3", "K\3", "1\4", "2\4", "3\4",
                      "4\4", "5\4", "6\4", "7\4", "8\4", "9\4", "10\4", "J\4",
                      "Q\4", "K\4", "1\5", "2\5", "3\5", "4\5", "5\5", "6\5",
                      "7\5", "8\5", "9\5", "10\5", "J\5", "Q\5", "K\5", "1\6",
                      "2\6", "3\6", "4\6", "5\6", "6\6", "7\6", "8\6", "9\6",
                      "10\6", "J\6", "Q\6", "K\6"};
  srand(time(NULL));
  for(char x=0; x<9; x++)
    for(char y=0; y<3; y++)
      for(;;){
        random = rand()%52;
        if(!strcmp(deck[random], "")) continue;
        strcpy(card[x][y], deck[random]);
        strcpy(deck[random], "");
        break;
      }
}

void read(char *chr){
  for(;;){
    *chr=getchar();
    if(*chr != '1' && *chr != '2' && *chr != '3') continue;
    printf("%d\n", *chr-=48);
    break;
  }
}

void arrangeCard(){
  char cardTmp[9][3][4], x, y;
  char i = -1, j = 0;
  for(x = 0; x < 9; x++)
    for(y = 0; y < 3; y++){
      if(i == 8){
        i = -1; 
        j++;
      }
      strcpy(cardTmp[x][y], card[++i][j]);
    }
  for(x = 0; x < 9; x++)
    for(y = 0; y < 3; y++)
      strcpy(card[x][y], cardTmp[x][y]);       
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
    system("clear");
    printf("Guess the Card\n");
    printf("==============\n\n");
    printf("Please choose a card in your mind...\n");
    generateCard();
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
      r=getchar();
    }while(r!='Y' && r!='y' && r!='n' && r!='N');
  }while(r=='Y' || r=='y');
  return 0;
}
