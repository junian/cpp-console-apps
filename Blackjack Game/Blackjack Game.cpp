#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Player structure
struct player{
  int poin;
  char hand[9][4];
};

void shuffleDeck(char *);
void command(char *, int);
int value(char);

int main(){
  char r;
  do{
    int i;
    char deck[52][4], card = 0, pos = 2, com;
    struct player gamer, comp;
    gamer.poin = 0;
    comp.poin = 0;
    system("cls");
    printf("BLACKJACK GAME\n");
    printf("==============\n");
    printf("(C) 2008 by Uchiha Junichi");
    shuffleDeck(deck[0]);
    //Give each player 2 cards
    for(i=0; i<=1; i++){
      gamer.poin += value(deck[card][0]);
      strcpy(gamer.hand[i], deck[card++]);
      comp.poin += value(deck[card][0]);
      strcpy(comp.hand[i], deck[card++]);
    }
    //Gamer Turn
    printf("\n\nYour Turn\n---------");
    do{
      printf("\n\nYou: ");
      for(i=0; i<pos; i++)
        printf("%3s ", gamer.hand[i]);
      printf("\nCom: %3s  %c%c\n\n", comp.hand[0], 177, 177);
      command(&com, gamer.poin);
      if(com == '1'){
        gamer.poin += value(deck[card][0]);
        strcpy(gamer.hand[pos++], deck[card++]);
      }  
    }while(com != '2');
    com = pos;
    pos = 2;
    //Computer Turn
    printf("\n\nComp Turn\n---------");
    for(;;){
      printf("\n\nYou: ");
      for(i=0; i<com; i++)
        printf("%3s ", gamer.hand[i]);
      printf("\nCom: ");
      for(i=0; i<pos; i++)
        printf("%3s ", comp.hand[i]);
      printf("\n\nCommand:\n--------\n");
      printf("[1] DRAW A CARD\n");
      printf("[2] STAND\n\n");
      printf("Comp choose: ");
      if(comp.poin < 15){
        comp.poin += value(deck[card][0]);
        strcpy(comp.hand[pos++], deck[card++]);
        printf("1");
      }else{
        printf("2");
        break;
      }
    }
    //Each player Final Score
    printf("\n\nFinal Score:\n------------\n");
    printf("Your Point: %d\n", gamer.poin);
    printf("Comp Point: %d\n\n", comp.poin);
    if(gamer.poin > 21) gamer.poin = 21 - gamer.poin;
    if(comp.poin > 21) comp.poin = 21 - comp.poin;
    if(gamer.poin == comp.poin)
      printf("DRAW... Nobody Wins...!!!");
    else if(gamer.poin > comp.poin){
      printf("YOU Win..!!");
      if(gamer.poin == 21) printf(" BLACKJACK...!!");
    }else{
      printf("COMP Win..!!");
      if(comp.poin == 21) printf(" BLACKJACK...!!");
    }
    printf("\n\nWanna try again [Y/N]? ");
    do{
      r = getch();
    }while(r!='Y' && r!='y' && r!='n' && r!='N');
  }while(r=='Y' || r=='y');
  return 0;
}

void shuffleDeck(char *deck){
  char i, random;
  //Initialize Bridge Cards
  char bridge[52][4] = {"A\3", "2\3", "3\3", "4\3", "5\3", "6\3", "7\3", "8\3",
                       "9\3", "10\3", "J\3", "Q\3", "K\3", "A\4", "2\4", "3\4",
                       "4\4", "5\4", "6\4", "7\4", "8\4", "9\4", "10\4", "J\4",
                       "Q\4", "K\4", "A\5", "2\5", "3\5", "4\5", "5\5", "6\5",
                       "7\5", "8\5", "9\5", "10\5", "J\5", "Q\5", "K\5", "A\6",
                       "2\6", "3\6", "4\6", "5\6", "6\6", "7\6", "8\6", "9\6",
                       "10\6", "J\6", "Q\6", "K\6"};
  //Shuffle Deck
  srand( time(NULL));
  for(i=0; i<52; i++)
    for(;;){
      random = rand()%52;
      if(!strcmp(bridge[random], "")) continue;
      strcpy(deck+4*i, bridge[random]);
      strcpy(bridge[random], "");
      break;
    }
}

//Player Command
void command(char *com, int poin){
  printf("Command:\n--------\n");
  printf("[1] DRAW A CARD\n");
  printf("[2] STAND\n\n");
  printf("Choose a command: ");
  do{
    *com = getch();
    if(*com == '2' && poin < 10){
      printf("You must DRAW A CARD\nChoose a command: ");
      *com = '1';
      continue;
    }else if(*com == '1' && poin >= 21){
      printf("You must STAND\nChoose a command: ");
      *com = '2';
      continue;
    }
  }while(*com != '1' && *com != '2');
  printf("%c", *com);
}

//Generate Value of the card
int value(char card){
  if(card >= '2' && card <= '9')
    return card-48;
  else if(card == 'A')
    return 11;
  else
    return 10;
}
