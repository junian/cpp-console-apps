#include <stdio.h>

#include <stdlib.h>

int main(){
  char r;
  do{
    system("clear");
    int n, i, limit, poin = 1;
    printf("SPIRAL BOX\n");
    printf("==========\n\n");
    printf("Input N : ");
    fflush(stdin);
    scanf("%d", &n);
    int box[n][n];
    limit = n;
    while(limit>=1){
      //dari kiri ke kanan
      for(i=n-limit; i<limit; i++)
        box[n-limit][i] = poin++;
      limit--;
      //dari atas ke bawah
      for(i=n-limit; i<=limit; i++)
        box[i][limit]=poin++;
      //dari kanan ke kiri
      for(i=limit-1; i>=n-limit-1; i--)
        box[limit][i]=poin++;
      limit--;
      //dari bawah ke atas
      for(i=limit; i>=n-limit-1; i--)
        box[i][n-limit-2] = poin++;
      limit++;
    }
    printf("\n");
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++)
        printf("%3d ", box[i][j]);
      printf("\n\n");
    }
    printf("Wanna try again? [Y/N] ");
    do{
      r=getchar();
    }while(r!='Y' && r!='y' && r!='N' && r!='n');
 }while(r=='y' || r=='Y');
 return 0;
}
