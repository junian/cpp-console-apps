#include <stdio.h>
#include <conio.h>

typedef struct mahasiswa
{
   float nilai;
   int umur;
}MHS_MASS[5], MHS_SINGLE;

int main()
{
   MHS_MASS data1;
   MHS_SINGLE data2[5];
   int i;
   for(i=0; i<5; i++)
   {
      fflush(stdin);
      scanf("%f %d", &data1[i].nilai, &data1[i].umur);
      data2[i].nilai = data1[i].nilai;
      data2[i].umur = data1[i].umur;
   }
   for(i=0; i<5; i++)
   {
      fflush(stdin);
      printf("%.2f %d\n", data2[i].nilai, data2[i].umur);
   }
   getch();
   return 0;
}
