//Bilangan Prima Kurang dari 100

#include <stdio.h>
//

int main(){
  char isPrime;
  printf("2\n3\n");
  for(int i=5; i<255; i+=2){
    isPrime=1;
    for(int j=3; j*j<=i; j+=2){
      if(i % j==0) {
        isPrime=0;
        break;
      }
    }
    if (isPrime) printf("%8d", i);
  }
  //getchar();
  return 0;
}
