#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int yMax, xMax;
int card[333][13];

void fillCard(){
  int n=1;
  for(int y = 0; y < yMax; y++)
    for(int x = 0; x < xMax; x++)
      card[y][x] = n++;
}

int pow(int x, int y){
  int tmpX;
  if (y == 0) return 1;
  else tmpX = x;
  for(int i=1; i<y; i++) tmpX *= x;
  return tmpX;
}

void arrangeCard(){
  int i = -1, j = 0;
  int cardTmp[333][13];
  for(int y = 0; y < yMax; y++)
    for(int x = 0; x < xMax; x++){
      if(i == yMax-1){
        i = -1; 
        j++;
      }
      i++;
      cardTmp[y][x] = card[i][j];
    }
  for(int y = 0; y < yMax; y++)
    for(int x = 0; x < xMax; x++)
      card[y][x] = cardTmp[y][x];
}

void viewCard(){
  printf("\n");
  for (int y=1; y<=xMax; y++) printf(" %2d   ", y);
  printf("\n");
  for (int y=1; y<=xMax; y++) printf("===== ");
  printf("\n");
  for(int y = 0; y < yMax; y++){
    for(int x = 0; x < xMax; x++){
      printf("%5d ", card[y][x]);
    }
    printf("\n");
  }
  printf("\nWhere is your Card [1");
  for (int y = 2; y <= xMax; y++) printf("/%d", y);
  printf("]? ");
}

int main(){
  int x, y = 0, chance;
  printf("Guess the Card\n");
  printf("==============\n\n");
  printf("Input Column [2-9]: ");
  scanf("%d", &xMax);
  printf("Input Chance: ");
  scanf("%d", &chance);
  yMax = pow(xMax, chance-1);
  printf("Please choose a card in your mind...\n");
  fillCard();
  for(int i = 0; i <= chance-2; i++){
    viewCard();
    scanf("%d", &x);
    y += (x-1) * pow(xMax, i);
    arrangeCard();
  }
  viewCard();
  scanf("%d", &x);
  printf("\nYour Card is %d, right? ^_^", card[y][x-1]);
  getch();
}
