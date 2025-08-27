//Pencetak Bilangan Prima Kurang dari 1000 dengan metode
//Sieve of Erastothenes

#include <stdio.h>


int main(){
  char isPrime[1000]; //gunakan variabel isPrime sebagai penentu kondisi
                    //apakah bilangan itu dicoret atau tidak

  for(int i=0; i<1000; i++)
    isPrime[i] = 1; //mula-mula semua bilangan dianggap prima
                    //dalam program ini diasumsikan jika array bernilai 1
                    //artinya belum dicoret, sedangkan 0 untuk yang sudah
                    //dicoret
  isPrime[0] = 0; //angka 0 dicoret
  isPrime[1] = 0; //angka 1 dicoret
  
  for(int i = 0; i < 1000; i++){
  //Jika ditemukan angka yang belum dicoret
    if(isPrime[i] == 1){
      printf("%8d", i); //cetak angka tersebut
      for(int j = 2*i; j < 1000; j += i)
        isPrime[j] = 0; //coret semua kelipatannya
    }
  }
  getchar();
  return 0;
}
