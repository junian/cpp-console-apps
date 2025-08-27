#include <stdio.h>
#include <conio.h>

int main(){
  int n, half;
  printf("Program Salib\n");
  printf("===============\n\n");
  printf("Input N: ");
  scanf("%d", &n);
  printf("\n");
  half=(n+1)/2;
  for(int i=0; i<n; i++){
    for(int j=1; j<=n; j++){
      if(i+1==half || j==half)
        printf(" o ");
      else if(i==0 || j==1)
        printf("%2d ", i+j);
      else if(j<=half-(n-i) || j>=half+(n-i))
        printf("%2d ", i-j+1);
      else if(j<half-i || j>half+i)
        printf("%2d ", i+j+1);
      else
        printf("   ");
    }
    printf("\n\n");
  }
  getch();
  return 0;
}
