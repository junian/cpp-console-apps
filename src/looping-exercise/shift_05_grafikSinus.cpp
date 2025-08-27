#include <stdio.h>


int main(){
  int n, x=1;
  printf("Grafik Sinus\n");
  printf("============\n\n");
  printf("Input N: ");
  scanf("%d", &n);
  printf("\n");
  for(int i=0; i<=n-1; i++){
    for(int j=1; j<=n+i; j++){
      if(j==n+i || j==n-i) printf("%d", x++);
      else printf(" ");
    }
    printf("\n");
  }
  for(int i=n-1; i>=0; i--){
    for(int j=1; j<2*n; j++) printf(" ");
    for(int j=1; j<=n+i; j++){
      if(j==n+i || j==n-i) printf("%d", --x);
      else printf(" ");
    }
    printf("\n");
  }
  getchar();
  return 0;
}
