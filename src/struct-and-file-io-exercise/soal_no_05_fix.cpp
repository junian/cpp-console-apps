#include <stdio.h>
#include <conio.h>

struct pecahan
{
   int pembilang;
   int penyebut;
};

void simplify(struct pecahan *a)
{
   int x, y, temp;
   
   x = (*a).pembilang;
   if(x==0) return;
   y = (*a).penyebut;
   
   while(!((temp = y%x)==0))
   {
      y = x;
      x = temp;
   }
   (*a).pembilang /= x;
   (*a).penyebut /= x;
}

void add(struct pecahan a[3])
{
   int x, y, i, j;
   simplify(&a[0]);
   simplify(&a[1]);
   i = x = a[0].penyebut;
   j = y = a[1].penyebut;
   
   while(i != j)
   {
      if(i<j) i += x;
      else if(i>j) j += y;
   }
   
   a[2].penyebut = j;
   for(i=0; i<2; i++)
   {
      a[i].pembilang *= j/a[i].penyebut;
      a[i].penyebut = j;
   }
   a[2].pembilang = a[0].pembilang + a[1].pembilang;
}

int main()
{
   struct pecahan data[3];
   int i, ix;
   
   printf("PROGRAM BILANGAN PECAHAN\n");
   printf("========================\n\n");
   
   for(i=0; i<2; i++)
   {
      printf("DATA %d\n", i+1);
      printf("pembilang: ");
      fflush(stdin);
      scanf("%d", &data[i].pembilang);
      do{
         printf("penyebut: ");
         fflush(stdin);
         scanf("%d", &data[i].penyebut);
      }while(data[i].penyebut==0);
   }
   printf("\n");
   
   for(i=0; i<2; i++)
   {
      printf("DATA %d = %d/%d = ", i+1, data[i].pembilang, data[i].penyebut);
      if(data[i].pembilang == 0) printf("0\n");
      else
      {
         simplify(&data[i]);
         ix = data[i].pembilang / data[i].penyebut;
         if(ix != 0) printf("%d ", ix);
         ix = data[i].pembilang % data[i].penyebut;
         if(ix != 0) printf("%d/%d", ix, data[i].penyebut);
         printf("\n");
      }
   }
   
   add(data);
   printf("Hasil Penjumlahan = %d/%d = ", data[2].pembilang, data[2].penyebut);
   if(data[2].pembilang == 0) printf("0 \n");
   else
   {
      simplify(&data[2]);
      i = data[2].pembilang / data[2].penyebut;
      if(i != 0) printf("%d ", i);
      i = data[2].pembilang % data[2].penyebut;
      if(i != 0) printf("%d/%d", i, data[2].penyebut);
      printf("\n");
   }
   
   getch();
   return 0;
}
