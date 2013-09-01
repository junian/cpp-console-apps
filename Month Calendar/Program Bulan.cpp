#include <stdio.h>
#include <conio.h>

int main(){
  int bln, thn;
  printf("Input Bulan [1-12]: ");
  scanf("%d", &bln);
  printf("Input Tahun: ");
  scanf("%d", &thn);
  printf("\n");
  switch(bln){
  case 1 : printf("Januari, 31"); break;
  case 2 : printf("Februari, "); 
           if((thn % 4 == 0 && thn % 100 != 0) || thn % 400 == 0)
             printf("29");
           else
             printf("28");
           break;
  case 3 : printf("Maret, 31"); break;
  case 4 : printf("April, 30"); break;
  case 5 : printf("Mei, 31"); break;
  case 6 : printf("Juni, 30"); break;
  case 7 : printf("Juli, 31"); break;
  case 8 : printf("Agustus, 31"); break;
  case 9 : printf("September, 30"); break;
  case 10: printf("Oktober, 31"); break;
  case 11: printf("November, 30"); break;
  case 12: printf("Desember, 31"); break;
  }
  printf(" hari");
  getch();
  return 0;
}
