//Magic Box Application

#include <stdio.h>
#include <stdlib.h>

int main(){
  char r;
  do{
    system("clear");
    int n, poin = 1;
    printf("MAGIC BOX\n");
    printf("=========\n\n");
    printf("Input N (Ganjil): ");
    fflush(stdin);
    scanf("%d", &n);
    int box[n][n], x=0, y=(n-1)/2;
    while(poin <= n*n ){
      if((poin-1) % n == 0 && poin > 1){
        x+=2;
        y-=1;
      }
      if(x < 0) x = n-1;
      if(y >= n) y = 0;
      box[x][y] = poin++;
      x--;
      y++;
    }
    printf("\n");
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++)
        printf("%3d ", box[i][j]);
      printf("\n");
    }
    printf("\nWanna try again? [Y/N] ");
    do{
      r=getchar();
    }while(r!='Y' && r!='y' && r!='N' && r!='n');
 }while(r=='y' || r=='Y');
 return 0;
}
