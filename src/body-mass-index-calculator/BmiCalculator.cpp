/*###################################################
  #                                                 #
  #   Body Mass index Calculator                    #
  #   Copyright (C) 2008 - Now()                    #
  #   By: Junian Triajianto 5108100038              #
  #                                                 #
  ###################################################*/

#include <stdio.h>
#include <stdlib.h>

char toUpper(char x);

int main()
{
  char r;
  do
  {
    system("clear");

    float bodyHeightInM, bodyMassIndex;
    int bodyWeightInKg;

    printf("┌──────────────────────────────┐\n");
    printf("│  Body Mass Index Calculator  │\n");
    printf("├──────┼───────────────────────┤\n");
    printf("│ BW   │ Body Weight (kg)      │\n");
    printf("│ BH   │ Body Height (m)       │\n");
    printf("│ BMI  │ Body Mass Index       │\n");
    printf("└──────┴───────────────────────┘\n\n");

    printf("BW   : ");
    scanf("%d", &bodyWeightInKg);

    printf("BH   : ");
    scanf("%f", &bodyHeightInM);

    bodyMassIndex = bodyWeightInKg / (bodyHeightInM * bodyHeightInM);

    printf("BMI  : %0.2f\n\n", bodyMassIndex);

    printf("Your result is ");
    if (bodyMassIndex < 18.5f)
      printf("Underweight (Below 18.5)");
    else if (bodyMassIndex < 25.0f)
      printf("Healthy (18.5 – 24.9)");
    else if (bodyMassIndex < 30)
      printf("Overweight (25.0 – 29.9)");
    else
      printf("Obesity (30.0 or above)");

    printf("\n\nTry again? [Y/n]? ");

    do
    {
      r = getchar();
      r = toUpper(r);
    } while (r != 'Y' && r != 'N');
  } while (r == 'Y');
  return 0;
}

char toUpper(char x)
{
  if (x >= 'a' && x <= 'z')
    x = x - 'a' + 'A';
  return x;
}
