//Program Array menampilkan 10 bilangan
//dengan memberi * untuk yang terbesar

#include <stdio.h>
#include <stdlib.h>

char toUpper(char x){
  if (x >= 97 && x <= 122) x = x - 32;
  return x;
}

int main(){
  int n[9], MAX;
  char r;
  do{
    system("clear");
    printf("Program Pencetak 10 Bilangan\n");
    printf("============================\n");
    printf("* menunjukkan bilangan terbesar\n\n");
    //diasumsikan bilangan terbesar yang pertama adalah n[0]
    MAX=0;
    for(int i=0; i<=9; i++){
      printf("Masukkan Bilangan ke-%d: ", i+1);
      scanf("%d", &n[i]); fflush(stdin);
      if(n[i]>n[MAX]) MAX=i;
    }
    for(int i=0; i<=9; i++){
      printf("\nBilangan ke-%d: %d", i+1, n[i]);
      if(i==MAX) printf("*");;
    }
    printf("\n\nIngin Mengulang [Y/N]? ");
      do{
        r = toUpper(getchar());
      }while(r != 'Y' && r != 'N');
  }while(r == 'Y');
  return 0;
}
