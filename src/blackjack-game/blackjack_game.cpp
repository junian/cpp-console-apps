#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Player structure
struct player
{
  int poin;
  char hand[9][12];
};

void shuffle_deck(char *);
void command(char *, int);
int value(char);

int main()
{
  char r;
  do
  {
    int i;
    char deck[52][12], card = 0, pos = 2, com;
    struct player gamer, comp;
    gamer.poin = 0;
    comp.poin = 0;
    //system("clear");
    printf("BLACKJACK GAME ♦️"); puts("");
    printf("==============\n"); puts("");
    printf("Copyright (c) 2008 - Now() Junian.dev"); puts("");
    
    shuffle_deck(deck[0]);
    // Give each player 2 cards
    for (i = 0; i <= 1; i++)
    {
      gamer.poin += value(deck[card][0]);
      strcpy(gamer.hand[i], deck[card++]);
      comp.poin += value(deck[card][0]);
      strcpy(comp.hand[i], deck[card++]);
    }
    // Gamer Turn
    printf("\n\nYour Turn\n---------");
    do
    {
      printf("\n\nYou: ");
      for (i = 0; i < pos; i++)
        printf("%3s ", gamer.hand[i]);
      printf("\nCom: %3s  🃏🃏\n\n", comp.hand[0]);
      command(&com, gamer.poin);
      if (com == '1')
      {
        gamer.poin += value(deck[card][0]);
        strcpy(gamer.hand[pos++], deck[card++]);
      }
    } while (com != '2');
    com = pos;
    pos = 2;
    // Computer Turn
    printf("\n\nComp Turn\n---------");
    for (;;)
    {
      printf("\n\nYou: ");
      for (i = 0; i < com; i++)
        printf("%3s ", gamer.hand[i]);
      printf("\nCom: ");
      for (i = 0; i < pos; i++)
        printf("%3s ", comp.hand[i]);
      printf("\n\nCommand:\n--------\n");
      printf("[1] DRAW A CARD\n");
      printf("[2] STAND\n\n");
      printf("Comp choose: ");
      if (comp.poin < 15)
      {
        comp.poin += value(deck[card][0]);
        strcpy(comp.hand[pos++], deck[card++]);
        printf("1");
      }
      else
      {
        printf("2");
        break;
      }
    }
    // Each player Final Score
    printf("\n\nFinal Score:\n------------\n");
    printf("Your Point: %d\n", gamer.poin);
    printf("Comp Point: %d\n\n", comp.poin);
    if (gamer.poin > 21)
      gamer.poin = 21 - gamer.poin;
    if (comp.poin > 21)
      comp.poin = 21 - comp.poin;
    if (gamer.poin == comp.poin)
      printf("DRAW... Nobody Wins...!!!");
    else if (gamer.poin > comp.poin)
    {
      printf("YOU Win..!!");
      if (gamer.poin == 21)
        printf(" BLACKJACK...!!");
    }
    else
    {
      printf("COMP Win..!!");
      if (comp.poin == 21)
        printf(" BLACKJACK...!!");
    }
    printf("\n\nWanna try again [Y/N]? ");
    do
    {
      r = getchar();
    } while (r != 'Y' && r != 'y' && r != 'n' && r != 'N');
  } while (r == 'Y' || r == 'y');
  return 0;
}

void shuffle_deck(char *deck)
{
  char i, random;

  // Initialize Bridge Cards
  char bridge[52][12] = {"A❤️", "2❤️", "3❤️", "4❤️", "5❤️", "6❤️", "7❤️", "8❤️",
                        "9❤️", "10❤️", "J❤️", "Q❤️", "K❤️", "A♦️", "2♦️", "3♦️",
                        "4♦️", "5♦️", "6♦️", "7♦️", "8♦️", "9♦️", "10♦️", "J♦️",
                        "Q♦️", "K♦️", "A♠️", "2♠️", "3♠️", "4♠️", "5♠️", "6♠️",
                        "7♠️", "8♠️", "9♠️", "10♠️", "J♠️", "Q♠️", "K♠️", "A♣️",
                        "2♣️", "3♣️", "4♣️", "5♣️", "6♣️", "7♣️", "8♣️", "9♣️",
                        "10♣️", "J♣️", "Q♣️", "K♣️"};
  
  // Shuffle Deck
  srand(time(NULL));
  for (i = 0; i < 52; i++)
    //for (;;)
    {
      random = rand() % 52;
      if (!strcmp(bridge[random], ""))
        continue;
        printf("HERE %i\n", i);
      strcpy(deck + 4 * i, bridge[random]);
      strcpy(bridge[random], "");
      break;
    }
}

// Player Command
void command(char *com, int poin)
{
  printf("Command:\n--------\n");
  printf("[1] DRAW A CARD\n");
  printf("[2] STAND\n\n");
  printf("Choose a command: ");
  do
  {
    *com = getchar();
    if (*com == '2' && poin < 10)
    {
      printf("You must DRAW A CARD\nChoose a command: ");
      *com = '1';
      continue;
    }
    else if (*com == '1' && poin >= 21)
    {
      printf("You must STAND\nChoose a command: ");
      *com = '2';
      continue;
    }
  } while (*com != '1' && *com != '2');
  printf("%c", *com);
}

// Generate Value of the card
int value(char card)
{
  if (card >= '2' && card <= '9')
    return card - 48;
  else if (card == 'A')
    return 11;
  else
    return 10;
}
